/*
	CREATED BY : Matthew Cumber
	STUDENT ID : 201131527
	EMAIL : ll16m23c@leeds.ac.uk

	STYLE:
		lowerCamelcase variables
		UpperCamelcase Methods and ClassNames 
		CAPS macros and namespace
*/

#include <iostream>
#include <chrono> 
#include <fstream>
#include <string>
#include <ctype.h>
#include <list>
#include <iterator>

namespace COMPILER
{

class Symbol
{
public:
	std::string name;
	std::string type;
	std::string kind;
	int offset;
	bool initialised;

public:

	Symbol()
	{
		initialised = false;
	}

	void PrintSymbolTerminal()
	{
		std::cout << "| " << name;
		std::cout << " | " << type;
		std::cout << " | " << kind;
		std::cout << " | " << offset;
		if(initialised == true)
		{
			std::cout << " | true";
		}
		else
		{
			std::cout << " | false";
		}
		std::cout << " |" << std::endl;
	}
};

class SymbolTable
{
public:
	std::string tableType;
	std::string tableName;
	std::list<Symbol> listOfSymbols;
	std::list<Symbol>::iterator listIterator;
	std::string returnType;
	int offsetCountLocal;
	int offsetCountArgument;
	int offsetCountStatic;
	int offsetCountField;

public:
	SymbolTable()
	{
		offsetCountLocal = 0;
		offsetCountArgument = 0;
		offsetCountStatic = 0;
		offsetCountField = 0;
	}

	void AddSymbolLocal(Symbol symbol)
	{
		symbol.offset = offsetCountLocal;
		++offsetCountLocal;
		listOfSymbols.push_back(symbol);
	}

	void AddSymbolArgument(Symbol symbol)
	{
		symbol.offset = offsetCountArgument;
		++offsetCountArgument;
		listOfSymbols.push_back(symbol);
	}

	void AddSymbolStatic(Symbol symbol)
	{
		symbol.offset = offsetCountStatic;
		++offsetCountStatic;
		listOfSymbols.push_back(symbol);
	}

	void AddSymbolField(Symbol symbol)
	{
		symbol.offset = offsetCountField;
		++offsetCountField;
		listOfSymbols.push_back(symbol);
	}

	bool SymbolInTable(std::string symbolName)
	{
		for(Symbol symbol : listOfSymbols)
		{
			if(symbol.name == symbolName)
			{
				return true;
			}
		}
		return false;
	}

	Symbol getSymbol(std::string symbolName)
	{
		Symbol missingSymbol;
		missingSymbol.name = "false";
		for(Symbol symbol : listOfSymbols)
		{
			if(symbol.name == symbolName)
			{
				return symbol;
			}
		}
		return missingSymbol;
	}

	std::string LookUpType(std::string symbolName)
	{
		for(Symbol symbol : listOfSymbols)
		{
			if(symbol.name == symbolName)
			{
				return symbol.type;
			}
		}
		return "null";
	}

	bool LookUpName(std::string symbolName)
	{
		for(Symbol symbol : listOfSymbols)
		{
			if(symbol.name == symbolName)
			{
				return true;
			}
		}
		return false;
	}

	void Print()
	{
		std::cout << std::endl;
		std::cout << "|--" << tableType << " : " << tableName << "--|" << std::endl;
		std::cout << "|--Return " << returnType << "--|" << std::endl;
		std::cout << "|------------------------------------------------|" << std::endl;
		std::cout << "|--Name--|--Type--|--Kind--|--#--|--Initialised--|" << std::endl;

		for(Symbol symbol : listOfSymbols)
		{
			symbol.PrintSymbolTerminal();
		}
		std::cout << "|------------------------------------------------|" << std::endl;
	}
};

class File
{

public:
	std::string fileName;
	std::list<SymbolTable> listOfSymbolTables;
	std::list<SymbolTable>::iterator listIterator;

public:
	File(){}
};

}