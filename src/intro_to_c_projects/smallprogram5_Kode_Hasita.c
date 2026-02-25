//Hasita Kode
//Dr. Steinberg
//COP 3223 Section 00343
//Small Program 5

#include <stdio.h>
#include <math.h>

//function prototypes for shell functions
void shellFunctionProblem1();

//function prototypes for small program functions
void pickButton(int * selection); 
void match(); 
void blockbuster(); 
void numberFacts(); 

int main(int argc, char* argv[])
{
    /* 
       DO NOT CHANGE ANYTHING OR ADD 
       ANYTHING INTO THE MAIN FUNCTION!
    */
    switch(*argv[1])
    {
        case '1':
        
            shellFunctionProblem1();
            break;
            
        case '2':
        
            match();
            break;
            
        case '3':
        
            blockbuster();
            break;
            
        case '4':
        
            numberFacts();
            break;
        
        default:
            printf("ERROR!\n");
    }
        
    return 0;
}

void shellFunctionProblem1()
{
	//create a variable for the button picked
	int selection;
	
	//function definition for problem 1 
	pickButton(&selection);
	
	//use an if else statement to traverse through the button options
	if(selection == 1)
	{
		printf("Blue Button Selected!\n");
	}
	else if(selection == 2)
	{
		printf("Green Button Selected!\n");
	}
	else if(selection == 3)
	{
		printf("Yellow Button Selected!\n");
	}
	else if(selection == 4)
	{
		printf("Red Button Selected!\n");
	}
	else if(selection == 5)
	{
		printf("Gold Button Selected!\n");
	}
	else if(selection == 6)
	{
		printf("Black Button Selected!\n");
	}
	else if(selection == 7)
	{
		printf("White Button Selected!\n");
	}
	else
	{
		printf("Invalid Button Selected!\n");
	}
	
} 

void pickButton(int * selection)
{
   
	
	//all the print statements
	printf("Choose a button.\n");
	printf("1. Blue Button\n");
	printf("2. Green Button\n");
	printf("3. Yellow Button\n");
	printf("4. Red Button\n");
	printf("5. Gold Button\n");
	printf("6. Black Button\n");
	printf("7. White Button\n");
	printf("Selection: ");
	
	//collect the user's selection with the scanner
	scanf("%d", selection);
	
	
}

void match()
{
	
	//open these three files for reading
    FILE *fptr1 = fopen("grades1.txt", "r");
	FILE *fptr2 = fopen("grades2.txt", "r");
	FILE *fptr3 = fopen("grades3.txt", "r");
	
	//declare all the grade variables
	char grade1;
	char grade2;
	char grade3;
	
	
	//for  while loop, make sure they all return 1 to show it works
	while(fscanf(fptr1, " %c", &grade1) == 1 &&
		  fscanf(fptr2, " %c", &grade2) == 1 &&
		  fscanf(fptr3, " %c", &grade3) == 1)
	{
		if(grade1 != grade2 || grade2 != grade3 || grade3 != grade1)
		{
			printf("No Match!\n");
			return;
			
		}
		
	}
	
	printf("Match!\n");
	//close the files :)
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
		
}

void blockbuster()
{
	//declare all the variables
	int customer;
	int videos;
	double cost;
	double profit = 0.0;
	
	printf("Retrieving the Records from today's sale!\n");
	
	//open the reading sales and writting recordsales file
	FILE *input = fopen("sales.txt", "r");
	FILE *recordsale = fopen ("recordsales.txt", "w");
	while (fscanf(input, "%d %d", &customer, &videos) == 2)
	{
		cost = 2.99 * videos;
		profit = profit + cost;
		
	
		printf("Customer: %d\t", customer);
		printf("Spent: $%.2lf\n", cost);
		
		//print statements for teh recordsales text file
		fprintf(recordsale, "Customer: %d\t", customer);
		fprintf(recordsale, "Spent: $%.2lf\n", cost);
		
		
			
	
	}
	printf("-----------------------------\n");
	fprintf(recordsale, "-----------------------------\n");
	
	
	
	printf("$%.2lf was made today.\n", profit);
	fprintf(recordsale,"$%.2lf was made today.\n", profit);
	
	//close the files!
	fclose(input);
	fclose(recordsale);
	
    
}

void numberFacts()
{
	//declare the num for scanner
    int num;

    FILE *fptr = fopen("numfact.txt", "w");

    printf("Number\tPart A\tPart B\tPart C\n");
    fprintf(fptr, "Number\tPart A\tPart B\tPart C\n");

    do
    {
        printf("Enter a positive integer: ");
        scanf("%d", &num);
		
		// break if user enters 0 or negative number
        if (num <= 0)
		{
            break;
		}

        // print the number being tested
        printf("%d\t", num);
        fprintf(fptr, "%d\t", num);

        //check if dividing by 7, 11, or 13 gives a remainder of 0
        if (num % 7 == 0)
        {
            printf("Yes!\t");
            fprintf(fptr, "Yes!\t");
        }
        else if (num % 11 == 0)
        {
            printf("Yes!\t");
            fprintf(fptr, "Yes!\t");
        }
        else if (num % 13 == 0)
        {
            printf("Yes!\t");
            fprintf(fptr, "Yes!\t");
        }
        else
        {
            printf("No!\t");
            fprintf(fptr, "No!\t");
        }

        //check if dividing by 2 gives a remainder of 0
        if (num % 2 == 0)
        {
            printf("Even\t");
            fprintf(fptr, "Even\t");
        }
        else
        {
            printf("Odd\t");
            fprintf(fptr, "Odd\t");
        }

        // I'm creating primeChecker to check for divisibility
        int primeChecker = 2;
		//I'm creating isPrime and assuming the number is prime for now
        int isPrime = 1; //so 1 means that the number is prime

        if (num == 1)
            isPrime = 0;//0 means the number isn't prime
        else
        {
            for (primeChecker = 2; primeChecker <= sqrt(num); primeChecker++)
            {
                if (num % primeChecker == 0)
                {
                    isPrime = 0;
                    break;
                }
            }
        }

        if (isPrime == 1)
        {
            printf("Prime\n");
            fprintf(fptr, "Prime\n");
        }
        else
        {
            printf("Composite\n");
            fprintf(fptr, "Composite\n");
        }

    } while (num > 0);
	
	//close the file
    fclose(fptr);
}