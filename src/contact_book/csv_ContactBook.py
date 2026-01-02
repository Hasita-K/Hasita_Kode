import csv
import os

FILENAME = "contacts.csv"

if not os.path.exists(FILENAME):
    with open(FILENAME, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["Name", "Phone", "Email"])

def add_contact():
    name = input("Name: ").strip()
    phone = input("Phone: ").strip()
    email = input("Email: ").strip()

    #check for duplicates
    with open(FILENAME, "r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row["Name"].lower() == name.lower():
                print("Contact Name already Exists")
                return
    
    with open(FILENAME, "a", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow([name, phone, email])
        print("Contact added")

def view_contacts():
    with open(FILENAME, "r", encoding="utf-8") as f:
        reader = csv.reader(f)
        rows = list(reader)

        if len(rows) < 1:
            print("No Contacts found")
            return 
        
        print("\n Your Contacts: \n")
        
        for row in rows[1:]:
            print(f"{row[0]} | {row[1]} | {row[2]}")
        print()

def search_contact():
    term = input("Enter the Name to search: ").strip().lower()
    found = False

    with open(FILENAME, 'r', encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if term in row["Name"].lower():
                print(f"{row['Name']} | 📞 {row['Phone']}")
                found = True

    if not found:
        print("No matching contact found")


def update_contact():
    term = input("Enter the Name to update: ").strip().lower()
    found = False
    contacts = []

    with open(FILENAME, 'r', encoding = "utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if term == row["Name"].lower():
                print("Contact found. Enter new details: ")
                row["Name"] = input("New name: ").strip()
                row["Phone"] = input("New phone: ").strip()
                row["Email"] = input("New email: ").strip()
                found = True
            contacts.append(row)
    if found:
        with open(FILENAME, "w", encoding = "utf-8") as f:
            fieldnames = ["Name", "Phone", "Email"]
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(contacts)
        print("Contact updated successfully")
    else:
        print("No matching contact found.")
def main():

    while True:
        print("\n📗 Contact Book")
        print("1. Add Contact")
        print("2. View All Contacts")
        print("3. Search Contact")
        print("4. Exit")

        choice = input("Choose an option (1-4)").strip()

        if choice == "1":
            add_contact()
        elif choice == "2":
            view_contacts()
        elif choice == "3":
            search_contact()
        elif choice == "4":
            print("Thank you for using our software")
            break
        else:
            print("Invalid choice of number")

if __name__ == "__main__":
    main()