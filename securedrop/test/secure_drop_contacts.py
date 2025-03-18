import sys
import os
import json
from getpass import getpass
from Crypto.Hash import SHA256
from Crypto.Random import get_random_bytes
from secure_drop_contacts import *
from file_transfer import *
from secure_drop import *
import socket
import threading

# Constants for file paths
USER_FILE = 'user_data.json'

# Global variable to store online contacts
online_contacts = set()

# Utility functions
# (Existing utility functions remain unchanged)
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

def check_online(email, online_contacts):
    return email in online_contacts

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
    users[email] = {'name': name, 'password': hashed_password}
    save_users(users)
    print("User Registered.")

def login_user():
    users = load_users()
    email = input("Enter Email Address: ")
    password = getpass("Enter Password: ")
    
    if email in users and check_password(users[email]['password'], password):
        print('Login successful.\nWelcome to SecureDrop.\nType "help" for commands')
        return email
    else:
        print("Invalid email or password.")
        sys.exit()

def add_contact_command():
    add_contact()

def list_contacts_command():
    global online_contacts
    contacts = load_encrypted_contacts()
    if online_contacts:
        print("The following contacts are online:")
        for email in online_contacts:
            if email in contacts:
                name = contacts[email]
                print(f"* {name} <{email}>")
    else:
        print("No contacts are currently online.")

def process_command(command, host, port):
    if command == "add":
        add_contact_command()
    elif command == "list":
        list_contacts_command()
    elif command.startswith("send "):
        parts = command.split()
        if len(parts) == 3:
            recipient_email = parts[1]
            filename = parts[2]
            send_file_command(recipient_email, filename, host, port)
        else:
            print("Invalid command format. Use: send recipient_email filename")
    elif command == "exit":
        os._exit(0)  # Exit the program immediately
    else:
        print("Invalid command. Type \"help\" for commands.")

def secure_drop_shell(host, port, running):
    global online_contacts  # Reference the global variable
    while running.is_set():
        command = input("secure_drop> ").strip().lower()
        if command == "help":
            print("\"add\" -> Add a new contact")
            print("\"list\" -> List all online contacts")
            print("\"send\" -> Transfer file to contact")
            print("\"exit\" -> Exit SecureDrop")
        else:
            process_command(command, host, port)

def handle_client(client_socket, address, email, host, port, running):
    print(f"[INFO] New connection from {address}, Email: {email}")
    
    # Load contacts to check if the connecting user is a friend
    contacts = load_encrypted_contacts()
    
    # Check if the email is in contacts to determine if the user is a friend
    if email in contacts:
        online_contacts.add(email)
    
    while running.is_set():
        data = client_socket.recv(1024)
        if not data:
            print(f"[INFO] {address} disconnected")
            # Remove the client from online contacts when they disconnect
            if email in online_contacts:
                online_contacts.remove(email)
            break
        else:
            command = data.decode().strip().lower()
            if command == "exit":
                break
            else:
                process_command(command, host, port)
                response = "Server received your command: " + command
                client_socket.send(response.encode())
    
    if email in online_contacts:
        online_contacts.remove(email)
    
    client_socket.close()  # Close the client socket when done
            
def main():
    host = '127.0.0.1'
    port = 8080

    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind((host, port))
    server_sock.listen(5)
    
    if not load_users():
        print("No users are registered with this client.")
        if input("Do you want to register a new user (y/n)? ").lower() == 'y':
            register_user()
    else:
        print("Please login to continue.")
        login_user()

    print(f"[INFO] Server listening on {host}:{port}")

    running = threading.Event()
    running.set()

    # Start SecureDrop shell thread
    secure_drop_shell_thread = threading.Thread(target=secure_drop_shell, args=(host, port, running))
    secure_drop_shell_thread.start()

    while running.is_set():
        client_socket, address = server_sock.accept()
        email = client_socket.recv(1024).decode().strip()
        
        online_contacts.add(email)  # Update online contacts
        client_handler = threading.Thread(target=handle_client, args=(client_socket, address, email, host, port, running))
        client_handler.start()

    server_sock.close()  # Close the server socket when done

if __name__ == "__main__":
    main()
