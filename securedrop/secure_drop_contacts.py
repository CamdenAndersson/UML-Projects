import json
import os
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
from secure_drop_client import check_online_status
import socket
import config
import logging

# Constants for file paths and key
CONTACTS_FILE = 'contacts_data.json'
KEY = b'Sixteen byte key'

def load_encrypted_contacts():
    try:
        with open('contacts_data.json', 'rb') as file:
            iv = file.read(16)  # Read exactly 16 bytes for the IV
            cipher = AES.new(KEY, AES.MODE_CBC, iv)
            decrypted_data = unpad(cipher.decrypt(file.read()), AES.block_size)
            return json.loads(decrypted_data.decode('utf-8'))
    except Exception as e:
        #logging.error(f"Failed to load or decrypt contacts: {str(e)}")
        return {}
    
def save_encrypted_contacts(contacts):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(json.dumps(contacts).encode('utf-8'), AES.block_size))
    with open('contacts_data.json', 'wb') as file:
        file.write(iv)  # Write the IV at the start of the file
        file.write(encrypted_data)

def add_contact():
    name = input("Enter Full Name: ")
    email = input("Enter Email Address: ")
    if email == config.user_email:
        return None
    contacts = load_encrypted_contacts()
    contacts[email] = name
    save_encrypted_contacts(contacts)
    print("Contact added.")

def list_contacts():
    contacts = load_encrypted_contacts()  # Ensure this loads correctly
    logging.debug("Loaded contacts: {}".format(contacts))
    online_contacts = []

    for email, name in contacts.items():
        logging.debug(f"Checking online status for {email}")
        online_status, _ = check_online_status(email, config.user_email)
        if online_status:
            online_contacts.append((name, email))
            logging.info(f"{name} <{email}> is online")
        else:
            logging.debug(f"{name} <{email}> is not online")

    if online_contacts:
        print("The following contacts are online:")
        for name, email in online_contacts:
            print(f"* {name} <{email}>")
    else:
        print("No contacts are currently online.")
