#include "stdafx.h"
#include "Computer.h"

/* *********************************************************************
Function Name: DecideNumDice
Purpose: choose the number of dice to roll
Parameters:
			none
Return Value: an int, either 1 or 2 dice
Algorithm:
		1) Checks if the saved rolls are empty
		2) If saved rolls are not empty, just read from there and play those numbers
		3) calls GetbestNumDice to see the best number of dice
		4)returns that value with appropriate output to terminal
Assistance Received: none
********************************************************************* */
int Computer::DecideNumDice() {
	Stratz.NumDiceCalc(playerBoard, GetP_Side());
	int numDice = Stratz.GetBestNumDice();
	if (numDice != 1 && numDice != 2) {
		cout << "Error With NumDice function, returning 2\n";
		return 2;
	}
	
	//Double check that we are not reading from saved dice
	if (!Dice.GetSavedRolls().empty()) {
		cout << "Dice Rolls read from Save\n";
		return numDice;
	}

	if (numDice == 1) {
		cout << "The Computer chose to roll 1 die because it could\n";
	}
	else {
		cout << "The Computer must roll 2 dice\n";
	}

	return numDice;			//COME BACK
};

/* *********************************************************************
Function Name: CoverOrUncover
Purpose: to decide whether to cover or uncover
Parameters:
			roll -> current roll
Return Value: int representing cover decision
Algorithm:
		1) calls CoverCalc on Stratz object
		2) returns what that calc returns with appropriate output
Assistance Received: none
********************************************************************* */
int Computer::CoverOrUncover(int roll) {
	Stratz.CoverCalc(playerBoard, roll, GetO_Side());
	int toReturn = Stratz.GetCoverDecision();
	if (toReturn == 0) { //Chose to Cover
		cout << "The Computer chose to Cover their side because they could not uncover your side\n";
	}
	else if (toReturn == 1) {
		cout << "The Computer chose to Uncover your side because it could\n";
	}

	return toReturn;
}

/* *********************************************************************
Function Name: DecideNumbers
Purpose: to pick numbers for the computer to play after their roll
Parameters:
			currBoard -> the current board
			roll -> their roll
			l_coverdecision -> whether to cover or uncover
Return Value: vector of integers to play
Algorithm:
		1) Have strategy object determine vector of numbers to play
		2) if that vector is empty, try a second time with the other cover decision
		3) if vector is still empty, return an empty vectors and output that computer
		lost their turn
		4)If a vector is returns, out the numbers selected to play and then return the vector
Assistance Received: none
********************************************************************* */
vector<int> Computer::DecideNumbers(Board currBoard, int roll, int l_coverDecision) {

	vector<int> toReturn = Stratz.NumberSelectCalc(currBoard, roll, GetO_Side(), GetP_Side(), l_coverDecision);
	if (toReturn.empty()) {
		if (Stratz.GetCoverDecision() == 1) {
			vector<int> toReturn = Stratz.NumberSelectCalc(currBoard, roll, GetO_Side(), GetP_Side(), 0);
		}
		if (toReturn.empty()) {
			cout << "The computer determined that it could not make any more moves\n";
		}
	}
	else if (!toReturn.empty()) {
			cout << "The computer is going to play the numbers: ";
		for (unsigned int i = 0; i < toReturn.size(); i++) {
			cout << toReturn[i];
			if (toReturn[i] != toReturn.back()) {
				cout << " ";
			}
			else {
				cout << " because it determined that these numbers were the highest it could play" << endl;
			}
		}
	}
		return toReturn;
}

/* *********************************************************************
Function Name: ToCover
Purpose: to cover a square on the board
Parameters:
			currBoard -> the current board
			num -> number to cover
Return Value: board with covered square
Algorithm:
		1) Creates a temp board -> returnBoard that == currBoard
		2) calls the cover function from board class on returnBoard
		3) returns returnBoard
Assistance Received: none
********************************************************************* */
Board Computer::ToCover(Board currBoard, int num) {
	Board returnBoard = currBoard;
	returnBoard.Cover(num - 1, 0);
	return returnBoard;
}

/* *********************************************************************
Function Name: ToUncover
Purpose: to uncover a square on the board
Parameters:
			currBoard -> the current board
			num -> number to uncover
Return Value: board with uncovered square
Algorithm:
		1) Creates a temp board -> returnBoard that == currBoard
		2) calls the uncover function from board class on returnBoard
		3) returns returnBoard
Assistance Received: none
********************************************************************* */
Board Computer::ToUncover(Board currBoard, int num) {
	Board returnBoard = currBoard;
	returnBoard.Uncover(num - 1, 1);
	return returnBoard;
}

/* *********************************************************************
Function Name: ReadBoard == (SetBoard)
Purpose: to read the board into human object
Parameters:
			toRead -> input board object
Return Value: void
Algorithm:
		1) sets board = toRead
Assistance Received: none
********************************************************************* */
void Computer::ReadBoard(Board toRead) {
	playerBoard = toRead;
}

/* *********************************************************************
Function Name: GetP_Side
Purpose: to get the player's side
Parameters:
			none
Return Value: computer side of board
Algorithm:
		1) gets player's side
Assistance Received: none
********************************************************************* */
vector<pair<int, bool>> Computer::GetP_Side() {
	return playerBoard.GetC_Side();
}

/* *********************************************************************
Function Name: GetO_Side
Purpose: to get the Opponent's side
Parameters:
			none
Return Value: Human side of board
Algorithm:
		1) gets opponent's side
Assistance Received: none
********************************************************************* */
vector<pair<int, bool>> Computer::GetO_Side() {
	return playerBoard.GetH_Side();
}

/* *********************************************************************
Function Name: SetP_Side
Purpose: to set the Player's Side
Parameters:
			toSet -> holds input
Return Value: void
Algorithm:
		1) sets player's side = toSet
Assistance Received: none
********************************************************************* */
void Computer::SetP_Side(vector<pair<int, bool>> toSet) {
	playerBoard.SetC_Side(toSet);
}

/* *********************************************************************
Function Name: SetO_Side
Purpose: to set the Opponent's side
Parameters:
			toSet -> holds input
Return Value: void
Algorithm:
		1) sets opponent's side = toSet
Assistance Received: none
********************************************************************* */
void Computer::SetO_Side(vector<pair<int, bool>> toSet) {
	playerBoard.SetH_Side(toSet);
}

/* *********************************************************************
Function Name: SetMyScore
Purpose: to set myscore
Parameters:
			score -> holds input
Return Value: void
Algorithm:
		1) sets myscore = score
Assistance Received: none
********************************************************************* */
void Computer::SetMyScore(int score) {
	myscore = score;
}

/* *********************************************************************
Function Name: SetLeftoverDiceRolls
Purpose: to set the leftover dice rolls
Parameters:
			l_rolls -> holds input
Return Value: void
Algorithm:
		1) sets leftover dice rolls = l_rolls
Assistance Received: none
********************************************************************* */
void Computer::SetLeftoverDiceRolls(vector < pair<int, int >> l_rolls) {
	leftoverDiceRolls = l_rolls;
}

/* *********************************************************************
Function Name: GetLeftoverDiceRolls
Purpose: to get the leftover dice rolls
Parameters:
			none
Return Value: vector of dice rolls
Algorithm:
		1) returns leftover dice rolls
Assistance Received: none
********************************************************************* */
vector < pair<int, int >> Computer::GetLeftoverDiceRolls() {
	return leftoverDiceRolls;
}