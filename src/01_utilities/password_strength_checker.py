import string
import random
import getpass

def check_password_strength(password):
    issues = []
    if len(password) <= 8:
        issues.append("Too short (minimum 8 characters)")
    if not any(c.islower() for c in password):
        issues.append("Missing lower case letter")
    if not any(c.isupper() for c in password):
        issues.append("Missing upper case letter")
    if not any (c.isdigit() for c in password):
        issues.append("Missing digit")
    if not any (c in string.punctuation for c in password):
        issues.append("Missing a Special Character")
    return issues

def generate_strong_password(length=12):
    chars = string.ascii_letters + string.digits + string.punctuation
    
    return " ".join(random.choice(chars) for _ in range(length))

password = getpass.getpass("Enter a password: ")
issues = check_password_strength(password)

if not issues:
    print("Strong password! You are good to go")
else:
    print("You got weak password")
    for issue in issues:
        print(f"- {issue}")

suggestion = generate_strong_password()
print("\n Suggesting you a strong password")
print(suggestion)