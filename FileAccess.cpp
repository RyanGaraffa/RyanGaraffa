//	Used some of Professor Miller's Code here from my assembler project

#include "stdafx.h"
#include "FileAccess.h"

FileAccess::FileAccess() {
	FileRead = false;
}


FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Canoga <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened" << endl;
		FileRead = false;
        //exit( 1 ); 
    }
	else {
		FileRead = true;
	}
}
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}

/* *********************************************************************
Function Name: GetNextLine
Purpose: to get the next line from file
Parameters:
			&a_line -> holds address of a string
Return Value: bool to see if next line exists
Algorithm:
		1) Checks if there is more data
		2) if not, we return false
		3) else, we set a_line = to the next line
		4) return true
Assistance Received: Professor Miller's Code
********************************************************************* */
bool FileAccess::GetNextLine( string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
}

/* *********************************************************************
Function Name: GetFileRead
Purpose: to get the file read bool
Parameters:
			none
Return Value: file read bool
Algorithm:
		1) return FileRead bool
Assistance Received: Professor Miller's Code
********************************************************************* */
bool FileAccess::GetFileRead() {
	return FileRead;
}
