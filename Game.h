/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga											*
* Class : #6 Game 											*
* Date : 2/12/2022											*
************************************************************
*/
//Header File for Game Class

#pragma once

#include "Round.h"
#include "FileAccess.h"
#include "Dice.h"

class Game {
public:
	//constructors
	Game() {
		scorePlayer = 0;
		scoreAI = 0;
		g_rowSize = 9;	
		keepPlaying = 1;			
		loadSave = 0;

		Round currRound;
		FileAccess Facc;
	};

	Game(int argc, char *argv[]) 
		:Facc(argc, argv)
	{
		scorePlayer = 0;
		scoreAI = 0;
		g_rowSize = 9;
		keepPlaying = 1;
		loadSave = 0;

		currRound = Round();
	}

	//destructor
	~Game() {};

	//Will Play the game, works in a loop until player doesnt want to play anymore, pass on needed info to round object
	void PlayGame();

	//will play the round normally without any loaded data
	void NextRound(int l_rowSize);

	//Will play the round with all of the loaded data
	void NextRound();

	void AnnounceWinnerAddScore(int score);

	//Will Set handicapp
	void ApplyHandicap(int rowSize, int HorC);

	//Announce Overall Winner
	void AnnounceOverallWinner();

	//Function that will load a savestate from an input file
	void LoadSave();

	//Collects input and makes sure program does not crash with garbage input
	int CollectInput();

private: 

	int scorePlayer = 0;			//will be used to track the score of the player
	int scorePlayerEarned = 0;			//will keep track of how much score the player JUST Earned for the handicap
	int scoreAI = 0;				//will be used to track the score of the AI
	int scoreAIEarned = 0;				//will keep track of how much score the AI JUST Earned for the handicap
	int g_rowSize= 9;				//Will keep track of row size for each round
	int keepPlaying = 1;			//will be used to determine if game continues
	int loadSave = 0;				//Wanted to Use bools but kept crashing with non binary digits
	int g_firstTurn;				//Used to keep track of the first turn 1 for human and 0 for computer
	int winner = 2;						//Used to set handicap, 1 for human and 0 for computer

	Round currRound;				//Round object in Game class
	FileAccess Facc;			//FileAccess Object to read from the save

	//vector holding all the logged dice rolls
	vector < pair<int, int>> g_diceRolls = {};

};
