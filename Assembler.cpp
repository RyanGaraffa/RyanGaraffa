//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler()
{
}

/**/
/*
void Assembler::PassI() 

NAME

		void Assembler::PassI() - Creates and displays symbol table

SYNOPSIS

		void Assembler::PassI();

			FileAccess m_facc;	    --> FileAccess object
			SymbolTable m_symtab;	--> Symbol Table object
			Instruction m_inst;	    --> Instruction object
			Emulator m_emul;        --> emulator object

DESCRIPTION

		This function will pass through every line of the input file and
		collect labels from each line. If the line does not have a label,
		then the function will just do nothing and continue to the next
		line. The function also keeps track of the current location and 
		records the location and label for each symbol found.

RETURNS

		Returns void

AUTHOR

		Victor Miller & Ryan Garaffa

DATE

		3:45pm 12/19/2021

*/
/**/


void Assembler::PassI(){
	int loc = 0;        // Tracks the location of the instructions to be generated.

	// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string line;
		if (!m_facc.GetNextLine(line)) {

			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(line);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement and report an error if it isn't.
		if (st == Instruction::ST_End){
			return;
		}
		// Labels can only be on machine language and assembler language
		// instructions.  So, skip comments.
		if (st == Instruction::ST_Comment)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the symbol table.
		if (m_inst.isLabel()) {
			m_symtab.AddSymbol(m_inst.GetLabel(), loc);

		}
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
	
}

/**/
/*
void Assembler::PassII()

NAME

		void Assembler::PassII() - Gathers locations, contents, and the origional statements into a neat table

SYNOPSIS

		void Assembler::PassII();

			FileAccess m_facc;	    --> FileAccess object
			SymbolTable m_symtab;	--> Symbol Table object
			Instruction m_inst;	    --> Instruction object
			Emulator m_emul;        --> emulator object

DESCRIPTION

		This function will pass through every line of the input file and
		collect data from it. It will store all needed information in the
		variables of the instruction object (like label, opcode, and the 
		Operands). It will also translate opcode and operands into machine
		langauge or assembly intructions and then store this information
		in a vector in the instruction class. Finally, It will output the
		second table showing the location, contents, and origional statement
		for each line. This Function should also collect all the errors 
		within the input file.

RETURNS

		Returns void

AUTHOR

		Victor Miller & Ryan Garaffa

DATE

		3:50pm 12/19/2021

*/
/**/

void Assembler::PassII(){
	int loc = 0;        // Tracks the location of the instructions to be generated.
	m_facc.rewind();	// reads file from beginning

	Errors::InitErrorReporting();
	string currError = "";

	//Print header for second table
	m_inst.PrintTranslationHeader();

	// Successively process each line of source code.
	for (; ; ) {

		string line; // Read the next line from the source file.

		if (!m_facc.GetNextLine(line)) {	// If there are no more lines, we are missing an end statement
			currError = "Missing end statement";
			cout << currError << endl;
			Errors::RecordError(currError);
			return;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(line);

		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement and report an error if it isn't.
		if (st == Instruction::ST_End) { 
			cout << "					" << m_inst.GetOrigional() << endl;
			
			if (m_facc.GetNextLine(line)) {
				currError = "More After End Statement";
				cout << currError << endl;
				Errors::RecordError(currError);
			}

			cout << endl << "Type Anything To Continue to Emulator" << endl << endl;
			string EnterToContinue;
			cin >> EnterToContinue;

			return; 
		};

		// Labels can only be on machine language and assembler language
		// instructions.  So, skip comments.
		if (st == Instruction::ST_Comment)
		{
			cout << "					" << m_inst.GetOrigional() << endl;
			continue;
		}


		if ((st == Instruction::ST_AssemblerInstr) || (st == Instruction::ST_MachineLanguage)) { // store code to m_translations and output to table.
			m_inst.AddTranslation(loc, m_symtab.GetMap());
		}
		loc = m_inst.LocationNextInstruction(loc);
		// Compute the location of the next instruction.

	}

	Errors::DisplayErrors();

}

/**/
/*
RunProgramInEmulator()

NAME

		RunProgramInEmulator() - Begins running the emulator

SYNOPSIS

		RunProgramInEmulator();

			FileAccess m_facc;	    --> FileAccess object
			SymbolTable m_symtab;	--> Symbol Table object
			Instruction m_inst;	    --> Instruction object
			Emulator m_emul;        --> emulator object

DESCRIPTION

		This function calls the run program function on the m_emul
		object. It passes a vector of locations and machine langauge
		strings from the instruction class.

RETURNS

		Returns void

AUTHOR

		Ryan Garaffa

DATE

		3:54pm 12/19/2021

*/
/**/

void Assembler::RunProgramInEmulator() {
	m_emul.runProgram(m_inst.GetTranslations());
}
