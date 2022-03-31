/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga									*
* Class : #5 Board 											*
* Date : 2/12/2022											*
************************************************************
*/

//Board class header file
//This class could be useful to store all the information of the current board in one place

#pragma once

#include "stdafx.h"

class Board {
public:
	//Constructor
	Board() {
		vector<pair<int, bool>> H_Side;
		vector<pair<int, bool>> C_Side;

		unsigned int size = 9;

		int firstTurn = 1;


		int turnCounter = 0;
	}

	//destructor
	~Board() {}

	//Will reset all existing conditions and create a new board
	void CreateNewBoard(int Turn);

	//Will Display the current board
	void DisplayBoard();

	//Will be the function to cover one of your numbers
	void Cover(int num, int player);

	//Will be the function to uncover opponents numbers
	void Uncover(int num, int player);

	//Will Check if HSide or CSide is full (A player has won)
	//Returns 0 if no winner, 1 is human won, 2 if comp won
	int CheckIfWon(); 


	//Sets Size
	void SetSize(int input_size);

	//Sets firstTurn
	void SetFirstTurn(int f_turn);

	//Will set the H_Side
	void SetH_Side(vector<pair<int, bool>> toSet);

	//Will set the C_Side
	void SetC_Side(vector<pair<int, bool>> toSet);

	//Mutator function for turncounter
	void SetTurnCounter(int toSet);

	//Incriment Turn counter
	void IncrimentTurnCounter();


	//Accesor function for size
	int GetSize();

	//Accesor function for H_Side
	vector<pair<int, bool>> GetH_Side();

	//Accesor function for H_Side
	vector<pair<int, bool>> GetC_Side();

	//Accesor function for firstturn
	int GetFirstTurn();

	//Accesor function for turncounter
	int GetTurnCounter();

private:

	//Vector pairs displaying the board for each player.
	vector<pair<int, bool>> H_Side;
	vector<pair<int, bool>> C_Side;

	//size of the board
	unsigned int size = 9;

	//== 1 if human plays first and 0 if com plays first
	int firstTurn = 1;		

	//Used to make sure a player does not win by uncovering on the first turn
	int turnCounter = 0;

};