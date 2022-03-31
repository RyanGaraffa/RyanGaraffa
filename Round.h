/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga											*
* Class : #7 Round 											*
* Date : 2/12/2022											*
************************************************************
*/
//Round class header file
//Round class will handle each round of play
//Probably will implement a while loop running turns until a victor
//

#pragma once

#include "Human.h"
#include "Computer.h"
#include "Board.h"

class Round {
public:
	
	//Constructor
	Round() {
		done = false;
		turnCounter = 0;
		nextTurn = 1;
		rowSize = 9;

		Human r_Human;
		Computer r_Computer;

		vector<pair<int, int>> r_DiceRolls;
		Board currBoard;
		pair<Board, bool> boardAndDone;
	};

	//destructor
	~Round() {};

	//Can return a negative value for AI's score and a positve value for players score
	//This Code runs Everything except the first round of a loaded save
	int PlayRound(int l_rowSize, int l_nextTurn);

	//Will Play the first Round for a loaded save
	int PlayRound();

	//returns the player in which will play the current turn (H or C)
	Player *NextTurn();

	//Will return the score earned after the round is complete
	int CalculateScore();

	//Sets currBoard
	void SetBoard(Board inputBoard);

	//Sets Scores
	void SetScores(int hScore, int cScore);

	//Sets r_DiceRolls
	void SetDiceRolls(vector<pair<int, int>> inputRolls);

	//Sets Next Turn
	void SetNextTurn(int n_turn);

	//Sets hCap
	void SetHCap(bool toSet);

	//Accessor for Board
	Board GetBoard();

private:

	//Holds rowSize of the board
	int rowSize;

	//Used to check if nextTurn was loaded from save file, 1 for human and 0 for Computer
	int nextTurn;	

	//Used to make sure no winner is declared immediately due to all spaces uncovered
	int turnCounter;

	//Holds dice rolls from loaded save if they exist
	vector<pair<int,int>> r_DiceRolls;			

	//Human object representing the human player
	Human r_Human;								

	//Computer object representing the computer player
	Computer r_Computer;						

	//Will keep track of the current board
	Board currBoard;							

	//Used to read the board and if not done, pass to next player
	pair<Board, bool> boardAndDone;				

	//Tells whether the player won the round or not
	bool done;							

	//Tells us whether a handicap was applied
	bool hCap = false;
};