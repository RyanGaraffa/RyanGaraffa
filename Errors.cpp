//
//		Implementation of the Error Class
//
#include "stdafx.h"
#include "Errors.h"
using namespace std;

vector<string> Errors::m_ErrorMsgs;

// Initializes error reports.
void Errors::InitErrorReporting() {
	m_ErrorMsgs.clear();
	string init = "ERROR LIST BELOW";
	m_ErrorMsgs.push_back(init);
}

// Records an error message.
void Errors::RecordError(string a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}

// Displays the collected error message.
void Errors::DisplayErrors() {
	for (int i = 0; i < m_ErrorMsgs.size(); i++) {
		cout << m_ErrorMsgs[i] << endl;
	}
}
