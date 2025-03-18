import os
import socket
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import json

KEY = b'Sixteen byte key'  # This key should be securely shared and stored.

def encrypt_data(data):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    return iv + encrypted_data

def decrypt_data(data):
    iv = data[:AES.block_size]
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    decrypted_data = unpad(cipher.decrypt(data[AES.block_size:]), AES.block_size)
    return decrypted_data

def send_file(socket, filename):
    try:
        filesize = os.path.getsize(filename)
        metadata = json.dumps({'filename': os.path.basename(filename), 'filesize': filesize})
        socket.sendall(encrypt_data(metadata.encode('utf-8')))
        with open(filename, 'rb') as file:
            while True:
                chunk = file.read(4096)
                if not chunk:
                    break
                socket.sendall(encrypt_data(chunk))
    except FileNotFoundError:
        print("File not found.")
    except Exception as e:
        print(f"Failed to send file: {e}")

def receive_file(socket, save_path):
    metadata = decrypt_data(socket.recv(1024))
    file_info = json.loads(metadata.decode('utf-8'))
    filename = file_info['filename']
    filesize = file_info['filesize']
    file_path = os.path.join(save_path, filename)
    
    with open(file_path, 'wb') as file:
        remaining = filesize
        while remaining > 0:
            chunk = decrypt_data(socket.recv(4096))
            file.write(chunk)
            remaining -= len(chunk)
    return file_path

def send_file_request(socket, recipient_email, filename):
    request_message = f"Request to send file {filename} to {recipient_email}. Accept (y/n)?"
    socket.sendall(encrypt_data(request_message.encode('utf-8')))
    try:
        response = decrypt_data(socket.recv(1024)).decode('utf-8').strip().lower()
        return response == 'y'
    except Exception as e:
        print(f"Error processing response: {e}")
        return False