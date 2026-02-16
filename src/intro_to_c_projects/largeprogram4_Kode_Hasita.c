//Hasita Kode
//Dr. Steinberg
//COP 3223
//Large Program 4

#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    double price;
    int orders;
    int quantity;
    char name[26];
    char ingredients[101];

} sandwich_t;

void chomp(char word[]);
void toLowerStr(char *s);
int displayMenu();
void addSandwich(sandwich_t sandwich[], int *currentNumSandwich);
void removeSandwich(sandwich_t sandwich[], int *currentNumSandwich);
void orderSandwich(sandwich_t sandwich[], int *currentNumSandwich);
void displaySandwich(sandwich_t sandwich[], int currentNumSandwich);
void restockSandwich(sandwich_t sandwich[], int *currentNumSandwich);

int main()
{
	//create all the variables
    int option;
    sandwich_t sandwich[5];
    int currentNumSandwich = 0;

    printf("Welcome to THE ULTIMATE Sandwich Manager System!\n");
	
	//use a do while loop so it runs at least once
    do
    {	
		//call the displayMenu function
        option = displayMenu();
		
		//use a switch to traverse through the different options
        switch(option)
        {
            case 1:
                addSandwich(sandwich, &currentNumSandwich);
                break;

            case 2:
                removeSandwich(sandwich, &currentNumSandwich);
                break;

            case 3:
                orderSandwich(sandwich, &currentNumSandwich);
                break;

            case 4:
                restockSandwich(sandwich, &currentNumSandwich);
                break;

            case 5:
                displaySandwich(sandwich, currentNumSandwich);
                break;

            case 6:
                printf("Thank you for using the system!\n");
                return 0;

            default:
                printf("Please select from the following options!\n");
        }

    } while(option != 6);

    return 0;
}

int displayMenu()
{
    int option;
	//display all the options
    printf("[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
    printf("Please select one of the options you would like to do\n");
    printf("------------------------------------------------------------------\n");
    printf("1: Add sandwich to the shop.\n");
    printf("2: Remove sandwich from the shop.\n");
    printf("3: Order sandwich from the shop.\n");
    printf("4: Restock sandwich in the shop.\n");
    printf("5: Display all sandwiches.\n");
    printf("6: Close system manager.\n");
    printf("Entered option: ");
	
    scanf("%d", &option);
    while(getchar() != '\n');//clear the buffer

    printf("[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
	//return the option
    return option;
}

void displaySandwich(sandwich_t sandwich[], int currentNumSandwich)
{
	//make sure there are actually sandwiches in the array
    if(currentNumSandwich == 0)
    {
        printf("Please add a sandwich to display.\n");
        return;
    }
	
	//use a for loop and print out the components
    for(int i = 0; i < currentNumSandwich; i++)
    {
        printf("Name: %s\n", sandwich[i].name);
        printf("Recipe: %s\n", sandwich[i].ingredients);
        printf("Price: %.2lf\n", sandwich[i].price);
        printf("Number of times people ordered this sandwich: %d\n", sandwich[i].orders);
        printf("In stock: %d\n", sandwich[i].quantity);
        printf("[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
    }
}

void addSandwich(sandwich_t sandwich[], int *currentNumSandwich)
{
	//make sure the array isn't full
    if(*currentNumSandwich == 5)
    {
        printf("You have reached the maximum amount of sandwiches you can have :(\n");
        printf("Please remove a sandwich\n");
        return;
    }
	
	//declare the struct
    sandwich_t newSandwich;

    printf("Please enter the following information carefully for the new sandwich.\n");
	
	//use fgets for the name and the ingredients
    printf("Enter the name of the sandwich: ");
    fgets(newSandwich.name, sizeof(newSandwich.name), stdin);
    chomp(newSandwich.name);

    printf("Enter what goes in the sandwich: ");
    fgets(newSandwich.ingredients, sizeof(newSandwich.ingredients), stdin);
    chomp(newSandwich.ingredients);
	
	//make sure the price is a possitive number
    double checkPrice;
    printf("Enter the price of the sandwich: ");
    scanf("%lf", &checkPrice);
    while(getchar() != '\n'); // flush input

    if(checkPrice < 0)
    {
        printf("Please enter a valid number to set as the price\n");
        return;
    }

    newSandwich.price = checkPrice;
    newSandwich.orders = 0;
    newSandwich.quantity = 2;

    sandwich[*currentNumSandwich] = newSandwich;
	//increment the number of sandwiches
    (*currentNumSandwich)++;
}

void removeSandwich(sandwich_t sandwich[], int *currentNumSandwich)
{
	//make sure there are actually sandwiches in the system.
    if(*currentNumSandwich == 0)
    {
        printf("You currently have no sandwiches.\n");
        printf("Please add a sandwich to remove.\n");
        return;
    }
	
	//print out all the sandwich names
    for(int i = 0; i < *currentNumSandwich; i++)
    {
        printf("Name: %s\n", sandwich[i].name);
    }

    char tempUserRemoveSandwich[26];
    printf("Please select the name of the sandwich you would like to remove: ");
	//use fgets to get the name of the sandwich
    fgets(tempUserRemoveSandwich, sizeof(tempUserRemoveSandwich), stdin);
    chomp(tempUserRemoveSandwich);
	
	//create a variable for the index to be removed
    int removeIndex = -1;
	
	//traverse through the loop and set the sandwich to be removed to that index
    for(int i = 0; i < *currentNumSandwich; i++)
    {
        if(strcmp(tempUserRemoveSandwich, sandwich[i].name) == 0)
        {
            removeIndex = i;
            break;
        }
    }

    if(removeIndex == -1)
    {
        printf("The name you entered is not currently on the list of sandwiches.\n");
        return;
    }
	
	//shift all the elements to the left
    for(int i = removeIndex; i < *currentNumSandwich - 1; i++)
    {
        sandwich[i] = sandwich[i + 1];
    }
	
	//decrement the current number of sandwiches
    (*currentNumSandwich)--;
}

void orderSandwich(sandwich_t sandwich[], int *currentNumSandwich)
{
    char userOrder[26];
	
	//make sure there are actually sandwiches in the system.
    if(*currentNumSandwich == 0)
    {
        printf("There are no sandwiches here to display.. please add a sandwich\n");
        return;
    }
	
	//call displaySandwich to display the sandwiches and their info
    displaySandwich(sandwich, *currentNumSandwich);

    printf("Please enter the name of the sandwich you would like to order: ");
    fgets(userOrder, sizeof(userOrder), stdin);
    chomp(userOrder);
	
	//convert the input into lowercase using MY OWN function
    char loweredInput[26];
    strcpy(loweredInput, userOrder);
    toLowerStr(loweredInput);
	
	//traverse through the system and find a match
    for(int i = 0; i < *currentNumSandwich; i++)
    {
        char loweredSandwich[26];
        strcpy(loweredSandwich, sandwich[i].name);
        toLowerStr(loweredSandwich);
		
		//make sure they actually match
        if(strcmp(loweredInput, loweredSandwich) == 0)
        {
            printf("Processing your request for %s\n", sandwich[i].name);
			
			//make sure the sandwich is in stock
            if(sandwich[i].quantity > 0)
            {	
				//decrement the sandwich quantity and increment the orders of it
                sandwich[i].quantity--;
                sandwich[i].orders++;

                printf("Your order was processed succesfully!\n");
                printf("You will be billed %.2lf. You can pay at the register.\n", sandwich[i].price);
            }
            else
            {
                printf("Sorry %s is out of stock.\n", sandwich[i].name);
                printf("Please restock the sandwich and order again.\n");
            }

            return;
        }
    }

    printf("Please enter a valid sandwich name.\n");
}

void restockSandwich(sandwich_t sandwich[], int *currentNumSandwich)
{
    char restockSandwichName[26];
	
	//make sure there are actually sandwiches in the system
    if(*currentNumSandwich == 0)
    {
        printf("Please add a sandwich first.\n");
        return;
    }
	
	//call displaySandwich to show sandwiches with info
    displaySandwich(sandwich, *currentNumSandwich);

    printf("Please enter the name of the sandwich you would like to restock: ");
    fgets(restockSandwichName, sizeof(restockSandwichName), stdin);
    chomp(restockSandwichName);
	
	//turn the input into lowercase
    char loweredInput[26];
    strcpy(loweredInput, restockSandwichName);
    toLowerStr(loweredInput);
	
	//traverse through the loop to find a match
    for(int i = 0; i < *currentNumSandwich; i++)
    {
        char loweredSandwich[26];
        strcpy(loweredSandwich, sandwich[i].name);
        toLowerStr(loweredSandwich);
		
		//make sure the input actually matches
        if(strcmp(loweredInput, loweredSandwich) == 0)
        {
            int numRestock;
            printf("Enter the number of sandwiches to restock: ");
            scanf("%d", &numRestock);
            while(getchar()!='\n');
			
			if(numRestock > 0)
			{
				//add the number to the quantity of the sandwich
				sandwich[i].quantity += numRestock;
			}
			else 
			{
				printf("Please enter a positive number.\n");
				return;
			}

            printf("There are now %d %s (s).\n", sandwich[i].quantity, sandwich[i].name);
            return;
        }
    }

    printf("Please enter a valid sandwich name.\n");
}

void toLowerStr(char *s)
{	
	// Loop through each char and convert it into lowercase.
    // Stops when s[i] is null.
    for(int i = 0; s[i]; i++)
    {
        s[i] = tolower(s[i]);
    }
}

void chomp(char word[])
{
    if(word[strlen(word) - 1] == '\n')
        word[strlen(word) - 1] = '\0';
}

//Thank you Dr. Steinberg and Hudson for making my first college course so enjoyable!
