import sympy
import random
import math
import time

def generate_20_digit_prime():
    while True:
        num = random.randint(10**19, 10**20 - 1)
        if sympy.isprime(num):
            return num

def generate_keypair():
    p = generate_20_digit_prime()
    q = generate_20_digit_prime()
    n = p * q
    phi_n = (p - 1) * (q - 1)
    e = 65537  # A common choice for the public exponent (e)

    # Calculate the private exponent (d)
    d = pow(e, -1, phi_n)

    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key

def encrypt_numeric(public_key, plaintext):
    n, e = public_key
    ciphertext = pow(plaintext, e, n)
    return ciphertext

def decrypt_numeric(private_key, ciphertext):
    n, d = private_key
    plaintext = pow(ciphertext, d, n)
    return plaintext

def encrypt_text(public_key, text):
    n, e = public_key
    # Convert the text to numeric values (e.g., using ASCII)
    numeric_values = [ord(char) for char in text]
    # Encrypt each numeric value
    encrypted_values = [pow(val, e, n) for val in numeric_values]
    return encrypted_values

def decrypt_text(private_key, encrypted_values):
    n, d = private_key
    # Decrypt each encrypted numeric value
    decrypted_values = [pow(val, d, n) for val in encrypted_values]
    # Convert back to text (e.g., using ASCII)
    decrypted_text = ''.join(chr(val) for val in decrypted_values)
    return decrypted_text

def getFactors(A):
    print("Prime Factorizing.....")
    end = (int)(math.sqrt(A)) + 1;
    for i in range(2, end):
        if A % i == 0:
            print(f"Prime Factors Are :  {i} , {A // i}")
            break
   
    print("_______________________________________________________")

if __name__ == "__main__":
    print("_________________________________________________________________")
    print("Let's Explore Cybersecurity -- RSA  Algorithm")
    print("_________________________________________________________________")
    public_key, private_key = generate_keypair()
    print("Public Key (n, e):", public_key)
    print("Private Key (n, d):", private_key)

    while True:
        print("_________________________________________________________________")
        print("Let's Explore Cybersecurity -- RSA  Algorithm")
        print("_________________________________________________________________")
        
        print("1. Encrypt Numeric Message")
        print("2. Decrypt Numeric Message")
        print("3. Encrypt Text Message")
        print("4. Decrypt Text Message")
        print("5. Find Prime Factors of Number")
        print("6. Exit")
        choice = input("Enter Choice Code: ")

        if choice == "1":
            numeric_message = int(input("Enter a numeric message to encrypt: "))
            ciphertext = encrypt_numeric(public_key, numeric_message)
            print("Encrypted Message:", ciphertext)
            print("_________________________________________________________________")
        elif choice == "2":
            ciphertext = int(input("Enter the numeric ciphertext to decrypt: "))
            plaintext = decrypt_numeric(private_key, ciphertext)
            print("Decrypted Message:", plaintext)
            print("_________________________________________________________________")
        elif choice == "3":
            text_message = input("Enter a text message to encrypt: ")
            encrypted_values = encrypt_text(public_key, text_message)
            print("Encrypted Message:", encrypted_values)
            print("_________________________________________________________________")
        elif choice == "4":
            encrypted_values = [int(val) for val in input("Enter the encrypted values (separated by spaces): ").split()]
            decrypted_text = decrypt_text(private_key, encrypted_values)
            print("Decrypted Message:", decrypted_text)
            print("_________________________________________________________________")
        elif choice == "5":
            number = int(input("Enter a number to find its prime factors: "))
            getFactors(number)
        elif choice == "6":
            exit(0)
        else:
            print("Invalid Input! Please enter a valid choice.")
