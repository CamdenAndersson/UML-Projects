#from cryptography import x509
#from cryptography.hazmat.primitives import hashes
#from cryptography.hazmat.primitives.asymmetric import rsa
#from cryptography.x509.oid import NameOID
#from datetime import datetime, timedelta
#from cryptography.hazmat.primitives.serialization import BestAvailableEncryption, Encoding, PrivateFormat, NoEncryption

# This module can be dynamically configured from anywhere
SERVER_PORT = None

# Global variable to keep track of the file transfer state
waiting_for_file_transfer_acceptance = False

# Email of the current user
user_email = None

# obvious
current_file_transfer_data = None


# certificate authority attempt

#def generate_ca_certificate():
#    # Generate private key
#    private_key = rsa.generate_private_key(
#        public_exponent=65537,
#        key_size=2048,
#    )
    
    # Generate a self-signed certificate
#    subject = issuer = x509.Name([
#        x509.NameAttribute(NameOID.COUNTRY_NAME, u"US"),
#        x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, u"California"),
#        x509.NameAttribute(NameOID.LOCALITY_NAME, u"San Francisco"),
#        x509.NameAttribute(NameOID.ORGANIZATION_NAME, u"My SecureDrop CA"),
#        x509.NameAttribute(NameOID.COMMON_NAME, u"securedrop.example.com"),
#    ])
#    cert = x509.CertificateBuilder().subject_name(
#        subject
#    ).issuer_name(
#        issuer
#    ).public_key(
#        private_key.public_key()
#    ).serial_number(
#        x509.random_serial_number()
#    ).not_valid_before(
#        datetime.utcnow()
#    ).not_valid_after(
#        # Our certificate will be valid for 10 years
#        datetime.utcnow() + timedelta(days=365*10)
#    ).add_extension(
#        x509.BasicConstraints(ca=True, path_length=None), critical=True,
#    ).sign(private_key, hashes.SHA256())

    # Save the private key and certificate
#    with open("ca_private_key.pem", "wb") as f:
#        f.write(private_key.private_bytes(
#            encoding=Encoding.PEM,
#            format=PrivateFormat.TraditionalOpenSSL,
#            encryption_algorithm=NoEncryption()  # Should be encrypted in production
#        ))
    
#    with open("ca_certificate.pem", "wb") as f:
#        f.write(cert.public_bytes(Encoding.PEM))
    
#    return cert, private_key

#ca_cert, ca_private_key = generate_ca_certificate()