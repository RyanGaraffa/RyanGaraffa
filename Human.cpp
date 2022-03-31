#include "stdafx.h"
#include "Human.h"

/* *********************************************************************
Function Name: PrintMenu
Purpose: to print a menu for human turn
Parameters:
			none
Return Value: none
Algorithm:
		1) Outputs menu
		2) collects input for choice
		3) calls appropriate function for choice
Assistance Received: none
********************************************************************* */
void Human::PrintMenu() {
	cout << "\nMENU\n"
		<< "1. Save Game\n"
		<< "2. Make a Move\n"
		<< "3. Ask For Help\n"
		<< "4. Quit\n" << "Please select an option by typing the corressponding number\n";

	int choice = 0;
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
		choice = CollectInput();
	}

	//Will run code to Save Game
	if (choice == 1) {
		cout << "You have chosen to save the game in its current state, please enter the name of the file that you would like to save to:\n";
		string fileName = "Save1.txt";
		cin >> fileName;
		if (SaveGame(fileName)) {
			cout << "Game Saved Successfully\n";
		}
		
		int quitDec = 2;
		while (quitDec != 1 && quitDec != 0) {
			cout << "Would you like to Quit?	Enter '1' for yes or '0' for no\n";
			quitDec = CollectInput();
		}

		if (quitDec == 1) {
			choice = 4;
		}

	}
	//Will run code to Make a Move
	else if (choice == 2) {
		cout << endl;
		//We can just return, nothing else is needed
	}
	//Will run code to "Ask for help"
	else if (choice == 3) {
		//Will Give the user a basic understanding of the game, 
		GiveHelp();
		//cout << "This feature has not been implemented yet" << endl;
	}
	//Will run code to quit
	if (choice == 4) {
		cout << "Quitting the Game\n\n";
		exit(1);

	}

}

/* *********************************************************************
Function Name: DecideNumDice
Purpose: choose the number of dice to roll
Parameters:
			none
Return Value: an int, either 1 or 2 dice
Algorithm:
		1) Checks if the saved rolls are empty
		2) If saved rolls are not empty, just read from there and play those numbers
		3) checks if the player has an option to roll 1 die
		4) if they don't output that they dont and return 2
		5) if they do, give them a decision
		6) if input is '3', then advise will be given
		7) else read in the number and if it is either 1 or 2, return
		8) if input is invalid, re enter input
Assistance Received: none
********************************************************************* */
int Human::DecideNumDice() {
	int numDice = 2;
	if (!Dice.GetSavedRolls().empty()) {
		return 2;
	}
	int count = playerBoard.GetSize() - 6;
	for (int i = 6; i < playerBoard.GetSize(); i++) {
		if (GetP_Side()[i].second == true) {
			count--;
		}
		if (count == 0) {
			do {
				cout << "How many Dice would you like to roll? Enter 1 or 2,	Enter '3' for advice" << endl;
				cin >> numDice;
				if (numDice == 3) {
					Stratz.NumDiceCalc(playerBoard, GetP_Side());
					cout << "The Computer would advise you to roll " << Stratz.GetBestNumDice() << " dice\n\n";
				}
			} while (numDice != 1 && numDice != 2);
		}
	}

	return numDice;

};

/* *********************************************************************
Function Name: CoverOrUncover
Purpose: to decide whether to cover or uncover
Parameters:
			roll -> current roll
Return Value: int representing cover decision
Algorithm:
		1) Outputs nice header
		2) reads input
		3) checks if menu option was selected
		4) returns cover decision if it is valid
		5) if input is 202, will end turn
		6) if input is 303, will give advice
Assistance Received: none
********************************************************************* */
int Human::CoverOrUncover(int roll) {
	cout << "\nYour Roll totals up to " << roll << endl << endl;
	do {
		cout << "Would you like to Uncover your Opponent's Numbers or Cover Your Numbers?\n";
		cout << "Please enter 1 to Uncover or 0 to Cover\n";
		cout << "If you cannot make any more moves, Enter '202'\n";
		cout << "You may also enter '303' for advice\n";
		CoverDecision = CollectInput();

		if (CoverDecision == 202) {
			cout << endl;
			break;
		}

		//give strategy here
		if (CoverDecision == 303) {
			Stratz.CoverCalc(playerBoard, roll, GetO_Side());
			if (Stratz.GetCoverDecision() == 0) {
				cout << "The Ai determined that you should cover your side because you cannot uncover\n\n";
			}
			else if (Stratz.GetCoverDecision() == 1) {
				cout << "The Ai determined that you should uncover your Opponent's side because you can\n\n";
			}
		}

	} while (CoverDecision != 1 && CoverDecision != 0);

	return CoverDecision;
}

/* *********************************************************************
Function Name: DecideNumbers
Purpose: to pick numbers for the human to play after their roll
Parameters:
			currBoard -> the current board
			roll -> their roll
			l_coverdecision -> whether to cover or uncover
Return Value: vector of integers to play
Algorithm:
		1) Displays a nice header with different options
		2) Reads input
		3) Checks for specifc menu option inputs
		4) Checks if the number is playable
		5) if the number is playable, adds that value to a count and adds that number to a vector
		6) Repeats until the count == roll
		7) Returns a vector of the selected numbers
		8) If input is 101, the input will be reset
		9) If input is 202, the turn will end
		10)If input is 303, advice will be given
		11)If input is 404, a player can change their cover decision
Assistance Received: none
********************************************************************* */
vector<int> Human::DecideNumbers(Board currBoard, int roll, int l_coverDecision) {

	CoverDecision = l_coverDecision;

	//output validation
	cout << "\nYou have chosen to ";
	if (CoverDecision == 1) {
		cout << "uncover your opponent's numbers,";
	}
	if (CoverDecision == 0) {
		cout << "cover your numbers,";
	}
	cout << " and your roll = " << roll << endl;

	numToPlay.clear();

	//Declare some variable that we will need
	int inputNum;				//input to be read
	int counter = 0;			//counter to make sure human does not exceed dice roll
	int redo = 0;				//Used to see if player is happy with the numbers they selected

	cout << "You can now select numbers to play totaling exactly your dice roll. Please enter 1 number at a time\n";
	cout << "Please enter '101' if you need to restart your input\n";
	cout << "Please enter '202' if you cannot make any more moves\n";
	cout << "Please enter '303' if you would like advice\n";
	cout << "Please enter '404' if you would like to change your cover decision\n";
	do {

		//collect input
		inputNum = CollectInput();

		//Check if user wants to restart input
		if (inputNum == 101) {
			cout << "Restarting your input, You may continue entering numbers\n";
			resetVector();
			counter = 0;
			continue;
		}

		//Checks if user cannot make any more moves
		if (inputNum == 202) {
			resetVector();
			cout << endl;
			return numToPlay;
		}

		//Will give advice as to what numbers to choose
		if (inputNum == 303) {
			vector<int> advice = Stratz.NumberSelectCalc(playerBoard, roll, GetO_Side(), GetP_Side(), CoverDecision);
			if (advice.size() == 0) {
				cout << "The computer thinks that you cannot make any more moves, please enter '202'\n";
			}
			else {
				cout << "The computer thinks you should play the numbers: ";
				for (unsigned int i = 0; i < advice.size(); i++) {
					cout << advice[i];
					if (advice[i] != advice.back()) {
						cout << ", ";
					}
				}
				cout << " because these are the highest numbers that you can play" << endl << endl;
			}
			continue;
		}

		//Will allow the user to change their cover decision
		if (inputNum == 404) {
			int happy = 2;
			do {
				cout << "\nYou have chosen to ";
				if (CoverDecision == 1) {
					cout << "uncover your opponent's numbers.";
				}
				else if (CoverDecision == 0) {
					cout << "cover your numbers.";
				}
				else {
					cout << "Please enter '0' to cover or '1' to uncover\n";
					CoverDecision = CollectInput();
					continue;
				}
				cout << "\nAre you happy with this decision? Enter 1 for yes and 0 for no\n";
				happy = CollectInput();
				if (happy != 1 && happy != 0) {
					continue;
				}
				if (happy != 1) {
					cout << "Please enter '0' to cover or '1' to uncover\n";
					CoverDecision = CollectInput();
					continue;
				}
			} while (happy != 1);

			numToPlay.clear();
			counter = 0;

			cout << "\nYou may now enter the numbers that you would like to ";
			cout << "Input numbers have been reset\n";
			if (CoverDecision == 1) {
				cout << "uncover.\n";
			}
			else if (CoverDecision == 0) {
				cout << "cover.\n";
			}

			continue;
		}

		//Check if input is positive and nonzero
		if (inputNum < 1) {
			cout << "You must enter a number greater than 0\n";
			continue;
		}

		//Check if input exceeds roll
		if (inputNum > roll) {
			cout << "You may not enter a number greater than your roll\n";
			continue;
		}

		//Checks if input will make total exceed roll
		if (counter + inputNum > roll) {
			cout << "The total of your inputs may not exceed your roll\n";
			string restart;
			do {
				cout << "Would you like to restart you input? Now enter 'y' for yes or 'n' for no\n";
				cin >> restart;
			} while (restart != "y" && restart != "n");
			if (restart == "y") {
				counter = 0;
				numToPlay.clear();
				continue;
			}
			continue;
		}

		//Checks if input is on board 
		if (currBoard.GetSize() < inputNum) {
			cout << "That Number is not playable on this board\n";
			continue;
		}

		//Check if number is already covered (while covering)
		if (CoverDecision == 0) {
			if (currBoard.GetH_Side()[inputNum - 1].second == true) {
				cout << "This number is already covered\n";
				continue;
			}
		}
		//Checks if number is not covered (while uncovering)
		if (CoverDecision == 1) {
			if (currBoard.GetC_Side()[inputNum - 1].second == false) {
				cout << "This number is not covered\n";
				continue;
			}
		}

		//Checks if number is already in numToPlay
		bool inNumToPlay = false;
		for (unsigned int i = 0; i < numToPlay.size(); i++) {
			if (inputNum == numToPlay[i]) {
				cout << "You are already playing this number: " << numToPlay[i] << endl;
				inNumToPlay = true;
			}
		}
		if (inNumToPlay == true) {
			continue;
		}
		//Adds input to vector and to counter
		numToPlay.push_back(inputNum);
		counter = counter + inputNum;

		//Check if counter is = to Roll, if so double check input with user
		if (counter == roll) {
			//Output the numbers chosen
			cout << "\nThe numbers you have chosen to play this round are: ";
			for (unsigned int i = 0; i < numToPlay.size(); i++) {
				if (numToPlay[i] != numToPlay.back()) {
					cout << numToPlay[i] << ", ";
				}
				else {
					cout << numToPlay[i] << endl;
				}
			}
			//Question is user is sure they want to play these numbers
			cout << "Are you sure these are the numbers that you would like to play?\n";
			do {
				cout << "Please enter 1 to play these numbers or 0 to reselect your numbers.\n";
				redo = CollectInput();

			} while (redo != 0 && redo != 1);
			//If user does not want to play these numbers, reset everything and go back to big do while loop
			if (redo == 0) {
				cout << "You may now enter your new numbers: \n";
				counter = 0;
				numToPlay.clear();
				continue;
			}
		}
		else {
			cout << "\nYou may now enter another number\n";
			continue;
		}
		return numToPlay;
	} while (1);

}

/* *********************************************************************
Function Name: CollectInput
Purpose: to read in input without crashing
Parameters:
			none
Return Value: an intager
Algorithm:
		1) Reads input
		2) tries to conver input to a string
		3) catches an exception so that program doesnt crash
		4) loops until we convert an input into a number
		5) returns int representing input
Assistance Received: none
********************************************************************* */
int Human::CollectInput() {
	string input;
	int collectedInput = 0;
	bool Collected = false;

	while (Collected == false) {
		cin >> input;
		try {
			collectedInput = stoi(input);
		}
		catch (exception) {
			cout << "Please Enter an Integer: \n";
			continue;
		}
		return collectedInput;
	}

	return collectedInput;
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
Board Human::ToCover(Board currBoard, int num) {
	Board returnBoard = currBoard;
	returnBoard.Cover(num - 1, 1);
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
Board Human::ToUncover(Board currBoard, int num) {
	Board returnBoard = currBoard;
	returnBoard.Uncover(num - 1, 0);
	return returnBoard;
}

/* *********************************************************************
Function Name: resetVector
Purpose: to reset numToPlay vector
Parameters:
			none
Return Value: void
Algorithm:
		1) clears numToPlay vector
Assistance Received: none
********************************************************************* */
void Human::resetVector() {
	numToPlay.clear();
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
void Human::ReadBoard(Board toRead) {
	playerBoard = toRead;
}

/* *********************************************************************
Function Name: GetP_Side
Purpose: to get the player's side
Parameters:
			none
Return Value: human side of board
Algorithm:
		1) gets player's side
Assistance Received: none
********************************************************************* */
vector<pair<int, bool>> Human::GetP_Side() {
	return playerBoard.GetH_Side();
}

/* *********************************************************************
Function Name: GetO_Side
Purpose: to get the Opponent's side
Parameters:
			none
Return Value: Computer's side of board
Algorithm:
		1) gets opponent's side
Assistance Received: none
********************************************************************* */
vector<pair<int, bool>> Human::GetO_Side() {
	return playerBoard.GetC_Side();
}

/* *********************************************************************
Function Name: GetCoverDecision
Purpose: to get the cover decision
Parameters:
			none
Return Value: cover decision as int -> 0 for cover or 1 for uncover
Algorithm:
		1) returns cover decision
Assistance Received: none
********************************************************************* */
int Human::GetCoverDecision() {
	return CoverDecision;
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
void Human::SetP_Side(vector<pair<int, bool>> toSet) {
	playerBoard.SetH_Side(toSet);
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
void Human::SetO_Side(vector<pair<int, bool>> toSet) {
	playerBoard.SetC_Side(toSet);
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
void Human::SetScores(int scoreH, int scoreC) {
	Hscore = scoreH;
	Cscore = scoreC;
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
void Human::SetLeftoverDiceRolls(vector < pair<int, int >> l_rolls) {
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
vector < pair<int, int >> Human::GetLeftoverDiceRolls() {
	return leftoverDiceRolls;
}

/* *********************************************************************
Function Name: SaveGame
Purpose: to Save the current state of the game into a file
Parameters:
			fName -> holding the name of the file that the player would like to save to
Return Value: bool representing if the save was a success or fail
Algorithm:
		1) Check if save will be overwritten
		2) Open File and begin overwriting/ writing
		3) Check if file is actually open, returns false if closed
		4) Saves the Computer data by reading c_Side and score
		5) Saves the human data by reading h_side and score
		6) Saves first turn as read from board
		7) Saves Next Turn as human because they didnt play their turn yet
		and only a human can save
		8) Close file and return true
Assistance Received: none
********************************************************************* */
bool Human::SaveGame(string fName) {

	//Check if a save will be OverWritten
	ifstream ifs(fName, ios::ate); // std::ios::ate means open at end
	if (ifs.tellg() == 0)
	{
		// file is empty
		ifs.close();
	}
	else {
		string input;
		do {
			cout << "Would you like to OverWrite a Previous Save? Enter 'y' for yes or 'n' for no\n";
			cin >> input;
		} while (input != "y" && input != "n");

		if (input == "n") {
			cout << "Did Not Save\n\n";
			return false;
		}
		else {
			ifs.close();
		}

	}

	//Open File and begin Writing will OverWrite prevoius Save
	ofstream ToSave;
	ToSave.open(fName);
	//ToSave.open("Save1", std::ofstream::out | std::ofstream::trunc);

	if (!ToSave.is_open()) {
		cout << "\nERROR -> Unable to open save file\n";
	}

	Board SaveBoard = playerBoard;
	string boardSide = "";

	//Save Computer Data
	ToSave << "Computer: \n";

	//Save Computer's side of the board
	ToSave << "  Squares: ";
	for (unsigned int i = 0; i < SaveBoard.GetC_Side().size(); i++) {
		if (SaveBoard.GetC_Side()[i].second == true) {
			boardSide = boardSide + "*";
		}
		else {
			boardSide = boardSide + to_string(SaveBoard.GetC_Side()[i].first);
		}
		if (i < SaveBoard.GetC_Side().size()) {
			boardSide = boardSide + " ";
		}
	}
	ToSave << boardSide << "\n";

	//Save Computer's score
	ToSave << "  Score: ";
	ToSave << to_string(Cscore) << "\n";

	ToSave << "\n";

	//Save Human Data
	ToSave << "Human: \n";

	//Save Human's side of the board
	ToSave << "  Squares: ";
	boardSide = "";
	for (unsigned int i = 0; i < SaveBoard.GetH_Side().size(); i++) {
		if (SaveBoard.GetH_Side()[i].second == true) {
			boardSide = boardSide + "*";
		}
		else {
			boardSide = boardSide + to_string(SaveBoard.GetH_Side()[i].first);
		}
		if (i < SaveBoard.GetH_Side().size()) {
			boardSide = boardSide + " ";
		}
	}
	ToSave << boardSide << "\n";

	//Save human's Score
	ToSave << "  Score: ";
	ToSave << to_string(Cscore) << "\n";

	ToSave << "\n";

	//Save First Turn Data
	ToSave << "First Turn: ";
	string fTurn = "";
	if (playerBoard.GetFirstTurn() == 1) {
		fTurn = "Human\n";
	}
	else {
		fTurn = "Computer\n";
	}
	ToSave << fTurn;

	//Save Next Turn Data
	ToSave << "Next Turn: ";
	ToSave << "Human"; //Next Turn will always be Human because Human can only save before their turn

//No Dice Rolls will be Saved

	ToSave.close();
	return true;

}

/* *********************************************************************
Function Name: GiveHelp
Purpose: to give some general game information to the player
Parameters:
			none
Return Value: void
Algorithm:
		1) Outputs game info to terminal
Assistance Received: none
********************************************************************* */
void Human::GiveHelp() {
	cout << "\nWelcome to Canoga\n"
		<< "The Goal of the game it to cover all of your numbers or uncover all of you opponent's numbers\n"
		<< "Each turn you will roll dice and choose numbers to either cover or uncover (cannot do both in one roll) totaling exactly your roll\n"
		<< "Score will be calculated based off the sum of the numbers you have covered if you won by uncvoering\n"
		<< "Or it can be calculated based off the sum of numbers your opponent has uncovered if you won by covering\n"
		<< "You can now begin your turn, further advice can be given for each decision as you play\n\n";
}
