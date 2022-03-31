#include "stdafx.h"
#include "Strategy.h"

//STRATEGY CALCULATION FUNCTIONS
//Will Calculate the best number of dice to roll
void Strategy::NumDiceCalc(Board currBoard, vector<pair<int, bool>> p_Side) {
	int count = currBoard.GetSize() - 6;
	for (int i = 6; i < currBoard.GetSize(); i++) {
		if (p_Side[i].second == true) {
			count--;
		}
		if (count == 0) {
			bestNumDice = 1;
			return;
		}
	}
	bestNumDice = 2;
}

//Will Calculate whether its better to cover or uncover
void Strategy::CoverCalc(Board currBoard, int roll, vector<pair<int, bool>> o_Side) {
	//If they can uncover, they will
	if (CanUncover(roll, o_Side)) {
		coverDecision = 1;  //Represents uncover
		coverDec = true;	//uncover
	}
	else {
		coverDecision = 0;	//Represents cover
		coverDec = false;	//cover
	}
}

/* *********************************************************************
Function Name: NumberSelectCalc
Purpose: to return the best numbers to play
Parameters:
			currBoard -> current board
			roll -> current roll
			o_Side -> opponents side
			p_Side -> players side
			covDec - > cover decision
Return Value: vector of numbers to play
Algorithm:
		1) Will find out the current side we are dealing with based off the baord and cover decision
		2) Will eliminate any numbers that do not apply to the cover decision
		3) Will Check Every combination of numbers on the current side to see if any sum up to roll
		4) Will return that vector of numbers
Assistance Received: none
********************************************************************* */
vector<int> Strategy::NumberSelectCalc(Board currBoard, int roll, vector<pair<int, bool>> o_Side, vector<pair<int, bool>> p_Side, int covDec) {

	//WIll reset NumberSelect vector
	NumberSelect.clear();

	//Will Decide whether to Uncover or Cover
	//CoverCalc(currBoard, roll, o_Side);
	coverDecision = covDec;
	coverDec = covDec;

	//Vector representing the current side that this function will select numbers from
	vector<pair<int, bool>> CURR_Side;

	//Determines side we will select numbers from based off cover decision
	if (coverDecision == 0) {
		CURR_Side = p_Side;
	}
	else {
		CURR_Side = o_Side;
	}

	//loop through and get rid of all the board numbers that will not satisfy coverdec and cannot be played
	for (unsigned int i = 0; i < CURR_Side.size(); i++) {
		//compare CURR_Side.second to cover decision
		//Empty out CURR_Side so that we only see whats actually available
		if (CURR_Side[i].second != coverDec) {
			CURR_Side.erase(CURR_Side.begin() + i);
			i--;
		}
		else if (CURR_Side[i].first > roll) {
			CURR_Side.erase(CURR_Side.begin() + i);
			i--;
		}
	}

	//Checks a bunch of combinations of the vector
	for (int i = (CURR_Side.size() - 1); i >= 0; i--) {
		if (CURR_Side[i].first == roll) {
			NumberSelect.push_back(CURR_Side[i].first);
			return NumberSelect;
		}
		//Will check combinations of the number in CURR_Side ONLY IF it is big enough 
		if (CURR_Side.size() > 1) {
			for (int j = (i-1); j >= 0; j--) {
				if (CURR_Side[i].first + CURR_Side[j].first == roll) {

					NumberSelect.push_back(CURR_Side[i].first);
					NumberSelect.push_back(CURR_Side[j].first);
					return NumberSelect;
				}
				if (CURR_Side.size() > 2) {
					for (int k = (j-1); k >= 0; k--) {
						if (CURR_Side[i].first + CURR_Side[j].first + CURR_Side[k].first == roll) {

							NumberSelect.push_back(CURR_Side[i].first);
							NumberSelect.push_back(CURR_Side[j].first);
							NumberSelect.push_back(CURR_Side[k].first);
							return NumberSelect;
						}
						if (CURR_Side.size() > 3) {
							for (int h = (k-1); h >= 0; h--) {
								if (CURR_Side[i].first + CURR_Side[j].first + CURR_Side[k].first + CURR_Side[h].first == roll) {

									NumberSelect.push_back(CURR_Side[i].first);
									NumberSelect.push_back(CURR_Side[j].first);
									NumberSelect.push_back(CURR_Side[k].first);
									NumberSelect.push_back(CURR_Side[h].first);
									return NumberSelect;
								}
							}
						}
					}
				}
			}
		}
	}

	return NumberSelect;
}

/* *********************************************************************
Function Name: CanUncover
Purpose: to see if it is possible to uncover
Parameters:
			roll -> current roll
			o_Side -> opponents side
Return Value: bool, either can or cant
Algorithm:
		1)create a new vector based off o_side except we eliminate all uncovered options
		2) Check this new vector for every combination of numbers inside of it
		3) if it finds a combination that can add up to roll, it will return true
		4) if it cannot find a combination, iot will return false
Assistance Received: none
********************************************************************* */
bool Strategy::CanUncover(int roll, vector<pair<int, bool>> o_Side) {

	//Vector representing the uncovered numbers on the opponents side
	vector<int> o_SU;


	//Gather a vector of all the covered numbers
	for (unsigned int i = 0; i < o_Side.size(); i++) {
		if (o_Side[i].second) {
			o_SU.push_back(o_Side[i].first);
		}
	}

	//Checks a bunch of combinations of the vector
	for (unsigned int i = 0; i < o_SU.size(); i++) {
		if (o_SU[i] == roll) {
			return true;
		}
		//Will check combinations of the number in o_SU ONLY IF it is big enough 
		if (o_SU.size() > 0) {
			for (unsigned int j = 1; j < o_SU.size(); j++) {
				if ((o_SU[i] + o_SU[j]) == roll) {
					return true;
				}
				if (o_SU.size() > 1) {
					for (unsigned int k = 2; k < o_SU.size(); k++) {
						if ((o_SU[i] + o_SU[j] + o_SU[k]) == roll) {
							return true;
						}
						if (o_SU.size() > 2) {
							for (unsigned int h = 3; h < o_SU.size(); h++) {
								if ((o_SU[i] + o_SU[j] + o_SU[k] + o_SU[h]) == roll) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	//returns false otherwise
	return false;

}

//Accesor for bestNumdice
int Strategy::GetBestNumDice() {
	return bestNumDice;
}

//accesor for coverdecision
int Strategy::GetCoverDecision() {
	return coverDecision;
}

//accesor for NumberSelect
vector<int>	Strategy::GetNumberSelect() {
	return NumberSelect;
}

//Mutator for cover decision
void Strategy::SetCoverDecision(int toSet) {
	coverDec = coverDecision = toSet;
}