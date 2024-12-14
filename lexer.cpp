#include "lexer.h"
#include <fstream>
#include <sstream>
using std::stringstream;

extern std::ifstream fin;

// construtor 
Lexer::Lexer()
{
	// insere palavras-reservadas na tabela de id's
	id_table["float"] = Id{ Tag::TYPE, "float" };
	id_table["int"] = Id{ Tag::TYPE, "int" };
	id_table["char"] = Id{ Tag::TYPE, "char" };
	id_table["bool"] = Id{ Tag::TYPE, "bool" };

	// inicia leitura da entrada
	peek = fin.get();
}

// retorna n�mero da linha atual
int Lexer::Lineno()
{
	return line;
}

// retorna tokens para o analisador sint�tico
Token * Lexer::Scan()
{
	// ignora espa�os em branco, tabula��es e novas linhas
	while (isspace(peek))
	{
		if (peek == '\n')
			line += 1;
		peek = fin.get();
	}

	// retorna n�meros
	if (isdigit(peek))
	{
		int v = 0;
		bool is_float = false;
    	double float_value = 0.0;
    	double divisor = 10.0;

		do
		{
			// converte caractere 'n' para o d�gito num�rico n
			int n = peek - '0';
			v = 10 * v + n;
			peek = fin.get();
		}
 		while (isdigit(peek));

		// Detectar ponto decimal
		if (peek == '.') {
			is_float = true;
			peek = fin.get();

			while (isdigit(peek)) {
				int n = peek - '0';
				float_value += n / divisor;
				divisor *= 10.0;
				peek = fin.get();
			}
		}

		if (is_float) {
        token.n = Num{ v + float_value, Tag::NUM_FLOAT };
		} else {
			token.n = Num{ v };
		}
		return &token.n;

		// retorna o token NUM
		token.n = Num{v};
		return &token.n;
	}

	// retorna palavras-chave e identificadores
	if (isalpha(peek))
	{
		stringstream ss;
		do 
		{
			ss << peek;
			peek = fin.get();
		} 
		while (isalpha(peek));

		string s = ss.str();
		auto pos = id_table.find(s);

		// se o lexema j� est� na tabela
		if (pos != id_table.end())
		{
			// retorna o token associado
			token.i = pos->second;
			return &token.i;
		}

		// se o lexema ainda n�o est� na tabela
		Id new_id {Tag::ID, s};
		id_table[s] = new_id;

		// retorna o token ID
		token.i = new_id;
		return &token.i;
	}

	// operadores (e caracteres n�o alphanum�ricos isolados)
	Token op {peek};
	peek = ' ';

	// retorna o token 
	token.t = op;
	return &token.t;
}

