//Hasita Kode
//Dr. Steinberg
//COP 3223
//Large Program 3

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void maskWord(char starword[], int size); //mask word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurencesInWord(char userguess, char answer[]); //times letter occurs in a word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
int guessTheWord(char answer[]); //guess the word
void playAgain(int *play); //ask user to play again

int main()
{
	//all the print statements for the main menu
	printf("Welcome to the Hangman Game\n");
	printf("----------------------------------------------------\n");
	printf(" \n");
	printf("Here are the rules: \n");
	printf("I will provide you with a set of * characters for each round\n");
	printf("Each * represents a character in the english alphabet.\n");
	printf("You must figure out each letter of the missing word.\n");
	printf("For every correct letter guessed, I will reveal its place in the word.\n");
	printf("Each mistake will result in a strike\n");
	printf("6 strikes will result in a loss in that round\n");
	printf("Are you ready? Here we go!\n");
	printf("----------------------------------------------------\n");
	
	FILE *fptr = fopen("words.txt", "r");
	
	if (fptr != NULL)
	{
		int play = 1;
		char answer[21];
		// Read one word at a time 21 chars with the null
		while (play == 1 && fscanf(fptr, "%20s", answer) != EOF)
		{
			//declare the masked version of the word array
			char starword[21];
			
			//call maskword to star the characters in the array
			maskWord(starword, strlen(answer));
			
			printf("New Round: Here's your word\n");
			printf("%s\n", starword);
			
			//calll playRound to actually play the round of hangman
			int result = playRound(starword, answer);
			
			//use the returned int from playRound to display message
			if(result == 1)
				printf("WHOOP WHOOP YOU WON!\n");
			else
				printf("oh no you lost... Skill Issue (; \n");
			
			//ask the user to play again
			playAgain(&play);
			
			if(play == 0)
				break;
			
			printf("----------------------------------------------------\n");
		}
	}
	else 
		printf("Error opening file\n");
	
	//close the file pointer
	fclose(fptr);
	printf("Thanks for playing :3\n");
	
}


int playRound(char starword[], char answer[])
{
	//create and initialize all the variables
	int strikes = 0;
	int correctConsecutiveGuess = 0;
	char userGuess;
	char guessed[50] = ""; 
	
	//use this to find the length of the word
	int wordSize = strlen(answer);
	
	printf("Welcome to the Round :33\n");
	printf("The size of the word has %d letters.\n", wordSize);
	
	while (strikes < 6)
	{
		printf("You currently have %d strike(s).\n", strikes);
		printf("Letter(s) you have guessed: %s\n", guessed);
		printf("%s\n", starword);
		
		printf("Enter your guess: ");
		//make sure the scanf works, if not clear the buffer
		if (scanf(" %c", &userGuess) != 1) 
		{
			
			while (getchar() != '\n');
			{
				printf("Invalid input. Try again D:<\n");
			}
			continue;
		}
		
		//make sure the user's input is an actuall letter
		if(!isalpha(userGuess))
		{
			printf("You did not enter a letter from the alphabet >:(\n");
			continue;
		}
		
		userGuess = tolower(userGuess);

		//make sure there aren't any duplicate guesses by the user
		if (strchr(guessed, userGuess) != NULL)
		{
			printf("You already guessed the letter %c (0-0)\n", userGuess);
			continue;
		}
		
		//add the new guessed letter to the guessed array list to keep track
		int guessLength = strlen(guessed);
		if (guessLength < (int)sizeof(guessed) - 1) 
		{
			guessed[guessLength] = userGuess;
			guessed[guessLength + 1] = '\0';//make the last index the null character
		} 
		else 
		{
			//just in case it gets overfilled!
			printf("Too many guesses recorded! (o~o)\n");
		}
		
		//call the occurencesInWord to count the occurencess of guessed letters
		int occurence = occurencesInWord(userGuess, answer);
		
		//if the guess is incorrect increment strikes and reset consecutive guesses.
		if(occurence == 0)
		{
			printf("The letter %c is NOT in the word (-_-)\n", userGuess);
			strikes++;
			correctConsecutiveGuess = 0;
		}
		else
		{
			printf("The letter %c is in the word :DD\n", userGuess);
			correctConsecutiveGuess++;
			
			//call updateStarWord to reveal the positions of the correctly guessed letters
			updateStarWord(starword, answer, userGuess);
			
			//if the user guesses the word correctly
			if(strcmp(starword, answer) == 0)
			{
				printf("Congratulations! You won! The word was %s. <[:D]-I-I\n", answer);
				return 1; //return 1 if the user wins
			}
			
			//give user the option to guess the entire word
			if(correctConsecutiveGuess >= 2)
			{
				int option = 0;
				printf("You have made %d consecutive correct guesses. >-<\n", correctConsecutiveGuess);
				printf("Would you like to guess the word?\n");
				printf("1: Yes\n");
				printf("2: No\n");
				
				//make sure the user's input is actually valid
				if (scanf("%d", &option) != 1) 
				{
					while (getchar() != '\n'); //clear the newline from input buffer
					option = 0;
					
				} 
				
				//if the user wants to guess the word
				if(option == 1)
				{
					if(guessTheWord(answer) == 1)
					{
						printf("You guessed correctly!!!! WHOOP WHOOP :D\n");
						return 1; //the user wins
					}
					else
					{
						printf("Incorrect, keep playing\n");
					}
				}
			}
			
		}
		
	}
	//display this if the user uses up all 6 strikes.
	printf("YOU LOST! The word was %s. :((\n", answer);
	return 0;
	
}


void maskWord(char starword[], int size)
{
	//iterate through the loop and turn every character into a star
	for (int i = 0; i < size; i++)
	{
		starword[i] = '*';
	}
	//add the null terminator at the end
	starword[size] = '\0';
	
}


int occurencesInWord(char userGuess, char answer[])
{
	int countOccurences = 0;
	
	//itterate through th eloop
	for(int i = 0; i < (int)strlen(answer); i++)
	{
		//if one of the characters is equal to the user's guess increment countOccurences
		if(tolower(answer[i]) == tolower(userGuess))
		{
			countOccurences++;
		}
	}
	
	return countOccurences;
}


void updateStarWord(char starword[], char answer[], char userguess)
{
	for(int i = 0; i < (int)strlen(answer); i++)
	{
		//if the guessed letter matches the answer, reveal that correct letter in masked word.
		if(tolower(answer[i]) == tolower(userguess))
		{
			starword[i] = answer[i];
		}
		
	}
}


void playAgain(int *play)
{
	int playAgain;
	
	//ask user if they'd like to play again
	printf("Would you like to play another round?\n");
	printf("1: Yes\n");
	printf("2: No\n");
	
	
	do
	{
		
		printf("Choice: ");
		
		//again make sure the user's input is valid
		if (scanf("%d", &playAgain) != 1) 
		{
			printf("Invalid input >:( Please enter 1 or 2.\n");
			
			while (getchar() != '\n'); //clear the newline
			continue;
		}
		if (playAgain == 1 || playAgain == 2) 
			break;
		
		
		printf("Please enter 1 for Yes or 2 for No.\n");
		
	} while(playAgain!= 1 && playAgain!= 2);
	
	//clear the newline in the input buffer so the next input works 
	while (getchar() != '\n');
	
	printf("Choice: %d\n", playAgain);
	
	if(playAgain == 1)
	{
		*play = 1;
	}
	else
	{
		*play = 0;
	}

}


int guessTheWord(char answer[])
{
	//use this array to store the user's whole guess 
	char userGuessInput[50];
	
	printf("Enter your complete word guess: ");
	scanf(" %49s", userGuessInput); //stopped at 49 to give room for the null character!
	
	//compare the user's guess to the correct answer
	if(strcmp(userGuessInput, answer) == 0)
		return 1;
	else 
		return 0;
}


//Hasita Kode
//Dr. Steinberg
//COP 3223
//Large Program 3

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void maskWord(char starword[], int size); //mask word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurencesInWord(char userguess, char answer[]); //times letter occurs in a word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
int guessTheWord(char answer[]); //guess the word
void playAgain(int *play); //ask user to play again

int main()
{
	printf("Welcome to the Hangman Game\n");
	printf("----------------------------------------------------\n");
	printf(" \n");
	printf("Here are the rules: \n");
	printf("I will provide you with a set of * characters for each round\n");
	printf("Each * represents a character in the english alphabet.\n");
	printf("You must figure out each letter of the missing word.\n");
	printf("For every correct letter guessed, I will reveal its place in the word.\n");
	printf("Each mistake will result in a strike\n");
	printf("6 strikes will result in a loss in that round\n");
	printf("Are you ready? Here we go!\n");
	printf("----------------------------------------------------\n");
	
	
	FILE *fptr = fopen("words.txt", "r");
	
	if (fptr != NULL)
	{
		int play = 1;
		char answer[21];
		while (fscanf(fptr, "%s", answer) != EOF)
		{
			char starword[21];
			maskWord(starword, strlen(answer));
			
			printf("New Round: Here's your word\n");
			printf("%s\n", starword);
			
			int result = playRound(starword, answer);
			
			if(result == 1)
				printf("WHOOP WHOOP YOU WON!\n");
			else
				printf("BOYYYYYY YOU SUCK \n");
			
			playAgain(&play);
			if(play == 0)
				break;
			
			printf("----------------------------------------------------\n");
		}
	}
	else 
		printf("Error oppening file");
	

	
	fclose(fptr);
	printf("Thanks for playing\n");
	
}

int playRound(char starword[], char answer[])
{
	int strikes = 0;
	int correctConsecutiveGuess = 0;
	char userGuess;
	char guessed[50] = "";
	
	int wordSize = strlen(answer);
	
	printf("Welcome to the Round!\n");
	printf("The size of the has %d letters.\n", wordSize);
	
	while (strikes < 6)
	{
		printf("You currently have %d strikes.\n", strikes);
		printf("Letter(s) you have guessed: %s\n", guessed);
		printf("%s\n", starword);
		
		
		printf("Enter your guess: ");
		scanf(" %c", &userGuess);
		
		if(!isalpha(userGuess))
		{
			printf("YOU NEED TO ENTER A LETTER BRO!!!!\n");
			continue;
		}
		
		userGuess = tolower(userGuess);
		
		int guessLength = strlen(guessed);
		guessed[guessLength] = userGuess;
		guessed[guessLength + 1] = '\0';
		
		int occurence = occurencesInWord(userGuess, answer);
		
		if(occurence == 0)
		{
			printf("The letter %c is not in the word.\n", userGuess);
			strikes++;
			correctConsecutiveGuess = 0;
		}
		else
		{
			
			printf("The letter %c is in the word.", userGuess);
			correctConsecutiveGuess++;
			updateStarWord(starword, answer, userGuess);
			
			if(strcmp(starword, answer) == 0)
			{
				printf("Congradulations! You won! The word was %s.\n", answer);
				return 1;
			}
			
			if(correctConsecutiveGuess >= 2)
			{
				int option;
				printf("You have made %d consecutive guesses.\n", correctConsecutiveGuess);
				printf("Would you like to guess the word?\n");
				printf("1: Yes\n");
				printf("2: No\n");
				scanf("%d", &option);
				
				if(option == 1)
				{
					if(guessTheWord(answer) == 1)
					{
						printf("You guessed correctly!!!! WHOOP WHOOP \n");
						return 1;
					}
					else
					{
						printf("Incorrect, keep playing\n");
					}
					
				}
			}
			
		}
		
	}
	printf("YOU LOST! The word was %s.\n", answer);
	return 0;
	
}

void maskWord(char starword[], int size)
{
	for (int i = 0; i < size; i++)
	{
		starword[i] = '*';
	}
	starword[size] = '\0';
	
}

int occurencesInWord(char userGuess, char answer[])
{
	int countOccurences = 0;
	
	for(int i = 0; i < strlen(answer); i++)
	{
		if(tolower(answer[i]) == tolower(userGuess))
		{
			countOccurences++;
		}
	}
	
	return countOccurences;
}


void updateStarWord(char starword[], char answer[], char userguess)
{
	for(int i = 0; i < strlen(answer); i++)
	{
		if(tolower(answer[i]) == tolower(userguess))
		{
			starword[i] = answer[i];
		}
		
	}
}


void playAgain(int *play)
{
	int playAgain;
	
	printf("Would you like to play another round?\n");
	printf("1: Yes\n");
	printf("2: No\n");
	scanf("%d", &playAgain);
	
	printf("Choice: %d\n", playAgain);
	
	if(playAgain == 1)
	{
		*play = 1;
	}
	else
	{
		*play = 0;
	}

}




int guessTheWord(char answer[])
{
	char userGuessInput[50];
	printf("Enter your complete word guess: ");
	scanf(" %s", userGuessInput);
	
	if(strcmp(userGuessInput, answer) == 0)
		return 1;
	else 
		return 0;
}

