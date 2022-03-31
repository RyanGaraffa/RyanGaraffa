/*
************************************************************
* Name:  Ryan Garaffa										*
* Project : Canoga.cpp										*
* Class : #1 Main											*
* Date : 2/12/2022											*
************************************************************
*/
// Canoga.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include "stdafx.h"
#include "Game.h"

#include <iostream>

/* *********************************************************************
Function Name: main
Purpose: To Run the Game
Parameters:
			int argc -> holds the number of command line arguements
			char *argv[] -> holds the command line arguements in a char array
Return Value: int representing nothing
Algorithm:
		1) Create game object
	   2) play the game
Assistance Received: none
********************************************************************* */

int main(int argc, char *argv[])
{
	
	//Detects if command line arguement is empty
	if(argc == 1) {
		//Create Game Object with defualt constructor
		Game Canoga;

		//Run Game
		Canoga.PlayGame();
	}

	//Will Load save from File if selected
	else {
		//Create Game Object with constructor that loads save
		Game Canoga(argc, argv);

		//Run Game
		Canoga.PlayGame();
	}

}