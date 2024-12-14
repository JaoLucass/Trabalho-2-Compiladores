#include <unordered_map>
#include <string>
#include <sstream>
using std::stringstream;
using std::unordered_map;
using std::string;

// cada token possui uma tag (n�mero a partir de 256)
// a tag de caracteres individuais � seu c�digo ASCII
enum Tag { TYPE = 256, NUM, NUM_FLOAT, ID };

// classes para representar tokens
struct Token
{
	int tag;
	Token() : tag(0) {}
	Token(int t) : tag(t) {}
	virtual string toString() { stringstream ss; ss << char(tag); return ss.str(); }
};

struct Num : public Token
{
    double value;
    bool is_float;

    Num() : Token(Tag::NUM), value(0), is_float(false) {}
    Num(double v, int tag = Tag::NUM) : Token(tag), value(v), is_float(tag == Tag::NUM_FLOAT) {}

    virtual string toString() {
        stringstream ss;
        if (is_float)
            ss << value;
        else
            ss << static_cast<int>(value);
        return ss.str();
    }
};

struct Id : public Token
{
	string name;
	Id(): Token(Tag::ID) {}
	Id(int t, string s) : Token(t), name(s) {}
	virtual string toString() { return name; }
};

// analisador l�xico
class Lexer
{
private:
	// tipos de token da linguagem
	struct
	{
		Token t;
		Num n;
		Id i;
	} 
	token;
	
	int line = 1;
	char peek;
	unordered_map<string, Id> id_table;

public:
	Lexer();
	int Lineno();
	Token * Scan();
};

