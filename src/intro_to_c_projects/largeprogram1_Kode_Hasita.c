//Hasita Kode
//Dr. Steinberg
//COP3223
//Large Program 1

#define ROUNDS 5
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void greeting();
void playRound(int round);
int pickOne();
int computerPick();
int battle(int player1, int player2);
void result(int player1, int player2);

int main()
{
	greeting();
	
	int seed;
	printf("Before we start, pick a number to determine how random I will be.\n");
	scanf("%d", &seed);
	srand(seed);
	printf("All set now!\n");
	
	for(int x = 0; x < ROUNDS; ++x)
	{
		printf("********************************************************\n");
		playRound(x + 1);
		printf("********************************************************\n");
	}
	printf("********************************************************\n");
	printf("Thank you for playing!\n");
	return 0;
}

void greeting()
{
	printf("********************************************************\n");
	printf("Welcome to rock paper scissors game!\n");
	printf("Here are the rules.\n");
	printf("You and I will get to choose rock, paper, or scissor.\n");
	printf("After we made a decision we will reveal it and determine the winner based on these rules.\n");
	printf("Rock beats Scissor!\n");
	printf("Paper beats Rock!\n");
	printf("Scissor beats Paper!\n");
	printf("If we both pick the same option, then it is a tie.\n");
	printf("Ready to play?... Here we go!\n");
	printf("********************************************************\n");
}

void playRound(int round)
{	
	//Print statements to start round
	printf("Welcome to a new round %d\n", round);
	printf("Best out of three... Let's go!\n");
	
	//declare and initialize wins for both players
	int p1wins = 0;
	int p2wins = 0;
	
	//Create a loop that stops when any player hits 3 wins. 
	while(p1wins != 3 && p2wins != 3)
	{
		//Call the pick one function for getting user input
		//Call the computerpick function for getting computer input
		//Call battle function to compare both values
		int p1Move = pickOne();
		int p2Move = computerPick();
		int winner = battle(p1Move, p2Move);
		
		//value of 1 is returned if player 1 wins, 2 is returned if player 2 wins
		//increment the wins by 1 at the end for the respective winner
		if(winner == 1)
			p1wins ++;
		else if (winner == 2)
			p2wins ++;
		
		printf("--- Current Score You: %d Computer %d ---\n", p1wins, p2wins);
	}
	
	result(p1wins, p2wins);
	printf("\n");
	
}

int pickOne()
{
	//declare player1
	int player1;
	
	
	//print out the options for the player to choose
	printf("1---Rock\n");
	printf("2---Paper\n");
	printf("3---Scissor\n");
	
	//use scanner to get user input
	printf("Make your selection: \n");
	scanf("%d", &player1);
	
	//let the user know they made an invalid input if they didn't choose 1, 2, or 3
	if (player1 != 3 && player1 != 2 && player1 != 1)
		printf("Someone made an invalid choice\n");
	
	//this is pass by valueing to battle 
	return player1;
}

int computerPick()
{
	
	int player2;
	//use the rand to get a range do (max - min + 1) + min
	player2 = rand() % (3 - 1 + 1) + 1;
	printf("I'm making my decision now...\n");
	return player2;
}

int battle(int player1, int player2)
{
	//Create if statements for each scenario (should be 9 total)
	
	//If it's a tie return 0
	//If player 1 wins, return 1
	//If player 2 wins return 2
	if (player1 == 1 && player2 == 1)
	{
		printf("Player 1 and Player 2 both used Rock!\n");
		printf("Draw!\n");
		return 0;
	}
	if (player1 == 1 && player2 == 2)
	{
		printf("Player 1 used Rock and Player 2 used Paper!\n");
		printf("Paper beats Rock!\n");
		return 2;
	}
	if (player1 == 1 && player2 == 3)
	{
		printf("Player 1 used Rock and Player 2 used Scissor!\n");
		printf("Rock beats Scissor!\n");
		return 1;
	}
	if (player1 == 2 && player2 == 1)
	{
		printf("Player 1 used Paper and Player 2 used Rock!\n");
		printf("Paper beats Rock!\n");
		return 1;
	}
	if (player1 == 2 && player2 == 2)
	{
		printf("Player 1 and Player 2 both used Paper!\n");
		printf("Draw!\n");
		return 0;
	}
	if (player1 == 2 && player2 == 3)
	{
		printf("Player 1 used Paper and Player 2 used Scissor!\n");
		printf("Scissor beats Paper!\n");
		return 2;
	}
	if (player1 == 3 && player2 == 1)
	{
		printf("Player 1 used Scissor and Player 2 used Rock!\n");
		printf("Rock beats Scissor!\n");
		return 2;
	}
	if (player1 == 3 && player2 == 2)
	{
		printf("Player 1 used Scissor and Player 2 used Paper!\n");
		printf("Scissor beats Paper!\n");
		return 1;
	}
	if (player1 == 3 && player2 == 3)
	{
		printf("Player 1 and Player 2 both used Scissor!\n");
		printf("Draw!\n");
		return 0;
	}
	
}

void result(int player1, int player2)
{
	//create an if else if statement with the 3 different scenarios
	if(player1 > player2)
		printf("You won! I'll let you have this one.\n");
	else if(player2 > player1)
		printf("I won! Haha better luck next time!\n");
	else 
		printf("UGH it's a Draw... REMATCH!\n");
}
	
	
	
	
	