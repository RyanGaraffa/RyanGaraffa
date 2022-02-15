//
//  Implementation of Instruction class.
//
#include "stdafx.h"
#include <sstream>
using namespace std;
#include "Instruction.h"
#include "Errors.h"

/**/
/*
ParseInstruction()

NAME

		ParseInstruction() - Reads line and returns appropriate type

SYNOPSIS

		Instruction::InstructionType Instruction::ParseInstruction(string a_line);

			a_line	--> a string holding the current line


DESCRIPTION

		This function will call the ParseIntoFields() function. Based off of what
		that functions sets the m_inst variables to, this function will determine
		the type of line that is being read. It will return the appropriate type.


RETURNS

		Returns an instruction type based off of the line

AUTHOR

		Ryan Garaffa & Victor Miller

DATE

		4:19pm 12/19/2021

*/
/**/

//Some Professor's Code
Instruction::InstructionType Instruction::ParseInstruction(string a_line) { // Largely Professor's Code 
	m_instruction = a_line;
	size_t isemi1 = a_line.find(';');
	if (isemi1 != string::npos)
	{
		a_line.erase(isemi1);
		if (a_line.empty()) {
			m_type = ST_Comment;
			return ST_Comment;
		}
	}
		ParseLineIntoFields(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2); // This should set m_variables using the input line
		//Check for end
	if (m_OpCode == "end" || m_OpCode == "End" || m_OpCode == "END") {
		m_type = ST_End;
		return ST_End;
	}
		//Check for assmbly language
	else if (m_OpCode == "DS" || m_OpCode == "ds") {
		m_type = ST_AssemblerInstr;
		return ST_AssemblerInstr;
	}
	else if (m_OpCode == "ORG" || m_OpCode == "org" || m_OpCode == "Org") {
		m_type = ST_AssemblerInstr;
		return ST_AssemblerInstr;
	}
	else if (m_OpCode == "dc" || m_OpCode == "DC") {
		//m_Operand2 = m_Operand1;
		m_type = ST_AssemblerInstr;
		return ST_AssemblerInstr;
	}
		// Rest should be machine language. Beter Check Occurs later
	else if (m_OpCode != "") {
		m_type = ST_MachineLanguage;			
		return ST_MachineLanguage;
	}

	
	m_type = ST_Comment;
	return ST_Comment;
};

/**/
/*
ParseLineIntoFields()

NAME

		ParseLineIntoFields() - Begins running the program

SYNOPSIS

		bool Instruction::ParseLineIntoFields(string a_line, 
			string& a_label, string& a_OpCode, string& a_Operand1, string& a_Operand2);

			a_line		--> string holding the current line
			a_label		--> string holding m_label from m_inst
			a_OpCode	--> string holding m_OpCode from m_inst
			a_Operand1	--> string holding m_Operand1 from m_inst
			a_Operand2	--> string holding m_Operand2 from m_inst

DESCRIPTION

		This function will read in the line and store the appropriate variables
		into their appropriate places in the instruction class. It detects whether
		or not there is a label and acts accordingly. It also returns false if
		it was not able to read everything from the line, if there was excess.


RETURNS

		Returns false if there is more in the line that function did not read
		otherwise returns true

AUTHOR

		Victor Miller

DATE

		5:04pm 12/19/2021

*/
/**/

//Professors Code
bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode, string& a_Operand1, string& a_Operand2) { // PROFFESSOR'S CODE
	// Get rid of any commas from the line.
	replace(a_line.begin(), a_line.end(), ',', ' ');

	// Get the elements of the line.  That is the label, op code, operand1, and operand2.
	string endStr;
	a_label = a_OpCode = a_Operand1 = a_Operand2 = "";
	istringstream ins(a_line);
	if (a_line[0] == ' ' || a_line[0] == '\t')
	{
		a_label = "";
		ins >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
	}
	else
	{
		ins >> a_label >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
	}
	// If there is extra data, return false. return error
	if (!endStr.empty()) {
		string currError = "Error after parsing line: ";
		cout << currError << a_line << endl;
		Errors::RecordError(currError); 
	}
	return endStr.empty() ? true : false;
}

/**/
/*
LocationNextInstruction()

NAME

		LocationNextInstruction - Finds the location of the next Instruction Based off the current instruction

SYNOPSIS

		int Instruction::LocationNextInstruction(int a_loc);

			a_loc	--> an int representing the current location


DESCRIPTION

		This function will read in the current location and return the
		location of the next instruction accounting for assembly language
		instructions.


RETURNS

		Returns an integer representing the next location

AUTHOR

		Ryan Garaffa

DATE

		4:59pm 12/19/2021

*/
/**/

int Instruction::LocationNextInstruction(int a_loc) {
	if (a_loc > 99999 || a_loc < 0) {
		string currError = "Location Out of Bounds";
		Errors::RecordError(currError);
	}
	
	if (m_type == ST_AssemblerInstr) {

		int x;
		stringstream ss(m_Operand1);
		ss >> x;

		if (m_OpCode == "DS" || m_OpCode == "ds") {
			return (a_loc + x);
		}
		else if (m_OpCode == "DC" || m_OpCode == "dc") {
			return (a_loc + 1);
		}
		else if (m_OpCode == "ORG" || m_OpCode == "org") {
			return x;
		}

	}
	return a_loc + 1;

};

/**/
/*
AddTranslation()

NAME

		AddTranslation() - Adds the translated machine code to translations vector

SYNOPSIS

		void Instruction::AddTranslation(int a_loc, map<string, int> a_Map);

			a_loc	--> a location to add to the translations vector
			a_Map	--> a map representing the symbol table used for passing to Translate function


DESCRIPTION

		This function will first check if the location is within memory. Then
		it will call the translate function to gather the machine language
		string.Then it will output the want output to the terminal and push
		back the translations vector with appropriate machine langauge code
		and location. This creates a vector of nistructions to pass to the 
		emulator.

RETURNS

		Returns void

AUTHOR

		Ryan Garaffa

DATE

		4:56pm 12/19/2021

*/
/**/

//Calls Translate function and then adds the translations to vector<pair <int, string>> m_Translations
void Instruction::AddTranslation(int a_loc, map<string, int> a_Map) {

	//Check if we are within 100000 memory limit
	if (a_loc > 99999 || a_loc < 0) {
		string currError = "Location Out of Bounds";
		cout << currError << endl;
		Errors::RecordError(currError);
	}

	string machineLang = Translate(a_Map);


	if (m_type == ST_AssemblerInstr) {
		if (m_OpCode == "dc" || m_OpCode == "DC") {
			cout << a_loc << "		" << machineLang << "		" << m_instruction << endl;
			m_Translations.push_back(make_pair(a_loc, machineLang));
		}
		else {
			cout << a_loc << "					" << m_instruction << endl;
			m_Translations.push_back(make_pair(a_loc, machineLang));
		}
	}
	else {
		cout << a_loc << "		" << machineLang << "		" << m_instruction << endl;
		m_Translations.push_back(make_pair(a_loc, machineLang));
	}

	/*
	The 12 digit number is the OpCode(2), then the location of operand1 (5), and then the location of operand 2 (5)
	*/
};

//Prints a Header for Translations
void Instruction::PrintTranslationHeader() {
	cout << "Translation of Program:" << endl << endl;
	cout << "Location" << "	Contents" << "		Origional Statement" << endl;
};

/**/
/*
Translate()

NAME

		Translate() - Translates an instruction into machine langauge

SYNOPSIS

		string Instruction::Translate(map<string, int> a_Map);

			a_Map	--> a map representing the symbol table used to check for Assembly Lang


DESCRIPTION

		This function will Translate the instruction into machine langauge.
		It will return a string so that we can keep track of necassary 0's
		out front.

RETURNS

		Returns a string of the machine language code.

AUTHOR

		Ryan Garaffa

DATE

		4:52pm 12/19/2021

*/
/**/

string Instruction::Translate(map<string, int> a_Map) {

	string machineLang = "";
	string Op1Loc;
	string Op2Loc;
	stringstream ss;

	CheckForErrors(a_Map);

	if (a_Map[m_Operand2] == 0) {
		if (m_type == ST_AssemblerInstr) {
			if (m_OpCode == "dc" || m_OpCode == "DC") {
				ss << m_Operand1;
				ss >> Op2Loc;
				ss.clear();

				if (Op2Loc.size() < 5) {
					for (int i = Op2Loc.size(); i < 5; i++) {
						Op2Loc = "0" + Op2Loc;
					}
				}
			}
		}
		else { Op2Loc = "00000"; }
		ss << a_Map[m_Operand1];
		ss >> Op1Loc;

		if (Op1Loc.size() < 5) {
			for (int i = Op1Loc.size(); i < 5; i++) {
				Op1Loc = "0" + Op1Loc;
			}
		}

		machineLang += opCodeInfo[m_OpCode];
		machineLang += Op1Loc;
		machineLang += Op2Loc;
		return machineLang;
	}
	else {

		ss << a_Map[m_Operand1];
		ss >> Op1Loc;
		ss.clear();
		ss << a_Map[m_Operand2];
		ss >> Op2Loc;

		//Fill out Operand Locations with zeros
		if (Op1Loc.size() < 5) {
			for (int i = Op1Loc.size(); i < 5; i++) {
				Op1Loc = "0" + Op1Loc;
			}
		}
		if (Op2Loc.size() < 5) {
			for (int i = Op2Loc.size(); i < 5; i++) {
				Op2Loc = "0" + Op2Loc;
			}
		}

		//Create the full string and return it
		machineLang += opCodeInfo[m_OpCode];
		machineLang += Op1Loc;
		machineLang += Op2Loc;

		//Final check to see if translation is correct
		if (machineLang.size() != 12) {
			string currError = "Did Not properly translate input";
			cout << currError << endl;
			Errors::RecordError(currError);
		}

		return machineLang;
	}
}

/**/
/*
CheckForErrors()

NAME

		CheckForErrors() - Checks for Errors while translating

SYNOPSIS

		void Instruction::CheckForErrors(map<string, int> a_Map);

			a_Map	--> a map representing the symbol table used to check for Assembly Lang


DESCRIPTION

		This function will Check for some Errors before following through with the translation

RETURNS

		Returns void

AUTHOR

		Ryan Garaffa

DATE

		7:26pm 12/19/2021

*/
/**/

void Instruction::CheckForErrors(map<string, int> a_Map) {
	string OpCodeNum = opCodeInfo[m_OpCode];

	//checks if we can read the OpCode Number Properly
	if (OpCodeNum == "") {
		string currError = "Invalid OpCode OR did not properly read OpCode";
		cout << currError << endl;
		Errors::RecordError(currError);
	}
	
	//Checks that add, sub, mult, div, copy, BM, BZ, and BP have 2 operands
	if (OpCodeNum == "01" || OpCodeNum == "02" || OpCodeNum == "03" || OpCodeNum == "04" || OpCodeNum == "05"
		|| OpCodeNum == "10" || OpCodeNum == "11" || OpCodeNum == "12") {
		if (m_Operand1 == "") {
			string currError = "Need Two Operands, could not read Operand 1";
			cout << currError << endl;
			Errors::RecordError(currError);
		}
		else if (m_Operand2 == "") {
			string currError = "Need Two Operands, could not read Operand 2";
			cout << currError << endl;
			Errors::RecordError(currError);
		}
	}

	//Checks for Syntax Errors --> add, sub, mult, and div must be symbolic
	if (OpCodeNum == "01" || OpCodeNum == "02" || OpCodeNum == "03" || OpCodeNum == "04") {
		for (int i = 0; i < 9; i++) {
			if (m_Operand1 == digits[i]){
				string currError = "Add, Subtract, Multiply, and Divide Must take in Symbolic Operands";
				cout << currError << endl;
				Errors::RecordError(currError);
			}
			if (m_Operand2 == digits[i]) {
				string currError = "Add, Subtract, Multiply, and Divide Must take in Symbolic Operands";
				cout << currError << endl;
				Errors::RecordError(currError);
			}
		}
	}

	//Checks if Constant is too large for Vc1620 Memory
	if (m_Operand1.size() > 5) {
		string currError = "Operand1 is too big for Memory";
		cout << currError << endl;
		Errors::RecordError(currError);
	}
	else if (m_Operand2.size() > 5) {
		string currError = "Operand2 is too big for Memory";
		cout << currError << endl;
		Errors::RecordError(currError);
	}

}