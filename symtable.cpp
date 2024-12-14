#include "symtable.h"

// construtor para a primeira tabela
SymTable::SymTable() : prev(nullptr)
{
}

// construtor para novas tabelas
SymTable::SymTable(SymTable * t) : prev(t)
{		
}

// insere um s�mbolo na tabela
bool SymTable::Insert(string s, Symbol symb) 
{ 
	auto result = table.insert({s, symb});
	auto pos = result.first;
	auto success = result.second;
	return success;

}

// busca um s�mbolo na tabela atual 
// se n�o encontrado, busca nas tabelas dos escopos envolventes
Symbol * SymTable::Find(string s) 
{
	for (SymTable * st = this; st != nullptr; st = st->prev) 
	{
        auto found = st->table.find(s);
        if (found != st->table.end()) 
			return &found->second;
    }

    return nullptr;
} 


