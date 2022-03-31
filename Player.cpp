#include "stdafx.h"
#include "Player.h"

//Virtual functions are defined in header 
//All Virtual functions are never actually called from Player class, all functions are defined in sub classes

/* *********************************************************************
Function Name: GiveHelp
Purpose: to give some general game information to the player
Parameters:
			currBoard-> board passed from round object
			l_diceRolls-> dice rolls passed from Round class to load into the dice object
Return Value: board and bool -> passes board back to round and a bool to see if the round has been won
Algorithm:
		1) Sets the dice rolls if any where loaded
		2) Prints menu for player (nothing for COM)
		3) Rolls Dice for player
		3.5) Error Check Dice Roll
		4) Make Cover Decision for Player
		5) Select Numbers for player
		6) Checks if player lost their turn
		7) Applies changes to board and displays it
		8) Check if the player won
		9) If they did win or lose their turn, returns board and bool and incriments turn counter
		10) loops if turn is not over
Assistance Received: none
********************************************************************* */
pair<Board, bool> Player::play(Board currBoard, vector < pair<int, int >> l_diceRolls) {
	int won = 0;

	//Will Read Dice rolls to Dice Object
	Dice.SetRolls(l_diceRolls);

	while (1) {

		//Player Reads the board
		ReadBoard(currBoard);

		//Menu function for human player
		PrintMenu();

		//Player Rolls the Dice
		pair<int, int> rolls = Dice.RollDice(DecideNumDice());
		cout << "Numbers Rolled: " << rolls.first << " " << rolls.second << endl;

		int roll = rolls.first + rolls.second;
		cout << "Total Roll: " << roll << endl;

		//Player reads dice rolls
		SetLeftoverDiceRolls(Dice.GetSavedRolls());

		//ERROR CHECK -> If Dice rolls from load save do not apply to 7-n covered rule And if Both Rolls == 0, ReRoll
		roll = ErrorCheck(rolls);

		//Player views Dice roll and decides whether to Cover or Uncover
		p_CoverDecision = CoverOrUncover(roll);

		//Check if player cannot make any more moves
		if (p_CoverDecision == 202) {
			break;
		}

		//Player Chooses Numbers to either cover or Uncover
		vector<int> NumToPlay = DecideNumbers(currBoard, roll, p_CoverDecision);

		//Confirm cover decision
		p_CoverDecision = GetCoverDecision();

		//Determines if the current Player Lost their turn
		if (NumToPlay.empty() == true) {
			Dice.SetRolls(GetLeftoverDiceRolls());
			currBoard.IncrimentTurnCounter();
			return make_pair(currBoard, false);
		}

		//Covers numbers if that was selection
		if (p_CoverDecision == 0) {
			for (unsigned int i = 0; i < NumToPlay.size(); i++) {
				currBoard = ToCover(currBoard, NumToPlay[i]);
			}

		}

		//Uncovers numbers if that was the selcection
		if (p_CoverDecision == 1) {
			for (unsigned int i = 0; i < NumToPlay.size(); i++) {

				currBoard = ToUncover(currBoard, NumToPlay[i]);
			}

		}

		//Output Current Board
		currBoard.DisplayBoard();

		//Checks if a Player has won
		won = currBoard.CheckIfWon();
		if (won == 1 || won == 2) {
			SetLeftoverDiceRolls(Dice.GetSavedRolls());
			return make_pair(currBoard, true);
		}

		//Determines if the current Player takes another turn or turns should switch
		if (NumToPlay.empty() == true) {
			Dice.SetRolls(GetLeftoverDiceRolls());
			currBoard.IncrimentTurnCounter();
			return make_pair(currBoard, false);
		}
		//If player did not lose their turn, let them take another
		else {
			NumToPlay.clear();
			continue;
		}
	}
	//This Code only runs if Human player entered "202" on the cover decision to end their turn 
	Dice.SetRolls(GetLeftoverDiceRolls());
	currBoard.IncrimentTurnCounter();
	return make_pair(currBoard, false);

};

/* *********************************************************************
Function Name: ErrorCheck
Purpose: to Check for dice error
Parameters:
			l_rolls-> dice rolls to check
Return Value: int returning total roll
Algorithm:
		1) Check if 7-n rule is broken
		2) Check if both die loaded in as '0'
		3) Reroll and recheck until everything seems fine
		4) Return value that is accepted
Assistance Received: none
********************************************************************* */
int Player::ErrorCheck(pair<int, int> l_rolls) {


	pair<int, int> rolls = l_rolls;
	int roll = rolls.first + rolls.second;


	while (rolls.first == 0 || rolls.second == 0) { // While loop so that if the save file loads multiple wrong dice, we can keep catching it

			//Check if Dice rolls are in tact with 7-n covered Rule
		unsigned int count = 6;
		for (int i = 6; i < GetP_Side().size(); i++) {
			if (GetP_Side()[i].second == true) {
				count++;
			}

		}
		if (count != GetP_Side().size()) {
			cout << "ERROR -> Dice Roll loaded from save breaks 7-n covered Rule\n";
			cout << "Rerolling Dice\n";
		}

		//Check if Both Die == 0
		else if (rolls.first == 0 && rolls.second == 0) {
			cout << "ERROR -> Both Die Rolled '0'\n";
			cout << "Rerolling Dice\n";
		}

		//Breaks if Dice are in compliance with the rules, returns proper total
		else {
			int Unchanged = rolls.first + rolls.second;
			return Unchanged;

		}

		//Reroll Dice if Needed
		rolls = Dice.RollDice(2);
		cout << "Numbers Rolled: " << rolls.first << " " << rolls.second << endl;

		roll = rolls.first + rolls.second;
		cout << "Total Roll: " << roll << endl;


	}

	return roll;
}
