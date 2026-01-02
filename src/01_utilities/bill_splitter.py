num_people = int(input("How many people are there in the group? "))
names = []

def get_float(prompt):
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Please enter a valid number. ")

for i in range(num_people):
    name = input(f"Enter the name of person #{i+1}").strip()
    names.append(name)

total_bill = get_float("Enter the bill amount in number only")

share = round(total_bill/ num_people, 2)

print("\n" + "*" * 40)
print(f"Total bill: {total_bill}")
print(f"Each person owers {share}")

for name in names:
    print(f"{name} owes {share} rupees")