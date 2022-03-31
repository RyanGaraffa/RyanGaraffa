#include "stdafx.h"
#include "Round.h"

//Can return a negative value for AI's score and a positve value for players score
//This Code runs Everything except the first round of a loaded save
/* *********************************************************************
Function Name: PlayRound
Purpose: to play round except first round of a loaded save
Parameters:
			l_rowSize -> tells us the board size
			l_nextTurn -> tells us the next turn
Return Value: int holding score (negative for computer score)
Algorithm:
		1)Check if board loaded, if not, create new board 
		2)Displays Board
		3) Reads dice rolls into human and computer
		4) Play Game alternating reading the dice rolls from human and computer and
		alternating turncounter
		5) NextTurn shows us who plays next and they play
		6) once there is a winner, we set the dice rolls again, and then calculate the score
		7) return the right score
Assistance Received: none
********************************************************************* */
int Round::PlayRound(int l_rowSize, int l_nextTurn) {

	
	//Runs this code if handicap was issued
	if (hCap) {
		hCap = false;
	}

	//Creates new Baord -> if no handicap was implmented
	else {
		//Sets Size from input
		currBoard.SetSize(l_rowSize);

		//Create a fresh board for the round if there was no handicap applied
		currBoard.CreateNewBoard(l_nextTurn);
	}
	//Set Dice Rolls
	r_Human.SetLeftoverDiceRolls(r_DiceRolls);
	r_Computer.SetLeftoverDiceRolls(r_DiceRolls);

	//Display the starting board
	currBoard.DisplayBoard();

	done = false;

	//This Variable is no longer useful after this function is called
	//That ^ is because when this function is called, we are no longer loading from a save
	nextTurn = 2;

	//Will Play the game until there is a winner
	while (done == false) {

		//Correctly set turn counter
		turnCounter = currBoard.GetTurnCounter();

		//Collect Leftover Dice rolls
		if (turnCounter % 2 == 1 && currBoard.GetFirstTurn() == 1) {
			SetDiceRolls(r_Human.GetLeftoverDiceRolls());
		}
		else if (turnCounter % 2 == 0 && currBoard.GetFirstTurn() == 0) {
			SetDiceRolls(r_Human.GetLeftoverDiceRolls());
		}
		else {
			SetDiceRolls(r_Computer.GetLeftoverDiceRolls());
		}

		//Will play the turn returning the current board and if the round is done
		boardAndDone = NextTurn()->play(currBoard, r_DiceRolls);

		//Will set the round members correctly from the play()
		currBoard = boardAndDone.first;
		done = boardAndDone.second;

	}
	
	//Calculate Score and return it
	return CalculateScore();
};

/* *********************************************************************
Function Name: PlayRound
Purpose: to play round of a loaded save
Parameters:
			none
Return Value: int holding score (negative for computer score)
Algorithm:
		1) Displays Board
		2) Reads dice rolls into human and computer
		3) Play Game alternating reading the dice rolls from human and computer and
		alternating turncounter
		4) NextTurn shows us who plays next and they play
		5) once there is a winner, we set the dice rolls again, and then calculate the score
		6) return the right score
Assistance Received: none
********************************************************************* */
int Round::PlayRound() {

	//Display the starting board
	currBoard.DisplayBoard();

	//Set Dice Rolls
	r_Human.SetLeftoverDiceRolls(r_DiceRolls);
	r_Computer.SetLeftoverDiceRolls(r_DiceRolls);

	done = false;

	//Will Play the game until there is a winner
	while (done == false) {

		//Check if turncounter and GetTurnCounter line up
		if (turnCounter != currBoard.GetTurnCounter() - 1) {
			turnCounter = currBoard.GetTurnCounter() - 1;
		}
		else {
			//will set turnCounter properly
			turnCounter = currBoard.GetTurnCounter();
		}

		//Collect Leftover Dice rolls
		if (turnCounter % 2 == 1) {
			SetDiceRolls(r_Human.GetLeftoverDiceRolls());
		}
		else {
			SetDiceRolls(r_Computer.GetLeftoverDiceRolls());
		}

		//Will play the turn returning the current board and if the round is done
		boardAndDone = NextTurn()->play(currBoard, r_DiceRolls);


		//Will set the round members correctly from the play()
		currBoard = boardAndDone.first;
		done = boardAndDone.second;

	}

	//Set Dice Rolls Appropriately
	if (turnCounter % 2 == 0) {
		SetDiceRolls(r_Human.GetLeftoverDiceRolls());
	}
	else {
		SetDiceRolls(r_Computer.GetLeftoverDiceRolls());
	}

	return CalculateScore();
};

/* *********************************************************************
Function Name: CalculateScore
Purpose: to calculate the appropriate score
Parameters:
			none
Return Value: int holding score (negative for computer score)
Algorithm:
		1) Reads board
		2) Checks if player won by uncovering (return all sum of covered)
		3) Checks if player won by covering		(return sum of uncovered)
		4) Will return the appropriate score (negative for computer)
Assistance Received: none
********************************************************************* */
int Round::CalculateScore() {
	vector<pair<int, bool>> C = currBoard.GetC_Side();
	vector<pair<int, bool>> H = currBoard.GetH_Side();

	//counters for the total number of covered squares for each player
	int CCount = 0; int HCount = 0; int maxScore = 0;

	for (int i = 0; i < currBoard.GetSize(); i++) {
		if (C[i].second == true) {
			CCount = CCount + C[i].first;
		}
		if (H[i].second == true) {
			HCount = HCount + H[i].first;
		}
	}

	//Will Check if a player won by uncovering
	if (CCount == 0) {
		//Hcount should represent the score to return;
		return HCount;
	}
	else if (HCount == 0) {
		//CCount should represent the score of the computer
		//Multiply by -1 so we know its the computer's score
		CCount = CCount * (-1);
		return CCount;
	}

	//Will Check if a player won by covering

	for (int i = 0; i < currBoard.GetSize(); i++) {
		maxScore = maxScore + C[i].first;
	}
	if (HCount == maxScore) {
		return (maxScore - CCount);
	}
	if (CCount == maxScore) {
		return ((-1)*(maxScore - HCount));
	}

	//
	cout << "\n\nERROR -> Unable to appropriately calculate Score (returning 1) \n\n";
	return 1;
};

/* *********************************************************************
Function Name: NextTurn
Purpose: to decide who plays the next turn
Parameters:
			none
Return Value: player pointer
Algorithm:
		1) Checks for a next turn value from loaded save
		2) Checks for first turn decision
		3) else returns address of r_Computer for an odd turncounter
		4) else returns address of r_Human for an even turncounter
Assistance Received: none
********************************************************************* */
Player *Round::NextTurn() {

	//CODE THAT WILL TRIGGER IF WE ARE READING FROM SAVE only once
	if (nextTurn == 1) { //Will return Human player
		turnCounter = 2;
		Board ToSet = currBoard;
		ToSet.SetTurnCounter(turnCounter);
		currBoard = ToSet;
		nextTurn = 2;
		return &r_Human;
	}
	if (nextTurn == 0) { //Will return Computer player
		turnCounter = 1;
		Board ToSet = currBoard;
		ToSet.SetTurnCounter(turnCounter);
		currBoard = ToSet;
		nextTurn = 2;
		return &r_Computer;
	}

	//Must select first turn from first turn from board
	if (currBoard.GetFirstTurn() == 0 && turnCounter == 0) {
		return &r_Computer;
	}
	else if (currBoard.GetFirstTurn() == 1 && turnCounter == 0) {
		return &r_Human;
	}

	//NORMAL CODE THAT WILL TRIGGER THROUGHOUT ROUND
	if (turnCounter % 2 == 1) {
		return &r_Computer;
	}
	else {
		return &r_Human;
	}
};

//Sets Board
void Round::SetBoard(Board inputBoard) {
	currBoard = inputBoard;
}

//Sets Scores
void Round::SetScores(int hScore, int cScore) {
	// Save both in human because Human is the only one who can save
	r_Human.SetScores(hScore, cScore);
}

//Accessor for Board
Board Round::GetBoard() {
	return currBoard;
}

//Sets Dice Rolls
void Round::SetDiceRolls(vector<pair<int, int>> inputRolls) {
	r_DiceRolls = inputRolls;
}

//Sets Next Turn
void Round::SetNextTurn(int n_turn) {
	if (n_turn == 1 || n_turn == 0) {
		nextTurn = n_turn;
	}
	else {
		cout << "\n\n\nERROR SETTING NEXT TURN -> Cannot set first turn to an integer other than '1' or '0'" << endl;
		cout << "next turn (n_turn) that was read and attempted to set next turn equal to = " << n_turn << endl;
		cout << "Setting next turn = 1 representing the human player\n";
		nextTurn = 1;
	}
}

//Sets hCap
void Round::SetHCap(bool toSet) {
	hCap = toSet;
}