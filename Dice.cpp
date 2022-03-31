#include "stdafx.h"
#include "Dice.h""

/* *********************************************************************
Function Name: RollDice
Purpose: to roll dice
Parameters:
			numDice -> holds number of dice to be rolled
Return Value: void
Algorithm:
		1) Checks if we need to read from savedRolls
		2) if not, we can roll the dice normally
		3) Generate 2 random numbers %6 + 1 to get numbers from 1-6
		4) return pair
Assistance Received: none
********************************************************************* */
pair<int, int> Dice::RollDice(int numDice) {

	int roll1 = 0;
	int roll2 = 0;

	//Will roll the Dice Normally
	if (SavedRolls.empty()) {

		roll1 = (rand()) % 6 + 1;

		if (numDice == 2) {
			roll2 = (rand()) % 6 + 1;
		}
		else {
			roll2 = 0;
		}

	}

	//Will read dice from Vector
	else {

		roll1 = SavedRolls.front().first;
		roll2 = SavedRolls.front().second;

		SavedRolls.erase(SavedRolls.begin());

	}

	//return make_pair(5, 5);
	return make_pair(roll1, roll2);
};

/* *********************************************************************
Function Name: GetSavedRolls
Purpose: to get the SavedRolls
Parameters:
			none
Return Value: vector of rolls
Algorithm:
		1) returns SavedRolls
Assistance Received: none
********************************************************************* */
vector < pair<int, int >> Dice::GetSavedRolls() {
	return SavedRolls;
}

/* *********************************************************************
Function Name: SetRolls
Purpose: to set the SavedRolls
Parameters:
			Rolls -> holds input
Return Value: void
Algorithm:
		1) sets SavedRolls = Rolls
Assistance Received: none
********************************************************************* */
void Dice::SetRolls(vector < pair<int, int >> Rolls) {
	SavedRolls = Rolls;
}
