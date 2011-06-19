#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/** roll function; simply rolls a random number,
  * acts as a dice for the game. This
  * is seeded with time by srand in main.
**/
int roll(void) {
	int static NUMBER_OF_DICE_SIDES = 6;

	// The +1 is because the range is between 0 and
	// the number of sides minus 1. +1 fixes this
	// off-by-one error.
	int randNum = (rand()%NUMBER_OF_DICE_SIDES)+1; 
	return randNum;
}

/** playTurn function; handles a player's turn score
  * and majority of the UI/text display.
**/
int playTurn(int currentPlayer, int playerScore) {
	int static DICE_NUM_TO_LOSE = 1;
	int playerTurnTotal = 0;
	_Bool turnDone = false;

	// Plays the person's turn as long 
	// as they don't hold or roll a one.
	while(!turnDone) {
		printf("Player %i - roll or hold?: ", currentPlayer);
		fflush(stdin); // gets rid of the \n character
		char choice = getchar();

		//The player wants to roll, so we roll the dice.
		if (choice == 'r') {
			int diceNumber = roll();
			printf("Rolled %i, your turn total is ", diceNumber);
			if (diceNumber == DICE_NUM_TO_LOSE) {
				printf("0.\n");
				turnDone = true;
				printf("Your score is %i.\n\n", playerScore);
				return playerScore;
			}
			else {
				playerTurnTotal += diceNumber;
				printf("%i.\n", playerTurnTotal);
			}
		}

		// If the person doesn't want to roll, they hold.
		else if (choice == 'h') {
			turnDone = true;
			int totalScore = (playerScore + playerTurnTotal);
			printf("Your score is %i.\n\n", totalScore);
			return totalScore;
		}
	}
}
/** Main function; handles the player score
  * and switching roles for a player's turn.
**/
int main(void) {
	int static PLAYER_ONE = 1;
	int static PLAYER_TWO = 2;
	int static WINNING_SCORE = 100;
	int currentPlayer = PLAYER_ONE;
	int player1Score = 0;
	int player2Score = 0;
	int winner = 0;
	_Bool gameDone = false;

	//seed the random number generator with time.
	srand((unsigned)(time(NULL)));

	while (!gameDone) {
		if (currentPlayer == PLAYER_ONE) {
			player1Score = playTurn(currentPlayer, player1Score);
			if (player1Score >= WINNING_SCORE) {
				winner = PLAYER_ONE;
				gameDone = true;
			}
			else {
				currentPlayer = PLAYER_TWO;
			}
		}
		else if (currentPlayer == PLAYER_TWO) {
			player2Score = playTurn(currentPlayer, player2Score);
				if (player2Score >= WINNING_SCORE) {
					winner = PLAYER_TWO;
					gameDone = true;
				}
				else {
					currentPlayer = PLAYER_ONE;
				}
		}
	}
	printf("Game over. Player %i wins!\n", winner);
	return 0;
}