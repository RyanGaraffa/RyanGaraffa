#include "stdafx.h"
#include "Game.h"

/* *********************************************************************
Function Name: NextRound
Purpose: to play the next round without loaded save or every round after first
Parameters:
			l_rowSize -> reads board size from Game
Return Value: void
Algorithm:
		1) Decides very first turn with dice roll
		2) Otherwise it alternates first turns
		3) Places a handicap if conditions are met
		4) Plays the Round
		5) calls announceWinnerAndScore
		6) Sets appropriate scores back into the round
Assistance Received: none
********************************************************************* */
void Game::NextRound(int l_rowSize) {

	//Decide First First Turn
	if (scorePlayer == 0 && scoreAI == 0) {
		bool done = false;
		while (!done) {
			Dice forFirst;
			pair<int, int> hRoll;
			pair<int, int> cRoll;
			cout << "We shall roll dice to see who goes first\n";
			hRoll = forFirst.RollDice(2);
			cout << "Player rolled: " << hRoll.first << " & " << hRoll.second << endl;
			cRoll = forFirst.RollDice(2);
			cout << "Computer rolled: " << cRoll.first << " & " << cRoll.second << endl;

			int hRollTot = hRoll.first + hRoll.second;
			int cRollTot = cRoll.first + cRoll.second;


			//g_firstTurn = 1 if human plays first
			if (hRollTot > cRollTot) {
				cout << "You won so you will go first\n";
				done = true;
				g_firstTurn = 1;
			}
			//g_firstTurn = 0 if com plays first
			else if (cRollTot > hRollTot) {
				cout << "Computer won so they will go first\n";
				done = true;
				g_firstTurn = 0;
			}
			else {
				cout << "It was a Tie, so everyone must Roll Again\n\n";
			}
		}

		AnnounceWinnerAddScore(currRound.PlayRound(l_rowSize, g_firstTurn));
	}

	//This Code will run after first round
	else {

		//Should Make sure we alternate first turns
		//If Human went first last game
		if (g_firstTurn == 1) {
			g_firstTurn = 0;
		}
		//if com went first last game
		else if (g_firstTurn == 0) {
			g_firstTurn = 1;
		}

	//Place Handicap here
		//Human had first turn and won
		if (g_firstTurn == 0 && winner == 1) {
			cout << "Human Player will recieve a handicap in the next round" << endl;
			ApplyHandicap(l_rowSize, 1);
		}
		//Computer Had first turn and won
		else if (g_firstTurn == 1 && winner == 0) {
			cout << "Computer will recieve a handicap in the next round" << endl;
			ApplyHandicap(l_rowSize, 0);

		}

		AnnounceWinnerAddScore(currRound.PlayRound(l_rowSize, g_firstTurn));
	}
	//Will Do this no matter what
	currRound.SetScores(scorePlayer, scoreAI);
};

/* *********************************************************************
Function Name: Applyhandicap
Purpose: to apply the handicap to the next round
Parameters:
			rowsize -> determines row size of next board
			HorC -> determines who is handicapped 1 for h and 0 for c
Return Value: void
Algorithm:
		1) Checks to see who won
		2) calculates the number to be covered
		3) checks to see if number to be covered is too high, lowers number until it is on the board
		4) Sets the board to a handicapped one
		5) Sets Hcap bool to be true so that we know we are playing with a handicap
Assistance Received: none
********************************************************************* */
void Game::ApplyHandicap(int rowSize, int HorC) {


	//find sum of digits that player just earned in score
	int handicapNum = 1;
	if (HorC == 1) {
		int tensDigit = scorePlayerEarned / 10;
		int singlesDigit = scorePlayerEarned % 10;
		handicapNum = tensDigit + singlesDigit;
	}
	else if (HorC == 0) {
		int tensDigit = scoreAIEarned / 10;
		int singlesDigit = scoreAIEarned % 10;
		handicapNum = tensDigit + singlesDigit;
	}
	else {
		cout << "ERROR -> never set handicapNum\n Exiting\n";
		exit(1);
	}

	//Account for specific high cases where digits of score add up to more than board size
	if (handicapNum > rowSize) {
		handicapNum = rowSize;
	}

	//Set Handicap On Board
	Board handicapped;
	handicapped.SetSize(rowSize);
	handicapped.CreateNewBoard(g_firstTurn);
	vector<pair<int, bool>> ToSet = handicapped.GetH_Side(); // doesnt matter that we GetH_side cause the new board should be blank
	ToSet[(handicapNum - 1)].second = true;

	//Diff per player
	if (HorC == 1) { // APPLIES ADVANTAGE TO COMPUTER
		handicapped.SetC_Side(ToSet);
	}
	else { //APPLIES ADVANTAGE TO HUMAN
		handicapped.SetH_Side(ToSet);
	}
	currRound.SetBoard(handicapped);

	//Set hCap in Round
	currRound.SetHCap(true);
}

/* *********************************************************************
Function Name: NextRound
Purpose: to play the next round with a loaded board
Parameters:
			none
Return Value: void
Algorithm:
		1) Alternates first turn
		2) Plays the round with a loaded board
Assistance Received: none
********************************************************************* */
void Game::NextRound() {

	//Should Make sure we alternate first turns
		//If Human went first last game
	if (g_firstTurn == 1) {
		g_firstTurn = 0;
	}
	//if com went first last game
	else if (g_firstTurn == 0) {
		g_firstTurn = 1;
	}

	AnnounceWinnerAddScore(currRound.PlayRound());
	currRound.SetScores(scorePlayer, scoreAI);
}

/* *********************************************************************
Function Name: AnnounceWinnerAddScore
Purpose: to see who won the whole game
Parameters:
			score -> holds score (negative if holding COM score)
Return Value: void
Algorithm:
		1) Checks to see who won
		2) Announces round winner appropriately
		3) adds score to total score for player
Assistance Received: none
********************************************************************* */
void Game::AnnounceWinnerAddScore(int score) {
	if (score > 0) {
		cout << "\n\nRound winner is Player1 earning " << score << " points!\n\n";
		scorePlayer = scorePlayer + score;
		scorePlayerEarned = score;
		winner = 1;
	}
	if (score < 0) {

		cout << "\n\nRound winner is Computer earning " << (-1 * score) << " points!\n\n";
		scoreAI = scoreAI + (-1 * score);
		scoreAIEarned = (-1 * score);
		winner = 0;
	}

}

/* *********************************************************************
Function Name: AnnounceOverallWinner
Purpose: to see who won the whole game
Parameters:
			none
Return Value: void
Algorithm:
		1) See whose score was higher or checks for tie
		2) outputs appropriate output
		3) exits with error if it was no one won and there was no tie
Assistance Received: none
********************************************************************* */
void Game::AnnounceOverallWinner() {

	if (scorePlayer > scoreAI) {
		cout << "\n\n\nCONGRATULATIONS! Player 1 has won the game!\n\nNow Exiting\n";
		exit(1);
	}
	else if (scorePlayer < scoreAI) {
		cout << "\n\n\nSorry, player 1 has lost the game...\n\nNow Exiting\n";
		exit(1);
	}
	else if (scorePlayer == scoreAI) {
		cout << "\n\n\nThe Game has ended in a Draw.\n\nNow Exiting\n";
		exit(1);
	}
	else {
		cout << "\n\n\nError determining winner/n/nNow Exiting\n";
		exit(1);
	}
}

/* *********************************************************************
Function Name: PlayGame
Purpose: to play the game
Parameters:
			none
Return Value: void
Algorithm:
		1) Checks if human would like to load a save
		2) Allows human to choose row size
		3) Plays round based off load or row size
		4) Announces scores after round
		5) allows the human to keep playing rounds until they dont want to anymore
		6) Overall winner is announced after a game end
Assistance Received: none
********************************************************************* */
void Game::PlayGame() {

	//Loading from a save mechanic
	do {
		cout << "Would you like to load a game from a file?" << endl << "If yes enter '1'		If no, enter '0'" << endl;
		loadSave = CollectInput();
	} while (loadSave != 1 && loadSave != 0);

	if (loadSave == 1)
	{
		LoadSave();
	}
	else if (loadSave != 0) {
		loadSave = 0;
		cout << "Input read as '0'\n";
	}


	while (keepPlaying == 1) {

		//keepPlaying = 1;

		//This code will Run if no save was loaded
		if (loadSave == 0) {
			//Row size selection mechanic
			do {
				cout << "Please enter the Row Size you would like to play with 9-11" << endl;
				g_rowSize = CollectInput();
			} while (g_rowSize != 9 && g_rowSize != 10 && g_rowSize != 11);

			//Play the Round
			NextRound(g_rowSize);
		}

		//This code will run of we did load a save
		else {
			currRound.SetScores(scorePlayer, scoreAI);
			loadSave = 0;
			NextRound();

		}

		//Keep Playing mechanic --- Will only Run after first round
		if (scoreAI != 0 || scorePlayer != 0) {
			cout << "Current Scores:		Computer: " << scoreAI << "			Human: " << scorePlayer << endl;
			do {
				cout << "Would you like to keep playing? " << endl << "If yes enter '1'		If no, enter '0'" << endl;
				keepPlaying = CollectInput();

			} while (keepPlaying != 1 && keepPlaying != 0);
		}

	}
	AnnounceOverallWinner();

};

/* *********************************************************************
Function Name: LoadSave
Purpose: to read a save file into round object
Parameters:
			none
Return Value: void
Algorithm:
		1) Reads next line from file
		2) if it identifies "Computer:"
		3) Will read in the data for the computer
		4) if it identifies "Human:"
		5) will read in the data for the human
		6) will identify header for data and then read the data into board for human, computer and first turn,
		vector for dice rolls and int for next turn
		7) will then close the load file and continue identifying the next line until there is no more
		data to colelct on the dice or there is no next line
Assistance Received: none
********************************************************************* */
void Game::LoadSave() {
	Board boardFromSave;

	//Read from file
	while (1) {
		string line;

		//Checks if there are any more lines in file (Reads Board if function doesnt return from Dice Read)
		if (!Facc.GetNextLine(line)) {

			//Should have successfull collected Whole Board So now we will set the board
			//First we will see if more than one turn has occured, if there are covered squares, a turn has occured
			for (int i = 0; i < boardFromSave.GetSize(); i++) {
				int count = 0;

				if (boardFromSave.GetC_Side()[i].second == true) {
					count++;
				}
				if (boardFromSave.GetH_Side()[i].second == true) {
					count;
				}
				if (count > 0) {
					//incriment twice so that we don't mess up turn order
					boardFromSave.IncrimentTurnCounter();
					boardFromSave.IncrimentTurnCounter();
					break;
				}
			}
			currRound.SetBoard(boardFromSave);

			return;
		}

		//Will be responsible for retrieving the computer's side of the board and score
		if (line == "Computer:") {

			//Read the Board for the computer
			Facc.GetNextLine(line);
			istringstream Read1(line);
			string Squares; // will hold the string "Squares:"
			string CS[11]; //Computer's Side String array

			Read1 >> Squares;
			for (unsigned int i = 0; i < 11; i++) {
				Read1 >> CS[i];
			}
			//Find out size of the board
			if (CS[9] == "") {
				boardFromSave.SetSize(9);
			}
			else if (CS[10] == "") {
				boardFromSave.SetSize(10);
			}
			else {
				boardFromSave.SetSize(11);
			}

			//Saved computerSide vector pair
			vector<pair<int, bool>> SCS;
			//Read strings into SCS 
			for (int i = 0; i < boardFromSave.GetSize(); i++) {

				if (CS[i] == "*") {
					SCS.push_back(make_pair((i + 1), true));
				}
				else {
					try {
						int x = stoi(CS[i]);
						if (x == (i + 1)) {
							SCS.push_back(make_pair((i + 1), false));
						}
					}
					catch (exception) {
						cout << "\nERROR READING SAVE FILE -> Computer side's " << i << " cannot be read!\n";
						cout << "Must be either a '*' or the appropriate number\n";
						cout << "Appropriate number = " << i << "		string read = " << CS[i] << endl;
						cout << "\n\nEXITING";
						exit(1);
					}

				}
			}

			//Set C_side on the board to = SCS
			if (SCS.size() == boardFromSave.GetSize()) {
				boardFromSave.SetC_Side(SCS);
			}
			else {
				cout << "\n\nERROR -> Computer side board size mismatch\n";
				cout << "Size of board = " << boardFromSave.GetSize() << endl;
				cout << "Size of Computer Board read from save file = " << SCS.size() << endl;
				cout << "Terminating\n";
				exit(1);
			}

			//Read the computer's Score
			Facc.GetNextLine(line);
			istringstream Read2(line);
			string label2;
			string score;
			Read2 >> label2 >> score;
			try {
				scoreAI = stoi(score);
			}
			catch (exception) {
				cout << "Error Reading Computer's Score from file, Terminating Program\n";
				exit(1);
			}
		}

		//Will be responsible for retrieving the human's side of the board and score
		if (line == "Human:") {
			//Read the Board for the Human
			Facc.GetNextLine(line);
			istringstream Read1(line);
			string Squares; // will hold the string "Squares:"
			string HS[11]; //Human's Side String array

			Read1 >> Squares;
			for (unsigned int i = 0; i < 11; i++) {
				Read1 >> HS[i];
			}

			//SavedHumanSide vector pair
			vector<pair<int, bool>> SHS;
			//Read strings into SHS 
			for (int i = 0; i < boardFromSave.GetSize(); i++) {

				if (HS[i] == "*") {
					SHS.push_back(make_pair((i + 1), true));
				}
				else {
					try {
						int x = stoi(HS[i]);
						if (x == (i + 1)) {
							SHS.push_back(make_pair((i + 1), false));
						}
					}
					catch (exception) {
						cout << "\nERROR READING SAVE FILE -> Human side's " << i << " cannot be read!\n";
						cout << "Must be either a '*' or the appropriate number\n";
						cout << "Appropriate number = " << i << "		string read = " << HS[i] << endl;
						cout << "\n\nEXITING";
						exit(1);
					}

				}
			}

			//Set H_side on the board to = SHS
			if (SHS.size() == boardFromSave.GetSize()) {
				boardFromSave.SetH_Side(SHS);
			}
			else {
				cout << "\n\nERROR -> Human side board size mismatch\n";
				cout << "Size of board = " << boardFromSave.GetSize() << endl;
				cout << "Size of Human Board read from save file = " << SHS.size() << endl;
				cout << "Terminating\n";
				exit(1);
			}



			//Read the human's Score
			Facc.GetNextLine(line);
			istringstream Read2(line);
			string label2;
			string score;
			Read2 >> label2 >> score;
			try {
				scorePlayer = stoi(score);
			}
			catch (exception) {
				cout << "Error Reading Human's Score from file\n";
				cout << "Score attempted to be read = " << score << endl;
				cout << "Terminating Program\n";
				exit(1);
			}


		}

		//Sets first turn appropriately
		if (line == "First Turn: Computer") {
			boardFromSave.SetFirstTurn(0);
		}
		if (line == "First Turn: Human") {
			boardFromSave.SetFirstTurn(1);
		}

		//Sets next turn appropriately
		if (line == "Next Turn: Computer") {
			currRound.SetNextTurn(0);
		}
		if (line == "Next Turn: Human") {
			currRound.SetNextTurn(1);
		}

		//Reads Dice, Reads board
		if (line == "Dice:") {

			//Should have successfull collected Whole Board So now we will set the board
			//First we will see if more than one turn has occured, if there are covered squares, a turn has occured
			for (int i = 0; i < boardFromSave.GetSize(); i++) {
				int count = 0;

				if (boardFromSave.GetC_Side()[i].second == true) {
					count++;
				}
				if (boardFromSave.GetH_Side()[i].second == true) {
					count;
				}
				if (count > 0) {
					boardFromSave.IncrimentTurnCounter();
					boardFromSave.IncrimentTurnCounter();
					break;
				}
			}
			currRound.SetBoard(boardFromSave);

			string D1 = "";		//string representing the first dice
			string D2 = "";		//string representing the second dice
			int D1i = 0;		//int representing the first dice
			int D2i = 0;		//int representing the second dice

			//Loop so that we read Dice Rolls until end of File
			while (1) {
				if (!Facc.GetNextLine(line)) {
					currRound.SetDiceRolls(g_diceRolls);
					return;
				}
				istringstream Read3(line);
				D1 = "";
				D2 = "";
				D1i = 0;
				D2i = 0;

				Read3 >> D1 >> D2;

				if (D2 == "") {
					D2 = "0";
				}

				//Two seperate try catch pair so that we can return appropriate errors
				try {
					D1i = stoi(D1);
				}
				catch (exception) {
					cout << "\n\n ERROR -> Cannot read Dice roll = " << D1 << endl;
					cout << "Setting Dice roll to 0\n";
					D1i = 0;
				}
				try {
					D2i = stoi(D2);
				}
				catch (exception) {
					cout << "\n\n ERROR -> Cannot read Dice roll = " << D2 << endl;
					cout << "Setting Dice roll to 0\n";
					D2i = 0;
				}

				g_diceRolls.push_back(make_pair(D1i, D2i));

			}
		}
	}
};

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
int Game::CollectInput() {
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
