#include "stdafx.h"
#include "Board.h"

/* *********************************************************************
Function Name: Uncover
Purpose: To uncover a specific space on the board
Parameters:
			int num -> is the number to cover
			int player -> is the player's side that will be uncovered
Return Value: void
Algorithm:
		1) Determine which player
	   2) uncover num on that player's side
Assistance Received: none
********************************************************************* */
void Board::Uncover(int num, int player) {
	if (player == 1) {
		H_Side[num].second = false;
	}
	if (player == 0) {
		C_Side[num].second = false;
	}
};

/* *********************************************************************
Function Name: Cover
Purpose: To Cover a specific space on the board
Parameters:
			int num -> is the number to cover
			int player -> is the player's side that will be uncovered
Return Value: void
Algorithm:
		1) Determine which player
	   2) Cover num on that player's side
Assistance Received: none
********************************************************************* */
void Board::Cover(int num, int player) {
	if (player == 1) {
		H_Side[num].second = true;
	}
	if (player == 0) {
		C_Side[num].second = true;
	}
};

/* *********************************************************************
Function Name: CheckIfWon
Purpose: To check if anyone has won the round
Parameters:
			none
Return Value: int representing the winner, 2 for Com, 1 for Human, 0 for no winner
Algorithm:
		1) count up uncovered and covered spaces on the board
	   2) if a count or uncovered count == the size of board, a player won
	   3) also check that the turncounter != 0 so that a player doesnt win by uncovering first check
	   4) also check first turn so that a player cannot win by uncovering during the second turn
Assistance Received: none
********************************************************************* */
int Board::CheckIfWon(){
	unsigned int counter = 0;
	unsigned int counterUnC = 0;


	//Checks Human Side if they won, returns 1 if so

	for (unsigned int i = 0; i < H_Side.size(); i++) {
		if (H_Side[i].second == true) {
			counter++;
		}
		if (C_Side[i].second == false) {
			counterUnC++;
		}
		if (H_Side.size() == counter || (H_Side.size() == counterUnC && turnCounter != 0 && firstTurn == 0)) {
			return 1;
		}
	}


	//Checks Computer's side if they won, returns 2 if they won

	counter = counterUnC = 0;

	for (unsigned int i = 0; i < C_Side.size(); i++) {
		if (C_Side[i].second == true) {
			counter++;
		}
		if (H_Side[i].second == false) {
			counterUnC++;
		}
		if (C_Side.size() == counter || (C_Side.size() == counterUnC && turnCounter != 0 && firstTurn == 1)) {
			return 2;
		}
	}

	return 0;
}

/* *********************************************************************
Function Name: CreateNewBoard
Purpose: To create a new board object
Parameters:
			int Turn -> sets first turn
Return Value: void
Algorithm:
		1) Create a board of size 9
	   2) if board size is 10 or 11, will add spaces to Human and computer sides
Assistance Received: none
********************************************************************* */
void Board::CreateNewBoard(int Turn) {

	//Clear pre-existing board
	H_Side.clear();
	C_Side.clear();
	turnCounter = 0;
	firstTurn = Turn;

	//Getting the player's side set up
	H_Side.push_back(make_pair(1, false));
	H_Side.push_back(make_pair(2, false));
	H_Side.push_back(make_pair(3, false));
	H_Side.push_back(make_pair(4, false));
	H_Side.push_back(make_pair(5, false));
	H_Side.push_back(make_pair(6, false));
	H_Side.push_back(make_pair(7, false));
	H_Side.push_back(make_pair(8, false));
	H_Side.push_back(make_pair(9, false));

	//Getting the Computer's side set up
	C_Side.push_back(make_pair(1, false));
	C_Side.push_back(make_pair(2, false));
	C_Side.push_back(make_pair(3, false));
	C_Side.push_back(make_pair(4, false));
	C_Side.push_back(make_pair(5, false));
	C_Side.push_back(make_pair(6, false));
	C_Side.push_back(make_pair(7, false));
	C_Side.push_back(make_pair(8, false));
	C_Side.push_back(make_pair(9, false));

	//Accounting for chosen board size
	//This code should allow up to twelve if I want to implement that
	int fill = 9;
	while (H_Side.size() < size) {
		fill++;
		H_Side.push_back(make_pair(fill, false));
		C_Side.push_back(make_pair(fill, false));
	}
}


/* *********************************************************************
Function Name: DisplayBoard
Purpose: to display the board to terminal
Parameters:
			none
Return Value: void
Algorithm:
		1) Output header - > computer:
	    2) cycle through Com's side of the board to display it
		3) repeat for human
		4) display first turn
Assistance Received: none
********************************************************************* */
void Board::DisplayBoard() {

	//Display Header
	cout << "\nCurrent Board:\n";

	//Display the Computer's Side
	cout << "Computer:	";
	for (unsigned int i = 0; i < C_Side.size(); i++) {
		//cout << C_Side[i].first;
		if (C_Side[i].second == true) {
			cout << "* ";
		}
		else {
			cout << C_Side[i].first << " ";
		}
	}
	cout << endl;

	//Display the human's Side
	cout << "Human:		";
	for (unsigned int i = 0; i < H_Side.size(); i++) {
		//cout << H_Side[i].first;
		if (H_Side[i].second == true) {
			cout << "* ";
		}
		else {
			cout << H_Side[i].first << " ";
		}
	}
	cout << endl;

	//Print first Turn
	cout << "First Turn: ";
	if (firstTurn == 0) {
		cout << "Computer\n" << endl;
	} 
	else {
		cout << "Human\n" << endl;
	}

}

/* *********************************************************************
Function Name: SetSize
Purpose: to set the size
Parameters:
			input_size -> will set Size to this
Return Value: void
Algorithm:
		1) sets board size value = to input_size
Assistance Received: none
********************************************************************* */
void Board::SetSize(int input_size) {
	size = input_size;
}

/* *********************************************************************
Function Name: GetSize
Purpose: to get the size
Parameters:
			none
Return Value: size of board
Algorithm:
		1) return's board size
Assistance Received: none
********************************************************************* */
int Board::GetSize() {
	return size;
}

/* *********************************************************************
Function Name: GetH_Side
Purpose: to get the human side of the board
Parameters:
			none
Return Value: vector of human's side of the board
Algorithm:
		1) return's human's side of the board
Assistance Received: none
********************************************************************* */
vector<pair<int, bool>> Board::GetH_Side() {
	return H_Side;
}

/* *********************************************************************
Function Name: GetC_Side
Purpose: to get the computer's side of the board
Parameters:
			none
Return Value: vector of computer's side of the board
Algorithm:
		1) return's computer's side of the board
Assistance Received: none
********************************************************************* */
vector<pair<int, bool>> Board::GetC_Side() {
	return C_Side;
}

/* *********************************************************************
Function Name: GetFirstTurn
Purpose: to get the first turn
Parameters:
			none
Return Value: first turn
Algorithm:
		1) return's first turn
Assistance Received: none
********************************************************************* */
int Board::GetFirstTurn() {
	return firstTurn;
}

/* *********************************************************************
Function Name: SetFirstTurn
Purpose: to set the first turn
Parameters:
			f_turn -> hold input
Return Value: void
Algorithm:
		1) sets first turn = f_turn
Assistance Received: none
********************************************************************* */
void Board::SetFirstTurn(int f_turn) {
	if (f_turn == 1 || f_turn == 0) {
		firstTurn = f_turn;
	}
	else {
		cout << "\n\n\nERROR SETTING FIRST TURN -> Cannot set first turn to an integer other than '1' or '0'" << endl;
		cout << "first turn (f_turn) that was read and attempted to set first turn equal to = " << f_turn << endl;
		cout << "Setting first turn = 1 representing the human player\n";
		firstTurn = 1;
	}
}

//Accesor function for turncounter
int Board::GetTurnCounter() {
	return turnCounter;
}

/* *********************************************************************
Function Name: SetH_Side
Purpose: to set the human's side of the board
Parameters:
			toSet-> holds input vector
Return Value: void
Algorithm:
		1) Sets human's side of the board
Assistance Received: none
********************************************************************* */
void Board::SetH_Side(vector<pair<int, bool>> toSet) {
	H_Side = toSet;
}

/* *********************************************************************
Function Name: GetC_Side
Purpose: to set the computer's side of the board
Parameters:
			toSet-> holds input vector
Return Value: void
Algorithm:
		1) sets computer's side of the board
Assistance Received: none
********************************************************************* */
void Board::SetC_Side(vector<pair<int, bool>> toSet) {
	C_Side = toSet;
}

/* *********************************************************************
Function Name: SetTurnCounter
Purpose: to set the turncounter
Parameters:
			toSet-> holds input 
Return Value: void
Algorithm:
		1) sets turncounter
Assistance Received: none
********************************************************************* */
void Board::SetTurnCounter(int toSet) {
	turnCounter = toSet;
}

/* *********************************************************************
Function Name: IncrimentTurnCounter
Purpose: to incriment the turncounter
Parameters:
			none
Return Value: void
Algorithm:
		1) incriments turncounter
Assistance Received: none
********************************************************************* */
void Board::IncrimentTurnCounter() {
	turnCounter++;
}