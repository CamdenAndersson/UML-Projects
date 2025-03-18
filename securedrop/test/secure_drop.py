import json
import os
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from file_transfer import *
import socket

CONTACTS_FILE = 'contacts_data.json'
KEY = get_random_bytes(16)

def load_encrypted_contacts():
    try:
        with open(CONTACTS_FILE, 'rb') as file:
            iv = file.read(16)
            cipher = AES.new(KEY, AES.MODE_CBC, iv)
            decrypted_data = unpad(cipher.decrypt(file.read()), AES.block_size)
            return json.loads(decrypted_data.decode('utf-8'))
    except (FileNotFoundError, json.JSONDecodeError):
        return {}

def save_encrypted_contacts(contacts):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(json.dumps(contacts).encode('utf-8'), AES.block_size))

    with open(CONTACTS_FILE, 'wb') as file:
        file.write(iv)
        file.write(encrypted_data)

def add_contact():
    name = input("Enter Full Name: ")
    email = input("Enter Email Address: ")
    contacts = load_encrypted_contacts()
    contacts[email] = name
    save_encrypted_contacts(contacts)
    print("Contact added.")



def mark_contact_online(email):
    global online_contacts
    online_contacts.add(email)

def mark_contact_offline(email):
    global online_contacts
    if email in online_contacts:
        online_contacts.remove(email)

def check_online(email):
    return email in online_contacts
def list_contacts():
    global online_contacts
    if online_contacts:
        print("The following contacts are online:")
        for email in online_contacts:
            name = load_encrypted_contacts().get(email, "Unknown")
            print(f"* {name} <{email}>")
    else:
        print("No contacts are currently online.")

def send_file_command(recipient_email, filename, host, port, online_contacts):
    if os.path.exists(filename):
        if check_online(recipient_email, online_contacts):  # Pass the set to the function
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
                try:
                    client_socket.connect((host, port))
                    if send_file_request(client_socket, recipient_email, filename):
                        send_file(client_socket, filename)
                        print("File sent successfully.")
                    else:
                        print("Recipient has declined the transfer.")
                except ConnectionRefusedError:
                    print("Connection refused. Ensure the server is running.")
        else:
            print("Recipient is not online.")
    else:
        print("File not found.")
