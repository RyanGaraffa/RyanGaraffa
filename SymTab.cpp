//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"
#include "Errors.h"

/**/
/*
AddSymbol()

NAME

		AddSymbol() - Adds a symbol to the SymbolTable

SYNOPSIS

		void SymbolTable::AddSymbol( const string &a_symbol, int a_loc );

			a_symbol	--> a string holding the label
			a_loc		--> integer holding the location of symbol


DESCRIPTION

		This function will check if a symbol is already in the table, and then
		if it is, the function will set the location of that symbol as -999. 
		If the symbol is not currently in the table, it will be added into 
		the symbol Table


RETURNS

		Returns void

AUTHOR

		Victor Miller

DATE

		4:19pm 12/19/2021

*/
/**/
void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol; // sets location of symbol to -999
		string currError = "Multiply Defined symbol: ";
		cout << currError << a_symbol << endl;
		Errors::RecordError(currError);
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
DisplaySymbolTable()

NAME

		DisplaySymbolTable() - Displays symbol Table

SYNOPSIS

		void SymbolTable::DisplaySymbolTable();

DESCRIPTION

		This function will display the symbol Table with header.


RETURNS

		Returns void

AUTHOR

		Ryan Garaffa

DATE

		4:19pm 12/19/2021

*/
/**/

void SymbolTable::DisplaySymbolTable() {
	cout << "SYMBOL TABLE:" << endl;
	cout << "Symbol #	" << "Symbol	" << "	Location" << endl;
	counter = 0;

	//create iterator to display symboltable
	map<string, int>::const_iterator it = m_symbolTable.begin();
	while(it != m_symbolTable.end()) {
		cout << counter << "		" << it->first << "		" << it->second << endl;
		it++;
		counter++;
	}

	cout << endl << "Type anything to Continue" << endl;
	string enterToContinue;
	cin >> enterToContinue;

}

//Briefly called in AddSymbol() function
bool SymbolTable::LookupSymbol(const string &a_symbol, int &a_loc) {
	return true;
}