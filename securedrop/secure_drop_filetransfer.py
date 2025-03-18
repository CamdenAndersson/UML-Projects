import socket
import json
import os
import logging
from secure_drop_contacts import check_online_status
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

KEY = get_random_bytes(16)  # This should be managed securely
BUFFER_SIZE = 1024  # Read buffer size

def encrypt_data(data):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    return iv + encrypted_data  # Return IV along with the encrypted data for use in decryption

def decrypt_data(encrypted_data):
    #print(f"Decrypting data of length: {len(encrypted_data)}")
    if len(encrypted_data) % AES.block_size != 0:
        raise ValueError("Encrypted data not a multiple of block size")
    iv = encrypted_data[:AES.block_size]
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    try:
        decrypted_data = unpad(cipher.decrypt(encrypted_data[AES.block_size:]), AES.block_size)
    except ValueError as e:
        print("Error in unpadding data", e)
        raise
    return decrypted_data

def hash_file(file_path):
    hasher = SHA256.new()
    with open(file_path, 'rb') as file:
        buffer = file.read(BUFFER_SIZE)
        while buffer:
            hasher.update(buffer)
            buffer = file.read(BUFFER_SIZE)
    return hasher.hexdigest()

def reliable_recv(sock, total_length):
    data = b''
    while len(data) < total_length:
        packet = sock.recv(min(total_length - len(data), BUFFER_SIZE))
        if not packet:
            raise Exception(f"Connection closed by client, expected {total_length}, received {len(data)}")
        data += packet
    return data

def send_file(email, sender_email, server_ip, port, file_path):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((server_ip, port))
            metadata = {
                'type': 'file_transfer',
                'recipient_email': email,
                'sender_email': sender_email,
                'file_name': os.path.basename(file_path),
                'file_size': os.path.getsize(file_path)
            }
            sock.sendall(json.dumps(metadata).encode())

            # Wait for the recipient to accept the file transfer
            response = sock.recv(1024).decode()
            
            if response == "Accepted":
                print("Receiver accepted the file transfer.")
                # Proceed to send the file data
                with open(file_path, 'rb') as file:
                    file_data = file.read()
                    sock.sendall(file_data)
                print(f"File {file_path} has been successfully sent.")
            elif response == "Rejected" or response == '':
                print("Receiver rejected the file transfer.")
            #else:
               # print(f"Unexpected response from server: {response}")

    except Exception as e:
        print(f"Error during file transmission: {e}")


def send_metadata(sock, metadata):
    try:
        metadata_json = json.dumps(metadata).encode()
        #print(f"Sending metadata: {metadata_json}")  # Debug output
        sock.sendall(metadata_json)
    except Exception as e:
        print(f"Failed to send metadata: {e}")