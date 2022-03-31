/*
************************************************************
* Name:  Ryan Garaffa	(+ Victor Miller code)				*
* Project : Canoga											*
* Class : #9 FileAccess 									*
* Date : 2/12/2022											*
************************************************************
*/

// This is the way that multiple inclusions are defended against often used in UNIX
#ifndef _FILEACCESS_H 

// We use pragmas in Visual Studio.  See other include files
#define _FILEACCESS_H 

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:

	FileAccess();

    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

    // Get the next line from the source file.  Returns true if there was one.
    bool GetNextLine( string &a_line );

	//Accesor for FileRead
	bool GetFileRead(); 

private:
	bool FileRead;

    ifstream m_sfile;		// Source file object.
};
#endif