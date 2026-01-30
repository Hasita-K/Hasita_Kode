//Hasita Kode
//Dr. Steinberg
//COP 3223 Section 00343
//Large Program 2

#include <stdio.h>

void greeting();
void order(double *balance);
void viewAccount(double *balance);
void transaction(double *balance, double price);
void reload(double *balance);
void displayMenu();

int main()
{
	greeting();
	//declare variables
	char option;
	double balance = 0.0;
	
	//use a do while loop so this runs at least once
	do {
		printf("Please select one of the following options.\n");
		printf("O: Order\n");
		printf("V: View Account Summary\n");
		printf("D: Display Menu\n");
		printf("R: Reload Account\n");
		printf("E: Exit\n");
		scanf(" %c", &option);  
	
		switch(option)
		{
			case 'O':
			order(&balance);
			break;
		
			case 'o':
			order(&balance);
			break;
		
			case 'V':
			viewAccount(&balance);
			break;
		
			case 'v':
			viewAccount(&balance);
			break;
		
			case 'D':
			displayMenu();
			break;
		
			case 'd':
			displayMenu();
			break;
		
			case 'R':
			reload(&balance);
			break;
		
			case 'r':
			reload(&balance);
			break;
		
			case 'E':
			printf("Thank you for visiting Knightro's Coffee Shop!\n");
			printf("You have $%.2lf in your account.\n", balance);
			printf("Have a great day!\n");
			printf("Go Knights, Charge On!\n");
			break;
		
			case 'e':
			printf("Thank you for visiting Knightro's Coffee Shop!\n");
			printf("You have $%.2lf in your account.\n", balance);
			printf("Have a great day!\n");
			printf("Go Knights, Charge On!\n");
			break;
		
			default:
			printf("Invalid option, please select from one of the options above!\n");
			break;
		}
	} while (option != 'E' && option != 'e');  

	return 0; 
}

void greeting()
{
	printf("Welcome to the Knightro's Coffee Shop!\n");
	printf("We serve delicious coffee and snacks!\n");
	printf("How can we help you today?\n");
	printf("***********************************************\n");
	
}

void order(double *balance)
{
	//declare variables
	int cafeOption;
	double price = 0.0;
	
	//print statements
	printf("You have selected the Order Option.\n");
	printf("***********************************************\n");
	
	printf("Here are the options!\n");
	printf("***********************************************\n");
	//call the display menu function to show menu
	displayMenu();
	printf("What would you like today?\n");
	scanf("%d", &cafeOption);
	
	//use a switch statement to traverse through the options
	switch(cafeOption)
	{
		case 1:
		printf("Hot Coffee has been selected. Total cost is: $3.53\n");
		price = 3.53;
		break;
		
		case 2:
		printf("Iced Coffee has been selected. Total cost is: $4.20\n");
		price = 4.20;
		break;
		
		case 3:
		printf("Hot Latte has been selected. Total cost is: $3.13\n");
		price = 3.13;
		break;
		
		case 4: 
		printf("Iced Latte has been selected. Total cost is: $4.12\n");
		price = 4.12;
		break;
		
		case 5:
		printf("Bagel (including cream cheese) has been selected. Total cost is $3.99\n");
		printf("Beginning Transaction Process.\n");
		price = 3.99;
		break;
		
		case 6: 
		printf("Big Scone has been selected. Total cost is: $4.99\n");
		price = 4.99;
		break;
		
		case 7: 
		printf("Frozen Coffee has been selected. Total cost is: $5.03\n");
		price = 5.03;
		break;
		
		case 8: 
		printf("Bottle Water has been selected. Total cost is: $1.50\n");
		price = 1.50;
		break;
		
		default: 
		printf("Invalid option, please select from the options above!\n");
		break;
	}
	
	//for transaction call the transaction function and pass the balance and price through
	printf("Beginning Transaction Process.\n");
	transaction(balance, price);
	printf("***********************************************\n");
	return;
}

void viewAccount(double *balance)
{
	printf("You selected View Account Summary Option.\n");
	printf("***********************************************\n");
	
	printf("Here is your current Account Balance.\n");
	//for this print statement make sure you have the value from the balance pointer
	printf("You have %.2lf in your account.\n", *balance);
	printf("***********************************************\n");
	
	return;
}

void transaction(double *balance, double price)
{
	//make the condition so that the balance is less than the price of the item
	while (*balance < price)
    {
        printf("You do not have enough in your account.\n");
        printf("Please reload your account balance.\n");
        printf("*****************************************************\n");
        reload(balance);
    }
	
	//print statements for when you do have enough balance to make the purchase
    printf("Your account balance before official transaction: $%.2lf\n", *balance);
    printf("Billing $%.2lf to your account.\n", price);
	//update the value from the balance POINTER
    *balance = *balance - price;
    printf("Transaction was successful!\n");
    printf("You have now $%.2lf in your account balance.\n", *balance);
    printf("*****************************************************\n");
	
	return;
}

void reload(double *balance)
{
	//declare a variable for storing the user's reload choice
	int reloadOption;
	
	//print statements to prompt the user
	printf("How much would you like to reload to your account?\n");
	printf("1: $1:00\n");
	printf("2: $5:00\n");
	printf("3: $10.00\n");
	scanf("%d", &reloadOption);
	
	//use a switch statement to traverse through the different options
	switch(reloadOption)
	{
		case 1:
		*balance = *balance + 1.00;
		printf("$1.00 has been added to your account successfully!\n");
		break;
		
		case 2: 
		*balance = *balance + 5.00;
		printf("$5.00 has been added to your account successfully!\n");
		break;
		
		case 3: 
		*balance = *balance + 10.00;
		printf("$10.00 has been added to your account successfully!\n");
		break;
		
		default:
		printf("Invalid Input, please pick from the options above.\n");
		break;
		
	}
	return;
	
}

void displayMenu()
{
	//use the print statements to show the menu
	printf("You selected the Display Menu Option!\n");
	printf("Here are the options!\n");
	printf("***********************************************\n");
	printf("1. Hot Coffee							$3.53\n");
	printf("2. Iced Coffee 							$4.20\n");
	printf("3. Hot Latte 							$3.13\n");
	printf("4. Iced Latte							$4.12\n");
	printf("5. Bagel (includes cream cheese)		 		$3.99\n");
	printf("6. Big Scone 							$4.99\n");
	printf("7. Frozen Coffee 						$5.03\n");
	printf("8. Bottle Water 						$1.50\n");
	printf("***********************************************\n");
	return;
	
}


	
	

