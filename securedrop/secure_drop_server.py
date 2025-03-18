import socket
import json
import os
from secure_drop_filetransfer import decrypt_data, BUFFER_SIZE, reliable_recv
from Crypto.Hash import SHA256
import logging
import threading
import logging
import config
from secure_drop_contacts import load_encrypted_contacts

incoming_files = {}

def start_user_server():
    server_socket = None
    for port in range(5000, 5004):  # Adjust the range if needed
        try:
            server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            server_socket.bind(('', port))
            config.SERVER_PORT = port
            server_socket.listen(5)
            #print(f"Server listening on port {port}")
            break
        except socket.error as e:
            #print(f"Port {port} is in use. Trying next port...")
            continue

    if server_socket is None:
        print("Failed to bind to any port in the range 5001-8000.")
        return

    try:
        while True:
            client_socket, addr = server_socket.accept()
            #print(f"Connection from {addr}")
            # Handle each client connection in a new thread
            threading.Thread(target=handle_client_connection, args=(client_socket,addr)).start()
    except Exception as e:
        logging.error(f"Error accepting connections: {e}")
    finally:
        if server_socket:
            server_socket.close()

def handle_file_transfer(client_socket, metadata):
    file_size = metadata['file_size']
    file_name = metadata['file_name']
    received_size = 0
    file_data = b''

    # Receive the file data
    while received_size < file_size:
        packet = client_socket.recv(1024)
        if not packet:
            break
        file_data += packet
        received_size += len(packet)

    # Save the received file
    with open(f'./received_files/{file_name}', 'wb') as f:
        f.write(file_data)

    # Send confirmation back to the client
    response = "File received successfully"
    client_socket.sendall(response.encode())
    print(f"File {file_name} received and saved successfully.")


def receive_data(sock):
    # First receive the length of the data
    data_length_bytes = sock.recv(4)
    if len(data_length_bytes) < 4:
        raise Exception("Failed to receive the full data length")
    data_length = int.from_bytes(data_length_bytes, 'big')
    if data_length > 10000000:  # Example max length check
        raise ValueError("Received data length is too large and unrealistic: {}".format(data_length))
    return reliable_recv(sock, data_length)

def receive_metadata(sock):
    metadata_length_bytes = sock.recv(4)
    if len(metadata_length_bytes) != 4:
        raise ValueError("Metadata length incorrect")
    metadata_length = int.from_bytes(metadata_length_bytes, 'big')
    metadata = sock.recv(metadata_length).decode()
    return json.loads(metadata)

def handle_client_connection(client_socket, client_address):
    try:
        # Receive initial message which should contain metadata
        data = client_socket.recv(1024).decode()
        contacts = load_encrypted_contacts()
        if data:
            metadata = json.loads(data)
            if metadata['type'] == 'file_transfer' and metadata['sender_email'] in contacts:
                response = input(f"Contact '{metadata['sender_email']}' is sending a file named '{metadata['file_name']}'. Accept (y/n)? ")
                if response.lower() == 'y':
                    client_socket.sendall(b"Accepted")
                    receive_file(client_socket, metadata)
                elif response.lower == 'n':
                    client_socket.sendall(b"Rejected")
            elif metadata['type'] == 'ping':
                # Load the recipient's contact list to check if the sender is a known contact
                contacts = load_encrypted_contacts()  # Make sure this function retrieves contacts for the specific logged-in user
                if metadata['sender_email'] in contacts:
                    # Handle ping request to check online status if sender is a known contact
                    response = json.dumps({'status': 'online', 'email': config.user_email}).encode()
                    client_socket.sendall(response)
                    #logging.debug(f"Sent response: {response}")
                else:
                    # If the sender is not in the recipient's contacts, do not acknowledge the ping
                    print(f"Received ping from unknown contact: {metadata['email']}")
    except Exception as e:
        #print(f"Error handling client connection: {e}")
        pass
    finally:
        client_socket.close()

def receive_file(client_socket, metadata):
    ensure_directory_exists()
    file_size = metadata['file_size']
    file_name = metadata['file_name']
    received_size = 0
    file_data = b''

    # Receiving the file data
    while received_size < file_size:
        data = client_socket.recv(1024)
        if not data:
            break
        file_data += data
        received_size += len(data)

    # Saving the file
    with open(f'./received_files/{file_name}', 'wb') as file:
        file.write(file_data)
    print(f"File {file_name} received and saved successfully.")

def ensure_directory_exists():
    directory = "./received_files"
    if not os.path.exists(directory):
        os.makedirs(directory)


#def create_secure_server_socket(host, port):
#    context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
#    context.load_cert_chain(certfile='path/to/server.crt', keyfile='path/to/server.key')  # Load server certificate and key

    # Bind socket to host and port
#    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
#        sock.bind((host, port))
#        sock.listen(5)
#        print(f"Server listening on {host}:{port}")

#        while True:
#            client_socket, addr = sock.accept()
#            with context.wrap_socket(client_socket, server_side=True) as secure_sock:
#                print(f"Secure connection with {addr}")
#                try:
#                    print(secure_sock.recv(4096))  # Receive data securely
#                    secure_sock.sendall(b"Hello from TLS server!")
#                except ssl.SSLError as e:
#                    print(f"SSL error: {e}")
