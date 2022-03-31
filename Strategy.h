/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga											*
* Class : #8 Strategy 										*
* Date : 2/12/2022											*
************************************************************
*/
//Strategy class Header file
//This class will be responsible for implementing strategy of the ai as well as giving advice to the player
//A general idea is going to be to prioritize larger numbers

#pragma once

#include "Board.h"

class Strategy {
public:
	

	//constructor
	Strategy() {
		
		int bestNumDice = 2;

		int coverDecision = 0;

		bool coverDec = 0;

		vector<int>	NumberSelect;

		bool prolong = false;

		vector<pair<int, bool>> o_Side;
		
		vector<pair<int, bool>> p_Side;
	};

	//destructor
	~Strategy() {};

	//STRATEGY CALCULATION FUNCTIONS
	//Will Calculate the best number of dice to roll
	void NumDiceCalc(Board currBoard, vector<pair<int, bool>> p_Side);

	//Will Calculate whether its better to cover or uncover
	void CoverCalc(Board currBoard, int roll, vector<pair<int, bool>> o_Side);

	//Will check if any combination of numbers up to three can add up to the roll
	bool CanUncover(int roll, vector<pair<int, bool>> o_Side);

	//Will calculate what numbers are best to play
	vector<int> NumberSelectCalc(Board currBoard, int roll, vector<pair<int, bool>> o_Side, vector<pair<int, bool>> p_Side, int covDec);

	//Accesor for bestNumdice
	int GetBestNumDice();

	//accesor for coverdecision
	int GetCoverDecision();

	//accesor for NumberSelect
	vector<int> GetNumberSelect();

	//Mutator for cover selection
	void SetCoverDecision(int toSet);


private:
	//Number of Dice that the AI determines is best to play
	int bestNumDice;					

	//Ai determines which is better to cover or not to cover --- 0 means u want to cover, 1 means you want to uncover
	int coverDecision;		

	//Same as int represented in a bool to compare to board.second
	bool coverDec;		

	//Ai determines what number is best to play
	vector<int>	NumberSelect;	

	//Ai will determine whether or not it wants to drag the game out
	bool prolong = false;				

	//Keeps track of the side that belongs to the opponent
	vector<pair<int, bool>> o_Side;	
	//Keeps track of the side that belongs to the player
	vector<pair<int, bool>> p_Side;	

};