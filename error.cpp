#include "error.h"
#include <iostream>
using std::cout;
using std::endl;

SyntaxError::SyntaxError(int line, string msg) : lineno(line), desc(msg)
{
	
}

void SyntaxError::What()
{
	cout << "\nErro (linha " << lineno << "): " << desc << endl;
}

