#include <string>
using std::string;

class SyntaxError 
{
private:
	int lineno;
	string desc;
public:
	SyntaxError(int line, string msg);
	void What();
};

