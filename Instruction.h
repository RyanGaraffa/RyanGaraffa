//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

	Instruction() { };
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage, 	// A machine language instruction.
		ST_AssemblerInstr,  		// Assembler Language instruction.
		ST_Comment,          		// Comment or blank line
		ST_End                   		// end instruction.
	};

	// Parse the Instruction.
	InstructionType ParseInstruction(string a_line); 

	//Professor's Code
	bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode, string& a_Operand1, string& a_Operand2);
	

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc); 

	//Calls Translate function and then adds the translations to vector<pair <int, string>> m_Translations
	void AddTranslation(int a_loc, map<string, int> a_Map); 

	//Prints a Header for Translations
	void PrintTranslationHeader();

	//Translates instruction and Operands into machine language string
	string Translate(map<string, int> a_Map);

	//To access the origional instruction
	inline string &GetOrigional() { return m_instruction; };

	// To access Operands 
	inline string &GetOperand1() { return m_Operand1; };
	inline string &GetOperand2() { return m_Operand2; };

	// To access OpCode
	inline string &GetOpCode() { return m_OpCode; };

	// To access translations vector pair
	inline vector<pair <int, string>> &GetTranslations() { return m_Translations; };

	// To access the label
	inline string &GetLabel() { return m_Label; };

	// To determine if a label is blank.
	inline bool isLabel() { return !m_Label.empty(); };

	//Check for Errors
	void CheckForErrors(map<string, int> a_Map);

private:

	// The elemements of a instruction
	string m_Label;									// The label.
	string m_OpCode;								// The symbolic op code.
	string m_Operand1;								// The first operand. 
	string m_Operand2;								// The second operand.


	string m_instruction;							// The original instruction.

	// Derived values.
	int m_NumOpCode;								// The numerical value of the op code for machine language equivalents.
	InstructionType m_type;							// The type of instruction.

	bool m_IsNumericOperand1;						// == true if the operand is numeric.
	int m_Operand1Value;							// The value of the operand if it is numeric.

	vector<pair <int, string>> m_Translations;		//the int is the loc and the string is the 12digit number
	//vector<pair <int, string>> m_locations;			//locations of labels

	//A map to translate OpCode words into OpCode Numbers
	map<string, string> opCodeInfo =
	{
		{ "ADD", "01" },{ "SUB", "02" },{ "MULT", "03" }, { "DIV", "04" }, { "COPY", "05" }, { "READ", "07" },{ "WRITE", "08" },{ "B", "09" },
		{ "BM", "10" },{ "BZ", "11" },{ "BP", "12" },{ "HALT", "13" },{ "DC", "00" },{ "DS", "00" },{ "ORG", "00" },{ "END", "00" },

		{ "add", "01" },{ "sub", "02" },{ "mult", "03" }, { "div", "04" }, { "copy", "05" }, { "read", "07" },{ "write", "08" },{ "b", "09" },
		{ "bm", "10" },{ "bz", "11" },{ "bp", "12" },{ "halt", "13" },{ "dc", "00" },{ "ds", "00" },{ "org", "00" },{ "end", "00" }
	};

	vector<string> digits = {"1", "2", "3", "4", "5", "6", "7", "8", "9" };
};