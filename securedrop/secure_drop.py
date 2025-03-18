import sys
import json
import threading
import socket
import config
from getpass import getpass
from Crypto.Hash import SHA256
from Crypto.Random import get_random_bytes
from secure_drop_contacts import add_contact, list_contacts, load_encrypted_contacts
from secure_drop_server import start_user_server
from secure_drop_filetransfer import send_file
from secure_drop_client import check_online_status
from secure_drop_filetransfer import encrypt_data

# Constants for file paths
USER_FILE = 'user_data.json'

# Utility functions
def load_users():
    try:
        with open(USER_FILE, 'r') as file:
            return json.load(file)
    except FileNotFoundError:
        return {}

def save_users(users):
    with open(USER_FILE, 'w') as file:
        json.dump(users, file, indent=4)

def hash_password(password):
    salt = get_random_bytes(16)  # Generates a 16-byte salt
    hasher = SHA256.new(salt + password.encode('utf-8'))
    return salt.hex() + hasher.hexdigest()

def check_password(stored, provided_password):
    salt = bytes.fromhex(stored[:32])  # Salt is the first 32 hex characters
    stored_hash = stored[32:]
    hasher = SHA256.new(salt + provided_password.encode('utf-8'))
    return hasher.hexdigest() == stored_hash

def register_user():
    users = load_users()
    email = input("Enter Email Address: ")
    if email in users:
        print("User already registered.")
        return
    
    name = input("Enter Full Name: ")
    password = getpass("Enter Password: ")
    re_password = getpass("Re-enter Password: ")
    
    while password != re_password:
        print("Passwords do not match. Try again.")
        password = getpass("Enter Password: ")
        re_password = getpass("Re-enter Password: ")
    
    hashed_password = hash_password(password)
    users[email] = {'name': name, 'password': hashed_password, 'contacts': {}}
    save_users(users)
    print("User Registered.\nExiting SecureDrop.")
    sys.exit()

def login_user():
    users = load_users()
    email = input("Enter Email Address: ")
    password = getpass("Enter Password: ")
    
    if email in users and check_password(users[email]['password'], password):
        print('Login successful.\nWelcome to SecureDrop.\nType "help" for commands')
        user_data = users[email]
        contacts = load_encrypted_contacts()  # Assuming 'contacts' are stored under user data
        #print("Loaded contacts for user:", contacts)  # Log the loaded contacts

        # Start server with contacts
        server_thread = threading.Thread(target=start_user_server, args=(), daemon=True)
        server_thread.start()
        return email
    else:
        print("Invalid email or password.")
        sys.exit()

def send_accept_command(server_ip, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((server_ip, port))
        accept_cmd = json.dumps({'type': 'accept_file'})
        sock.sendall(accept_cmd.encode())
        response = sock.recv(1024).decode()
        #print("Server response:", response)

def send_reject_command(server_ip, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((server_ip, port))
        reject_cmd = json.dumps({'type': 'reject_file'})
        sock.sendall(reject_cmd.encode())
        response = sock.recv(1024).decode()
        #print("Server response:", response)

# Main loop that handles input
def main():
    if not load_users():
        print("No users are registered with this client.")
        if input("Do you want to register a new user (y/n)? ").lower() == 'y':
            register_user()
    else:
        print("Please login to continue.")
        config.user_email = login_user()
        user_email = config.user_email
        while True:
            if config.waiting_for_file_transfer_acceptance:
                response = input("Accept the file transfer (y/n)? ").strip().lower()
                if response == 'y':
                    print("File transfer accepted.")
                    #send_accept_command(server_ip, port)
                    print("send_accept_command")
                    config.waiting_for_file_transfer_acceptance = False
                elif response == 'n':
                    print("File transfer rejected.")
                    #send_reject_command(server_ip, port)
                    print("send_reject_command")
                    config.waiting_for_file_transfer_acceptance = False
            else:
                if config.waiting_for_file_transfer_acceptance:
                    pass
                command_input = input("secure_drop> ").strip()
                handle_command(command_input, user_email)

def handle_command(command_input, user_email):
    command_parts = command_input.split()
    command = command_parts[0].lower() if command_parts else None

    if len(command_parts) == 0:
        pass  # No command entered
    if command == "help":
        print_commands()
    elif command == "add":
        add_contact()
    elif command == "list":
        list_contacts()
    elif command == "send":
                if len(command_parts) < 3:
                    print("Usage: send <email> <file_path>")
                else:
                    recipient_email = command_parts[1]
                    file_path = ' '.join(command_parts[2:])  # Join the rest as the file path
        
                    # Using check_online_status to get port number
                    online, port = check_online_status(recipient_email, user_email)
                    if online and port is not None:
                        server_ip = 'localhost'  # Or another IP if known and different
                        send_file(recipient_email, user_email, server_ip, port, file_path)
                    else:
                        #print(f"{recipient_email} is not online or port not found.")
                        pass
    elif command == "exit":
        sys.exit()
    else:
        print("Invalid command. Type 'help' for available commands.")

if __name__ == '__main__':
    main()

def print_commands():
    print("\"add\" -> Add a new contact")
    print("\"list\" -> List all online contacts")
    print("\"send\" -> Transfer file to contact")
    print("\"exit\" -> Exit SecureDrop")