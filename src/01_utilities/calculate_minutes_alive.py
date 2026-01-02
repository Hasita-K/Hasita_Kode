def calculate_minutes(age_years):
    DAYS_IN_YEAR = 365.25
    HOURS_IN_DAY = 24
    MINUTES_IN_HOUR = 60

    total_days = age_years * DAYS_IN_YEAR
    total_hours = total_days * HOURS_IN_DAY
    total_minutes = total_hours * MINUTES_IN_HOUR

    return round(total_days), round(total_hours), round(total_minutes)

while True:
    try:
        age =  float(input("Enter your age in years: "))
        days, hours, minutes = calculate_minutes(age)

        print("\n You are approx: ")
        print(f" - {days} days old")
        print(f" - {hours} horus old")
        print(f" - {minutes} minutes old\n")

        again = input("Would you like to try again? (y/n)").strip().lower()

        if again != 'y':
            print("Goodbye!")
            break
        
    except:
        print("Please enter a valid number for age")