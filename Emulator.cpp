#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"
#pragma once



/**/
/*
insertMemory()

NAME

		bool Emulator::insertMemory() - Inserts contents into specific lcoations in memory

SYNOPSIS

		bool Emulator::insertMemory(int a_location, long long a_contents);

			a_location		--> a number representing the locataion in memory
			a_contents		--> a number representing the informations stored at that memory

DESCRIPTION

		This function calls takes in a location and the contents
		and then stores the contents at the location in m_memory
		It also checks if the locaation is within bounds and 
		returns an error and false if the location is out of bounds
		

RETURNS

		Returns false if the location is out of bounds and
		true if the location is within bunds and memory can
		be inserted properly

AUTHOR

		Ryan Garaffa

DATE

		3:54pm 12/19/2021

*/
/**/

bool Emulator::insertMemory(int a_location, long long a_contents) {

	if (InBounds(a_location)) {
		m_memory[a_location] = a_contents;
		return true;

	}
	else {
		string tempErrorStr = "Location out of bounds";
		cout << endl << tempErrorStr << endl << endl;
		//pushback to error vector ////////////////////////////////////////////////////COME BACK ERROR
		return false;
	}

	return true;
};


/**/
/*
runProgram()

NAME

		runProgram() - Begins running the program

SYNOPSIS

		bool Emulator::runProgram(vector<pair <int, string>> a_instructions);

			a_instructions	--> a vector of input containing the location and contents
			

DESCRIPTION

		This function will first call the insert memory function to insert
		everything into the memory. Then it will go through starting at
		location 100 and read the contents. If it is a machine langauge
		instruction, it will decode it and call the appropriate opcode
		function.


RETURNS

		Returns false if the program runs into a fatal error
		Returns true if everything runs smoothly

AUTHOR

		Ryan Garaffa

DATE

		4:19pm 12/19/2021

*/
/**/

bool Emulator::runProgram(vector<pair <int, string>> a_instructions) {

	//Insert Everything needed into the memory of VC1620
	for (unsigned int i = 0; i < a_instructions.size(); i++) {

		//Convert String passed into long long using 
		long long a_contents = 0;
		stringstream ss;
		ss << a_instructions[i].second;
		ss >> a_contents;
		ss.clear();

		//call insertMemory in loop
		insertMemory(a_instructions[i].first, a_contents);

	}


	//cycle through intructions and execute them one by one
	m_loc = start;

	for (; ;) {

		//collects data from memory at current location
		//stores it in variables with names that make sense
		OpCode = m_memory[m_loc] / 10'000'000'000;
		int BothOperands = m_memory[m_loc] % 10'000'000'000;
		Operands.first = BothOperands / 100'000;
		Operands.second = BothOperands % 100'000;

		//Checks if is assembly code and skips it
		if (OpCode == 0) {
			if (Operands.second != 0) {

			}

			m_loc++;
			continue;
		}

		else if (OpCode == 1) {
			Add();
			m_loc++;
		}
		else if (OpCode == 2) {
			Subtract();
			m_loc++;
		}
		else if (OpCode == 3) {
			Multiply();
			m_loc++;
		}
		else if (OpCode == 4) {
			Divide();
			m_loc++;
		}
		else if (OpCode == 5) {
			Copy();
			m_loc++;
		}
		else if (OpCode == 7) {
			Read();
			m_loc++;
		}
		else if (OpCode == 8) {
			Write();
			m_loc++;
		}
		else if (OpCode == 9) {
			Branch();
		}
		else if (OpCode == 10) {
			BranchMinus();
		}
		else if (OpCode == 11) {
			BranchZero();
		}
		else if (OpCode == 12) {
			BranchPostitive();
		}
		else if (OpCode == 13) {
			Halt();
		}
		else {
			m_loc++;
		}

		if (isdone) {
			cout << endl << "End Of Emulation" << endl;
			return true;
		}


	}

};

//add operand1 and operand2 and store in operand1' memory location
void Emulator::Add() {

	m_memory[Operands.first] = m_memory[Operands.first] + m_memory[Operands.second];
};

//subtract operand2 from operand1 and store in operand1' memory location
void Emulator::Subtract() {
	m_memory[Operands.first] = m_memory[Operands.first] - m_memory[Operands.second];
};

//multiply operand1 by operand2 and store in operand1' memory location
void Emulator::Multiply() {
	m_memory[Operands.first] = m_memory[Operands.first] * m_memory[Operands.second];
};

//divide operand1 by operand2 and store in operand1' memory location
void Emulator::Divide() {
	m_memory[Operands.first] = m_memory[Operands.first] / m_memory[Operands.second];
};

//sets operand1's location in memory = to operand2's location in memory
void Emulator::Copy() {
	m_memory[Operands.first] = m_memory[Operands.second];
};

//takes in an input long long from the terminal and stores it at operand1's lcoation in memory
void Emulator::Read() {
	long long input;
	cout << "? ";
	cin >> input;
	m_memory[Operands.first] = input;
};

//displays the contents of the memory at the location of the first operand
void Emulator::Write() {
	cout << m_memory[Operands.first] << endl;
};

//sets the location to the first operand
void Emulator::Branch() {
	m_loc = m_memory[Operands.first];

};

//sets the location to the first operand if the second operand is negative
void Emulator::BranchMinus() {
	if (m_memory[Operands.second] < 0) {
		m_loc = Operands.first;
	}
	else {
		m_loc++;
	}
};

//sets the location to the first operand if the second operand is zero
void Emulator::BranchZero() {
	if (m_memory[Operands.second] == 0) {
		m_loc = Operands.first;
	}
	else {
		m_loc++;
	}
};

//sets the location to the first operand if the second operand is positive
void Emulator::BranchPostitive() {
	if (m_memory[Operands.second] > 0) {
		m_loc = Operands.first;
	}
	else {
		m_loc++;
	}
};

//Sets isdone to true so that program will stop
void Emulator::Halt() {
	isdone = true;
};
