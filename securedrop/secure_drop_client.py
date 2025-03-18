
import socket
import json
import logging
import config
#import tls

#logging.basicConfig(level=logging.DEBUG)

def check_online_status(contact_email, sender_email):
    for port in range(5000, 5004):  # Ensure you are checking the correct port range
        if port == config.SERVER_PORT:
            continue  # Skip the server's own port to avoid false positives
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.settimeout(2)  # Enough timeout to wait for the response
                s.connect(('localhost', port))
                request = json.dumps({'type': 'ping', 'recipient_email': contact_email, 'sender_email': sender_email}).encode()
                s.sendall(request)

                response_bytes = s.recv(1024)  # Receive the response
                #print(response_bytes)
                if response_bytes:
                    response = json.loads(response_bytes.decode())
                    if response.get('status') == 'online' and response.get('email') == contact_email:
                        #print(f"{contact_email} is online at port {port}")
                        return True, port
                #print("No response or not the expected response received")
        except socket.error as e:
            pass
            #print(f"Error connecting to port {port}: {e}")
        except json.JSONDecodeError as e:
            print(f"JSON decoding error: {e}")
        except Exception as e:
            print(f"Error during checking online status: {e}")
    #print(f"{contact_email} is not online on any checked port.")
    return False, None


#def create_secure_socket(host, port):
 #   context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
 #   context.load_verify_locations('path/to/cacert.pem')  # Load CA certificates if necessary

    # Create a raw socket and wrap it with SSL
 #   with socket.create_connection((host, port)) as sock:
 #       with context.wrap_socket(sock, server_hostname=host) as secure_sock:
 #           # Now you can use secure_sock to communicate with the server securely
 #           secure_sock.sendall(b"Hello, TLS!")
 #           print(secure_sock.recv(4096))