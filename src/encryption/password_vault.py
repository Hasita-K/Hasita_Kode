import base64
import os

VAULT_FILE = "vault.txt"

def encode(text):
    return base64.b64encode(text.encode()).decode()

def decode(text):
    return base64.b64decode(text.encode()).decode()


def password_strength(password):
    length = len(password)
    has_upper = any(c.isupper() for c in password)
    has_digit = any(c.isdigit() for c in password)
    has_special = any(c in "!@#$%^&*().,<>" for c in password)

    score = sum([length >= 8, has_upper, has_digit, has_special])
    return ["Weak", "Medium", "Strong", "Very Strong"][min(score, 3)]

def add_credential():
    website = input("Website: ").strip()
    username = input("Username: ").strip()
    password = input("Password: ").strip()

    strength = password_strength(password)

    line = f"{website}||{username}||{password}"
    encoded_line = encode(line)

    with open(VAULT_FILE, "a", encoding="utf-8") as f:
        f.write(encoded_line)

    print("✅ Credential Saved")

def view_credentials():
    if not os.path.exists(VAULT_FILE):
        print("File not Found")
        return
    
    with open(VAULT_FILE, "r", encoding = "utf-8") as f:
        for line in f:
            decoded = decode(line.strip())
            website, username, password = decoded.split("||")
            hidden_password = '*' * len(password)
            print(f"{website}  | {username} | {password}")

def update_password():
    if not os.path.exists(VAULT_FILE):
        print("No vault file found")
        return 

    term = input("Enter the website credentials to update: ").strip().lower()
    updated = False
    new_lines = []

    with open(VAULT_FILE, "r", encoding = "utf-8") as f:
        for line in f:
            decoded = decode(line.strip())
            website, username, password = decoded.split()

            if website.lower() == term:
                new_password = input("Enter the new password: ").strip()
                decoded = f"{website} || {username} || {new_password}"
                updated = True
    
    if not updated:
        print("No matching website found")
        return
    
    with open(VAULT_FILE, "w", encoding = "utf-8") as f:
        f.writelines(new_lines)
    
    print("🔄️ Password updated successfully")
    

def main():
    while True:
        print("\n 🔒 Credential Manager")
        print("1. Add Credential")
        print("2. View Credential")
        print("3. Update password")
        print("4. Exit")

        choice = input("Enter your choice: ")

        match choice:
            case "1":
                add_credential()
            case "2":
                view_credentials()
            case "3":
                update_password()
            case "4":
                break
            case _:
                print("Invalid Choice")

if __name__ == "__main__":
    main()