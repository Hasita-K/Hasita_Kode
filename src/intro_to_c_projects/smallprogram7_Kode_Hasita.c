//Hasita Kode
//Dr. Steinberg
//COP 3223 Section
//Small Program 7

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//function prototypes for shell functions
void shellFunctionProblem1();
void shellFunctionProblem2();
void shellFunctionProblem3();
void shellFunctionProblem4();

//function prototypes for small program functions
void lastWordLength(char sentence []);
void truncateSentence(char sentence [], int k);
int strongPasswordCheck(char psw []);
int romanNumber(char roman_num []);

//function prototype for provided functions
void chomp(char word []);
void clearBuffer();

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
        
            shellFunctionProblem2();
            break;
            
        case '3':
        
            shellFunctionProblem3();
            break;
            
        case '4':
        
            shellFunctionProblem4();
            break;
        
        default:
            printf("ERROR!\n");
    }
        
    return 0;
}

void shellFunctionProblem1()
{
	//create the array
    char sentence [501];
	
	//get the user input
	printf("Enter a sentence: ");
	fgets(sentence, sizeof(sentence), stdin);
	chomp(sentence);
	lastWordLength(sentence);
}

void shellFunctionProblem2()
{
	//create the array
	char sentence[501];
	//declare the variable 
	int numTruncate;
	
	//get the user sentence
	printf("Enter a sentence: ");
	fgets(sentence, sizeof(sentence), stdin);
	chomp(sentence);
	
	printf("Truncate sentence to how many words: ");
	scanf("%d", &numTruncate);
	
	//call the function
	truncateSentence(sentence, numTruncate);
}

void shellFunctionProblem3()
{
	//create the array
    char pswd[101];
	
	//get the user input
	printf("Enter your password: ");
	fgets(pswd, sizeof(pswd), stdin);
	chomp(pswd);
	
	//function call
	int result = strongPasswordCheck(pswd);
	
	//if else statement to display the respective statement. 
	if(result == 1)
	{
		printf("%s is a strong password.\n", pswd);
	}
	else
	{
		printf("%s is not a strong password.\n", pswd);
	}
}

void shellFunctionProblem4()
{
	//create the array
    char roman_num[31];
	
	//get the user input
	printf("Enter a roman numeral: ");
	fgets(roman_num, sizeof(roman_num), stdin);
	chomp(roman_num);
	
	//call the function
	int result = romanNumber(roman_num);
	
	printf("%s = %d\n", roman_num, result);
	

	
}

void lastWordLength(char sentence [])
{
	//declare and assign the variables
    int stringLength = strlen(sentence);
	int i = stringLength - 1;
	int lastWordLength = 0;
	
	//use a while loop to skip over spaces and punctuation
	while (i >= 0 && (isspace(sentence[i]) || ispunct(sentence[i])))
        i--;
	
	//count the characters in the last word to get the length.
	while (i>=0 && !isspace(sentence[i]))
	{
		lastWordLength++;
		i--;
	}
	
	
	printf("Length of last word in \"%s\" is %d.\n", sentence, lastWordLength);
	
	
}

void truncateSentence(char sentence [], int k)
{
	//declare and assign all the variables
	int numSpaces = 0;
	int i = 0;
	
	//use a while loop to iterate through the sentence
	while(sentence[i] != '\0')
	{
		
		if(sentence[i] == ' ')
		{
			numSpaces++;
		}
		//make it stop when you reach to the kth word
		if(numSpaces == k)
		{
			break;
		}
		i++;
	}
	
	//reasign the last character to null to terminate
	sentence[i] = '\0';
	
	printf("Truncated sentence is \"%s\"\n", sentence);
	
    
}

int strongPasswordCheck(char pswd [])
{
	//declare all the variabels
    int sizePswd = 0;
	int numLowerCase = 0;
	int numUpperCase = 0;
	int numDigit = 0;
	int i = 0;
	
	//use a while loop to traverse and update the num variables.
	while(pswd[i] != '\0')
	{
		
		if (isupper(pswd[i]))
			numUpperCase++;
		
		if (islower(pswd[i]))
			numLowerCase++;
		
		if (isdigit(pswd[i]))
			numDigit++;		

		sizePswd++;
		
		i++;
	}	
	
	//make sure the password is greater than 6 and less than 20 chars
	if (sizePswd < 6 || sizePswd > 20)
		return 0;
	
	//use a for loop to turn consecutive chars into the same case
	for (int i = 0; i < sizePswd - 2; i++)
	{
		char char1 = tolower(pswd[i]);
		char char2 = tolower(pswd[i + 1]);
		char char3 = tolower(pswd[i + 2]);
		
		//if the consecutive chars are the same then return 0
		if (char1 == char2 && char2 == char3)
			return 0;
		
	}
	
	//make sure the nums of digits/cases are the amount required by the problem
	if (numUpperCase >= 2 && numLowerCase >= 1 && numDigit >= 3)
		return 1;
	else 
		return 0;
	
	
}

int romanNumber(char roman_num [])
{
	//declare all the variables
    int value = 0;
	int totalValue = 0;
	int prevValue = 0;
	
	
	//Genius idea - Start from the BACK! 
	//if the value of num is smaller than the one it just saw THEN subtract
	//else just add
	for(int i = strlen(roman_num) - 1; i >= 0; i--)
	{
		//assign all the roman numerals their values
		if(roman_num[i] == 'I')
			value = 1;
		else if(roman_num[i] == 'V')
			value = 5;
		else if(roman_num[i] == 'X')
			value = 10;
		else if(roman_num[i] == 'L')
			value = 50;
		else if(roman_num[i] == 'C')
			value = 100;
		else if(roman_num[i] == 'D')
			value = 500;
		else if(roman_num[i] == 'M')
			value = 1000;
		
		//implement the if else statements
		if(value < prevValue)
			totalValue = totalValue - value;
		else 
			totalValue = totalValue + value;
		
		//update the previous value
		prevValue = value;
	
	}
	
	//return the total to the shell function
	return totalValue;
	
		
}

void chomp(char word [])
{
    if(word[strlen(word) - 1] == '\n')
        word[strlen(word) - 1] = '\0';
}

void clearBuffer()
{
    while(getchar() != '\n');
}