/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga									*
* Class : #4 Computer 											*
* Date : 2/12/2022											*
************************************************************
*/
#pragma once

#include "Player.h"

class Computer : public Player {
public:


	//constructor
	Computer() {
		Board playerBoard;
		Strategy Stratz;
		vector < pair<int, int >> leftoverDiceRolls;

		int myscore = 0;
	};

	//destructor
	~Computer() {};

	int DecideNumDice();

	int CoverOrUncover(int roll);

	vector<int> DecideNumbers(Board currBoard, int roll, int l_coverDecision);

	Board ToCover(Board currBoard, int num);

	Board ToUncover(Board currBoard, int num);

	void ReadBoard(Board toRead);

	//Accesor for Player side of the Board (COMPUTER)
	vector<pair<int, bool>> GetP_Side();

	//Accesor for Opponent's side of the board (HUMAN)
	vector<pair<int, bool>> GetO_Side();

	//Will Set Player's Side of the Board
	void SetP_Side(vector<pair<int, bool>> toSet);

	//Will Set Opponent's side of the board
	void SetO_Side(vector<pair<int, bool>> toSet);

	//Sets myscore
	void SetMyScore(int score);

	//Sets the leftoverDiceRolls
	void SetLeftoverDiceRolls(vector < pair<int, int >> l_rolls);
	
	//Gets the leftoverDiceRolls
	vector < pair<int, int >> GetLeftoverDiceRolls();

private:
	Board playerBoard;
	Strategy Stratz;
	vector < pair<int, int >> leftoverDiceRolls;

	//Used to keep player Overall Score and save it
	int myscore;				


};