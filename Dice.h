/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga									*
* Class : #10 Dice 											*
* Date : 2/12/2022											*
************************************************************
*/
//Dice class header file
//Dice class will handle the random dice generation 
//Also will handle whether one or two dice are played

#pragma once

#include "stdafx.h"
#include "time.h"

class Dice {
public:

	//constructor
	Dice() {
		vector < pair<int, int >> SavedRolls;
	};

	//destructor
	~Dice() {};

	//Rolls dice based off number of Dice
	pair<int, int> RollDice(int numDice);

	//SavedRolls Accessor
	vector < pair<int, int >> GetSavedRolls();

	//Sets SavedRolls
	void SetRolls(vector < pair<int, int >> Rolls);

private:
	vector < pair<int, int >> SavedRolls;

};