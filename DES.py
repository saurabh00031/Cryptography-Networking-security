from Crypto.Cipher import DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

def generate_key():
    # Generate a random 8-byte key for DES
    return get_random_bytes(8)

def encrypt_text(key, plaintext):
    cipher = DES.new(key, DES.MODE_ECB)
    plaintext = pad(plaintext.encode(), DES.block_size)
    ciphertext = cipher.encrypt(plaintext)
    return ciphertext
           

if __name__ == "__main__":
            print("_________________________________________________________________")
            print("Let's Explore Cybersecurity -- DES  Algorithm")
            print("_________________________________________________________________")
            key = generate_key()
            plaintext = input("Enter the text to encrypt: ")
            ciphertext = encrypt_text(key, plaintext)
            print(f"Encrypted text: {ciphertext.hex()}")
            print("_________________________________________________________________")
