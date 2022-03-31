/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga											*
* Class : #3 Human 											*
* Date : 2/12/2022											*
************************************************************
*/
#pragma once

#include "Player.h"

class Human : public Player {
public:

	//constructor
	Human() {
		
		int CoverDecision = 2;
		
		vector<int> numToPlay;

		Board playerBoard;

		Strategy Stratz;

		vector<pair<int, int>> leftoverDiceRolls;

		int Hscore = 0;

		int Cscore = 0;
	};

	//destructor
	~Human() {};

	//Will Print the board out to the human player
	void PrintMenu();

	//Will let the human player choose the number of dice they would like to play ONLY IF 7-n are covered
	int DecideNumDice();

	//Will let the Human choose to cover or uncover
	int CoverOrUncover(int roll);

	//Will Let the Human Player choose the number that they would like to play
	vector<int> DecideNumbers(Board currBoard, int roll, int l_coverDecision);

	//Handle Errors from input
	//Proud of this function, simple and makes the code so much better
	int CollectInput();

	//Covers a number on the board
	Board ToCover(Board currBoard, int num);

	//Uncovers a number on the board
	Board ToUncover(Board currBoard, int num);

	//Will reset numtoPlay vector
	void resetVector();

	//Will read the input board to the player object
	void ReadBoard(Board toRead);

	//Accesor for Player side of the Board (HUMAN)
	vector<pair<int, bool>> GetP_Side();

	//Accesor for Opponent's side of the board (COMPUTER)
	vector<pair<int, bool>> GetO_Side();

	//Accesor for CoverDecision
	int GetCoverDecision();

	//Will Set Player's Side of the Board
	void SetP_Side(vector<pair<int, bool>> toSet);

	//Will Set Opponent's side of the board
	void SetO_Side(vector<pair<int, bool>> toSet);

	//Sets myscore
	void SetScores(int scoreH, int scoreC);

	//Sets the leftoverDiceRolls
	void SetLeftoverDiceRolls(vector < pair<int, int >> l_rolls);

	//Gets the leftoverDiceRolls
	vector < pair<int, int >> GetLeftoverDiceRolls();

	//Save Function ->Will Write to Save1;
	bool SaveGame(string fName);

	//Gives Rules and intro to Game
	void GiveHelp();

private:
	//Cover or uncover decision, 0 means u want to cover, 1 means you want to uncover
	int CoverDecision = 2;	
	//vector to return
	vector<int> numToPlay;	

	//State of the current Board
	Board playerBoard;			

	//Strategy object used for advising the human
	Strategy Stratz;			

	//Vector to hold leftover Dice Rolls
	vector<pair<int, int>> leftoverDiceRolls;

	//Used to keep player Overall Score and save it
	int Hscore;		

	//Used to keep track of Computer score and save it
	int Cscore;

};