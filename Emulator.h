//
//		Emulator class - supports the emulation of VC1620 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class Emulator {

public:

	const static int MEMSZ = 100'000;	// The size of the memory of the VC1620.
	Emulator() {
		m_memory.resize(MEMSZ, 0);
	}

	// Records instructions and data into VC1620.
	bool insertMemory(int a_location, long long a_contents);

	// Runs the VC1620 program recorded in memory.
	bool runProgram(vector<pair <int, string>> a_instructions);

private:

	vector<long long> m_memory;  			// Memory for the VC1620 stores strings of int
	long long m_loc;								// holds current location
	bool isdone = false;					//indicates if the program is done
	int start = 100;							//indicates start of program in memory
	long long OpCode = 0;
	pair<long long, long long> Operands;				//holds Operands 1 and 2 seperately

	//Function to check if a location is within the VC1620's memory
	bool InBounds(int a_loc) {
		if (a_loc < MEMSZ && a_loc > -1) {
			return true;
		}
		else {
			string tempErrorStr = "location is out of bounds";
			cout << endl << tempErrorStr << endl << endl;
			//Errors::m_ErrorMsgs.push_back(tempErrorStr); ///////////////////////////////////////////ERRORS COME BACK HERE
			return false;
		}
	};

	void Add();
	void Subtract();
	void Multiply();
	void Divide();
	void Copy();
	void Read();
	void Write();
	void Branch();
	void BranchMinus();
	void BranchZero();
	void BranchPostitive();
	void Halt();
};

#endif