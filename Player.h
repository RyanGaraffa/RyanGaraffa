/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga											*
* Class : #2 Player											*
* Date : 2/12/2022											*
************************************************************
*/
//Player class header file
//Player will hold functions tat are the same for both computers and Humans
//play function will work for both computer and human

#pragma once

#include "Dice.h"
#include "Board.h"
#include "Strategy.h"
#include "stdafx.h"

class Player {
public:

	//constructor
	Player() {
	
		Board playerBoard;

		int p_CoverDecision = 0;

		vector < pair<int, int >> leftoverDiceRolls;
	};

	//destructor
	~Player() {};
	
	//returns the current board so that if a turn switch occurs, the board is saved
	//returns a bool to see if round is complete, if bool is true, we can calculate who won and points based off current board
	pair<Board, bool> play(Board currBoard, vector < pair<int, int >> l_diceRolls);

	//Used to check if dice rolls from save break 7-n covered rule
	int ErrorCheck(pair<int, int> l_rolls);

	//Virtual functions, Player will execute differently depending on if it is a human or a computer
	//See Human and Computer classes for better details of these functions
	virtual int DecideNumDice() { return 1;  };
	virtual int CoverOrUncover(int roll) {	return 1; }
	virtual vector<int> DecideNumbers(Board currBoard, int roll, int l_coverDecision) {vector<int> empty; return empty;}

	virtual Board ToCover(Board currBoard, int num) { return currBoard; }
	virtual Board ToUncover(Board currBoard, int num) { return currBoard; }

	virtual int GetCoverDecision() { return p_CoverDecision; }

	virtual void ReadBoard(Board toRead) {}
	virtual void PrintMenu() {}

	virtual vector<pair<int, bool>> GetP_Side() { return playerBoard.GetC_Side(); }
	virtual vector<pair<int, bool>> GetO_Side() { return playerBoard.GetH_Side(); }
	virtual void SetP_Side(vector<pair<int, bool>> toSet) {}
	virtual void SetO_Side(vector<pair<int, bool>> toSet) {}

	virtual vector < pair<int, int >> GetLeftoverDiceRolls() { return leftoverDiceRolls; }
	virtual void SetLeftoverDiceRolls(vector < pair<int, int >> l_rolls) { leftoverDiceRolls = l_rolls; }

	//Dice Object for determining Roll Public so that is can be accessed by Human and Computer
	Dice Dice;

private:
	//Holds the board for the player class
	Board playerBoard;

	//holds the cover decision that the player selected
	int p_CoverDecision = 0;

	//holds leftover Dice rolls
	vector < pair<int, int >> leftoverDiceRolls;

};