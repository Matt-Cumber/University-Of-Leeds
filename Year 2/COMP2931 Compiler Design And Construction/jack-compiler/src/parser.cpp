/*
	CREATED BY : Matthew Cumber
	STUDENT ID : 201131527
	EMAIL : ll16m23c@leeds.ac.uk

	STYLE:
		lowerCamelcase variables
		UpperCamelcase Methods and ClassNames 
		CAPS macros
*/

#include "lexer.cpp"
#include "symboltable.cpp"
#include <string.h>
#include <fstream>

namespace COMPILER
{

// Class for compiler
class Parser
{

public:
	int whileLoopCount = 0; // Incrementer for while loop labels
	int ifCount = 0; // Incrementer for if statement labels
	int argCheck = 0; // Incrementer to compare expected argument count to actual
	bool returnStatemntChecked = false; // Set true when return statement seen
	bool inIf = false; // Check if in if statement
	bool ifReturn = false; // Check if statement has return value
	bool inElse = false; // Check if in else statement
	bool elseReturn = false; // Check else has return value
	Symbol newSymbol;
	SymbolTable scopeTable;
	SymbolTable classTable;
	//std::list<SymbolTable> listOfSymbolTables;
	std::list<File> listOfFiles;
	std::list<std::string> resolveVariables;
	std::list<std::string> VMCode;
	std::string currentScope;

// Public Methods
public:

	// Constructor
	Parser()
	{
		// Symbolise jack os files
		lexer.InitLexer("src/OS Files/Keyboard.jack");
		Symbolise();
		lexer.InitLexer("src/OS Files/Math.jack");
		Symbolise();
		lexer.InitLexer("src/OS Files/Memory.jack");
		Symbolise();
		lexer.InitLexer("src/OS Files/Output.jack");
		Symbolise();
		lexer.InitLexer("src/OS Files/Screen.jack");
		Symbolise();
		lexer.InitLexer("src/OS Files/String.jack");
		Symbolise();
		lexer.InitLexer("src/OS Files/Sys.jack");
		Symbolise();

		// // #ifdef DEBUG
		// 	PrintTables();
		// // #endif
	}

	int getArgCount(std::string name)
	{
		std::cout << "argcount : " << name << std::endl;
		for(File file : listOfFiles)
		{
			for(SymbolTable symbolTable : file.listOfSymbolTables)
			{
				if(symbolTable.tableName == name)
				{
					std::cout << "= " << symbolTable.offsetCountArgument << std::endl;
					return symbolTable.offsetCountArgument;
				}
			}
		}
		return -1;
	}

	// Returns offset of a symbol in the given table name
	int getOffset(std::string name)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	for(Symbol symbol : table.listOfSymbols)
		// 	{
		// 		if(symbol.name == name && ((table.tableName == currentScope) || 
		// 			(table.tableName == classTable.tableName)))
		// 		{
		// 			return symbol.offset;
		// 		}
		// 	}
		// }
		return 0;
	}

	// Returns the return tyoe of a table
	std::string getReturnType(std::string name)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	if(table.tableName == name)
		// 	{
		// 		return table.returnType;
		// 	}
		// }
		return "notfound";
	}

	// Returns the number of argument variables in a table
	int getArgumentCount(std::string name)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	if(table.tableName == name)
		// 	{
		// 		return table.offsetCountArgument;
		// 	}
		// }
		return -1;
	}

	// Returns the kind of a given symbol name
	std::string getKind(std::string name)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	for(Symbol symbol : table.listOfSymbols)
		// 	{
		// 		if(symbol.name == name && ((table.tableName == currentScope) || 
		// 			(table.tableName == classTable.tableName)))
		// 		{
		// 			if(symbol.kind == "field")
		// 			{
		// 				return "this";
		// 			}
		// 			return symbol.kind;
		// 		}
		// 	}
		// }
		return "notexist";
	}

	// Returns the type of a given symbol name
	std::string getType(std::string name)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	for(Symbol symbol : table.listOfSymbols)
		// 	{
		// 		if(symbol.name == name && ((table.tableName == currentScope) || 
		// 			(table.tableName == classTable.tableName)))
		// 		{
		// 			return symbol.type;
		// 		}
		// 	}
		// }
		return "";
	}

	// Generalised function write code to push a variable
	void writePushVMVariable(Token token, std::string name)
	{
		std::string kind = getKind(name);

		// If the variable could not be found produce an error
		if(kind == "notexist")
		{
			SemanticError(token,name + " does not exist");
		}

		VMCode.push_back("push " + getKind(name) + " " + std::to_string(getOffset(name)));
	}

	// Generalised code for a pop command
	void writePopVMVariable(Token token, std::string name)
	{
		std::string kind = getKind(name);

		// If the variable could not be found produce an error
		if(kind == "notexist")
		{
			SemanticError(token,name + " does not exist");
		}

		VMCode.push_back("pop "  + getKind(name) + " " + std::to_string(getOffset(name)));
	}

	// Generalised code for the declartion of a function
	void writeVMSubCall(std::string name)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	if(table.tableName == name)
		// 	{
		// 		VMCode.push_back("function " + name + " " + std::to_string(table.offsetCountLocal));
		// 	}
		// }
	}

	// General function for generating method calls in VM
	void writeVMCallMethod(Token token,std::string name)
	{
		// Particular array case
		if(name == "Array.new")
		{
			VMCode.push_back("call Array.new 1");
			return;
		}

		// Check the argument counts match up
		// Only check if method found
		// int argCount = getArgumentCount(name);
		// if(argCount != -1)
		// {
		// 	if(argCount != argCheck)
		// 	{
		// 		SemanticError(token,"Number of arguments do not match");
		// 	}
		// }

		int argCount = 0;
		argCount = getArgCount(name);

		if(argCount != argCheck)
		{
			SemanticError(token, "Number of arguments do no match calling function");
		}
		
		VMCode.push_back("call " + name + " " + std::to_string(argCount));
		std::string returnType = getReturnType(name);

		// Special cases to clear top of stack
		if(returnType == "void")
		{
			VMCode.push_back("pop temp 0");
		}
		if(name.substr(0,6) == "Output")
		{
			VMCode.push_back("pop temp 0");
		}
	}

	// Returns true if a given symbol is initialised
	bool IsInitialised(std::string symbolName)
	{
		// for(SymbolTable table : listOfSymbolTables)
		// {
		// 	for(Symbol symbol : table.listOfSymbols)
		// 	{
		// 		if(symbol.name == symbolName && ((table.tableName == currentScope) || 
		// 			(table.tableName == classTable.tableName)))
		// 		{
		// 			return symbol.initialised;
		// 		}
		// 	}
		// }
		return false;
	}

	// Sets the initialised variable of a symbol to true 
	void InitialiseSymbol(std::string symbolName)
	{	
		// Loop symbol tables
		// std::list<SymbolTable>::iterator itTables = listOfSymbolTables.begin();
		// while(itTables != listOfSymbolTables.end())
		// {
		// 	SymbolTable& table = *itTables;

		// 	// Loop symbols of each table
		// 	std::list<Symbol>::iterator itSymbols = table.listOfSymbols.begin();
		// 	while(itSymbols != table.listOfSymbols.end())
		// 	{
		// 		// Check symbol name and change init
		// 		Symbol& symbol = *itSymbols;
		// 		if(symbol.name == symbolName && ((table.tableName == currentScope) || 
		// 			(table.tableName == classTable.tableName)))
		// 		{
		// 			symbol.initialised = true;
		// 			return;
		// 		}
		// 		++itSymbols;
		// 	}
		// 	++itTables;
		// }
	}

	// Returns the type of a symbol from the class table
	std::string classTableLookUpType(std::string symbolName)
	{
		// for(Symbol symbol : classTable.listOfSymbols)
		// {
		// 	if(symbol.name == symbolName)
		// 	{
		// 		return symbol.type;
		// 	}
		// }
		return "null";
	}

	// Returns true if the name of a symbol is from the class table
	bool ClassTableLookUpName(std::string symbolName)
	{
		// for(Symbol symbol : classTable.listOfSymbols)
		// {
		// 	if(symbol.name == symbolName)
		// 	{
		// 		return true;
		// 	}
		// }
		return false;
	}

	// Method to parse a file
	void Parse(std::string fileName)
	{
		// Before parsing run lexical anyalsis to get all tokens
		lexer.InitLexer(fileName);

		#ifdef DEBUG
			std::cout << "Parsing now..." << std::endl;
		#endif

		// Create symbol tables first
		Symbolise();

		//#ifdef DEBUG
			PrintTables();
		//#endif

		// Reset lexer iterators for parser to use getnexttoken and peeknexttoken methods
		lexer.ResetIterator();

		// Begin parsing file
		StartParsing();

		#ifdef DEBUG
			std::cout << "Parsing successful" << std::endl;
		#endif
	}

	void LookUpNames(std::string name, SymbolTable table, Token token)
	{
		bool checkName = ClassTableLookUpName(token.lexeme);
		if(checkName)
		{
			SemanticError(token,
				"Redeclaration of " + token.lexeme);
		}
		checkName = table.LookUpName(token.lexeme);
		if(checkName)
		{
			SemanticError(token,
				"Redeclaration of " + token.lexeme);
		}
	}

	// Method to create symbol tables
	// Assumes almost everything is correct
	void Symbolise()
	{
		File file;
		file.fileName = lexer.lexerFileName;

		Token token = lexer.GetNextToken();
		std::cout << "start of symbolise" << token.lexeme << std::endl;
		
		while(token.type != Token::Types::Eof)
		{
			// Create class table
			if(token.lexeme == "class")
			{
				SymbolTable newTable;
				token = lexer.GetNextToken(); // Get class name
				newTable.tableType = "class";
				newTable.tableName = token.lexeme;
				std::cout << token.lexeme << std::endl;
				newTable.returnType = "class";
				classTable = newTable;
				token = lexer.GetNextToken(); // Next token for next if
			}

			// Add static to class table
			if(token.lexeme == "static")
			{
				newSymbol.kind = token.lexeme; // Assign static to kind
				token = lexer.GetNextToken(); 
				newSymbol.type = token.lexeme; // Assign type
				token = lexer.GetNextToken();
				LookUpNames(token.lexeme, classTable, token); // Check for redeclarations
				newSymbol.name = token.lexeme; // Assign name
				classTable.AddSymbolStatic(newSymbol); // Add static symbol
				token = lexer.GetNextToken(); // Next token for while loop

				while(token.lexeme != ";")
				{
					token = lexer.GetNextToken(); // Move past comma
					LookUpNames(token.lexeme, classTable, token); // Check for redeclarations
					newSymbol.name = token.lexeme; // Assign name
					classTable.AddSymbolStatic(newSymbol); // Add new static symbol
					token = lexer.GetNextToken(); // Next token for while condition
				}
			}

			// Add fields to class table
			if(token.lexeme == "field")
			{
				newSymbol.kind = token.lexeme; // Assign static to kind
				token = lexer.GetNextToken(); 
				newSymbol.type = token.lexeme; // Assign type
				token = lexer.GetNextToken();
				LookUpNames(token.lexeme, classTable, token); // Check for redeclarations
				newSymbol.name = token.lexeme; // Assign name
				classTable.AddSymbolField(newSymbol); // Add static symbol
				token = lexer.GetNextToken(); // Next token for while loop

				while(token.lexeme != ";")
				{
					token = lexer.GetNextToken(); // Move past comma
					LookUpNames(token.lexeme, classTable, token); // Check for redeclarations
					newSymbol.name = token.lexeme; // Assign name
					classTable.AddSymbolField(newSymbol); // Add new static symbol
					token = lexer.GetNextToken(); // Next token for while condition
				}
			}

			// Create constructor symbol table
			if(token.lexeme == "constructor")
			{
				SymbolTable newTable;
				newTable.tableType = "constructor";
				token = lexer.GetNextToken();

				// Constructors must return an instance of the class
				if(token.lexeme != classTable.tableName)
				{
					SemanticError(token,
						"The return type of a constructor must be the same as the class name");
				}

				newTable.returnType = "this";
				token = lexer.GetNextToken();

				// Constructors must be called new
				if(token.lexeme != "new")
				{
					SemanticError(token, "Constructors must be called new.");
				}

				newTable.tableName = classTable.tableName + "." + token.lexeme; // Assign table name
				token = lexer.GetNextToken(); // Move past "("
				token = lexer.GetNextToken(); // Expect either ")" or type

				while(token.lexeme != ")")
				{
					newSymbol.type = token.lexeme; // Assign type
					token = lexer.GetNextToken();
					LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
					newSymbol.name = token.lexeme; // Assign name
					newSymbol.initialised = true; // Arguments are initialised by default
					newSymbol.kind = "argument";
					newTable.AddSymbolArgument(newSymbol); // Add argument
					token = lexer.GetNextToken();
					if(token.lexeme == ",")
					{
						token = lexer.GetNextToken(); // skip comma
					}
				}

				lexer.GetNextToken(); // Skip "{"
				token = lexer.GetNextToken(); // Expect either statement or "}"

				while(token.lexeme != "}")
				{
					// Add var to constructor symbol table
					if(token.lexeme == "var")
					{
						newSymbol.kind = "local"; // Var statements add locals
						token = lexer.GetNextToken();
						newSymbol.type = token.lexeme; // Assign type
						token = lexer.GetNextToken();
						LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
						newSymbol.name = token.lexeme; // Assign name
						newSymbol.initialised = false;
						newTable.AddSymbolLocal(newSymbol); // Add local
						token = lexer.GetNextToken();

						// Add multiple vars
						while(token.lexeme != ";")
						{
							token = lexer.GetNextToken();
							LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
							newSymbol.name = token.lexeme;
							newTable.AddSymbolLocal(newSymbol); // Add local
							token = lexer.GetNextToken();
						}
					}

					// Check return type which must be "this" for a constructor 
					if(token.lexeme == "return")
					{
						token = lexer.GetNextToken();
						if(token.lexeme != "this")
						{
							SemanticError(token,
								"A constructor must return this.");
						}
					}

					token = lexer.GetNextToken();
				}

				//listOfSymbolTables.push_back(newTable); // Add constructor table to list
				file.listOfSymbolTables.push_back(newTable);
			}

			// Create method symbol table
			if(token.lexeme == "method")
			{
				SymbolTable newTable;
				newTable.tableType = "method";

				// Add implicit this argument
				newSymbol.name = "this";
				newSymbol.type = classTable.tableName;
				newSymbol.kind = "argument";
				newSymbol.initialised = true;
				newTable.AddSymbolArgument(newSymbol); 

				token = lexer.GetNextToken(); // Get return type
				newTable.returnType = token.lexeme;
				token = lexer.GetNextToken();
				newTable.tableName = classTable.tableName + "." + token.lexeme; // Assign table name
				token = lexer.GetNextToken(); // skip "("
				token = lexer.GetNextToken(); // Expect either ")" or type

				while(token.lexeme != ")")
				{
					newSymbol.type = token.lexeme; // Assign type
					token = lexer.GetNextToken();
					LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
					newSymbol.name = token.lexeme; // Assign name
					newSymbol.initialised = true;
					newTable.AddSymbolArgument(newSymbol); // Add argument
					token = lexer.GetNextToken();
					if(token.lexeme == ",")
					{
						token = lexer.GetNextToken(); // skip comma
					}
				}

				lexer.GetNextToken(); // skip "{"
				token = lexer.GetNextToken(); // Expect either "}" or type

				while(token.lexeme != "}")
				{
					// Add more local to symbol table
					if(token.lexeme == "var")
					{
						newSymbol.kind = "local";
						token = lexer.GetNextToken();
						newSymbol.type = token.lexeme; // Assign type
						token = lexer.GetNextToken();
						LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
						newSymbol.name = token.lexeme; // Assign name
						newSymbol.initialised = false;
						newTable.AddSymbolLocal(newSymbol); // Add local
						token = lexer.GetNextToken();

						while(token.lexeme != ";")
						{
							token = lexer.GetNextToken();
							LookUpNames(token.lexeme, newTable, token);
							newSymbol.name = token.lexeme;
							newTable.AddSymbolLocal(newSymbol); // Add local
							token = lexer.GetNextToken();
						}
					}

					// Check return types match
					if(token.lexeme == "return")
					{
						token = lexer.GetNextToken();

						// First check current table
						std::string checkType = newTable.LookUpType(token.lexeme);

						// Check class table if not in current table
						if(checkType == "null")
						{
							checkType = classTableLookUpType(token.lexeme);
						}

						if(token.type == Token::Types::IntegerConstant)
						{
							checkType = "int"; // Integer constant have type int
						}

						if(token.type == Token::Types::StringConstant)
						{
							checkType = "String"; // String constants have type string
						}

						// Error if type is not void or they do not match
						if(checkType != newTable.returnType && newTable.returnType != "void")
						{
							SemanticError(token,
								"The return types are not the same");
						}
					}

					token = lexer.GetNextToken();
				}

				//listOfSymbolTables.push_back(newTable); // Add method symbol table to list
				file.listOfSymbolTables.push_back(newTable);
			}

			// Create function Symbol table
			if(token.lexeme == "function")
			{
				SymbolTable newTable;
				newTable.tableType = "function";
				token = lexer.GetNextToken(); // Get return type
				newTable.returnType = token.lexeme;
				token = lexer.GetNextToken(); // Get name of table
				newTable.tableName = classTable.tableName + "." + token.lexeme; // Assign table name
				token = lexer.GetNextToken(); // skip "("
				token = lexer.GetNextToken(); // Expect either ")" or type

				while(token.lexeme != ")")
				{
					newSymbol.type = token.lexeme; // Assign type
					token = lexer.GetNextToken();
					LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
					newSymbol.name = token.lexeme; // Assign name
					newSymbol.initialised = true; // Arguments initialised by default
					newSymbol.kind = "argument";
					newTable.AddSymbolArgument(newSymbol); // Add argument
					token = lexer.GetNextToken();
					if(token.lexeme == ",")
					{
						token = lexer.GetNextToken(); // skip comma
					}
				}

				lexer.GetNextToken(); // Skip "{"
				token = lexer.GetNextToken(); // Expect either "}" or type

				while(token.lexeme != "}")
				{
					if(token.lexeme == "var")
					{
						newSymbol.kind = "local"; // Vars have local kind
						token = lexer.GetNextToken();
						newSymbol.type = token.lexeme; // Assign type
						token = lexer.GetNextToken();
						LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
						newSymbol.name = token.lexeme; // Assign name
						newSymbol.initialised = false;
						newTable.AddSymbolLocal(newSymbol); // Add local
						token = lexer.GetNextToken();

						while(token.lexeme != ";")
						{
							token = lexer.GetNextToken();
							LookUpNames(token.lexeme, newTable, token); // Check for redeclarations
							newSymbol.name = token.lexeme;
							newTable.AddSymbolLocal(newSymbol); // Add local
							token = lexer.GetNextToken();
						}
					}

					// Check return type
					if(token.lexeme == "return")
					{
						token = lexer.PeekNextToken();

						// If not end of return statement check the type
						if(token.lexeme != ";")
						{
							token = lexer.GetNextToken();
						}

						// Else there is no return value to check
						else
						{
							token = lexer.GetNextToken();
							continue;
						}

						// If null from current table check class table
						std::string checkType = newTable.LookUpType(token.lexeme);
						if(checkType == "null")
						{
							checkType = classTableLookUpType(token.lexeme);
						}

						if(token.type == Token::Types::IntegerConstant)
						{
							checkType = "int"; // Integer constants have type int
						}

						if(token.type == Token::Types::StringConstant)
						{
							checkType = "String"; // String constants have type String
						}

						// Comapre return types
						if(checkType != newTable.returnType && newTable.returnType != "void")
						{
							SemanticError(token,
								"The return types are not the same");
						}
					}

					token = lexer.GetNextToken();
				}

				//listOfSymbolTables.push_back(newTable); // Add function symbol table
				file.listOfSymbolTables.push_back(newTable);
			}

			token = lexer.GetNextToken();
		}
		//listOfSymbolTables.push_front(classTable); // Add class table to front of list
		file.listOfSymbolTables.push_front(classTable);
		listOfFiles.push_back(file);
	}

	// Method to print symbol tables for debugging
	void PrintTables() 
	{
		// for(SymbolTable symbolTable : listOfSymbolTables)
		// {
		// 	symbolTable.Print();
		// }
		for(File file : listOfFiles)
		{
			std::cout << "file name" << file.fileName << std::endl;
			for(SymbolTable symbolTable : file.listOfSymbolTables)
			{
				symbolTable.Print();
			}
		}
	}

	/*---------------------VM CODE GENERATION----------------------*/
	// Method to generate VM code, i.e. write the VM code to a file
	void generateVMCode()
	{
		// Initialise name of VM file
		std::string VMFileName = lexer.lexerFileName;
		VMFileName.erase(VMFileName.length() - 5,std::string::npos); // removes .jack extension
		VMFileName += ".vm"; // add vm extension

		// Create stream to write to file
		std::ofstream streamToFile(VMFileName,std::ofstream::out);

		// Write all VM code to file, replacing any existing VM code
		for(std::string code : VMCode)
		{
			streamToFile << code << std::endl;
		}

		// Close the stream
		streamToFile.flush();
		streamToFile.close();
	}
	/*--------------------------------------------------------*/

// Private Methods
private:

	// Method to print debugging messages
	void PrintParse(Token tokenFound, std::string tokenExpected, std::string grammarRule)
	{
		std::cout << "------------------------" << std::endl;
		std::cout << "Parsing on Grammar Rule : ";
		std::cout << grammarRule << std::endl;
		std::cout << "Expected this token : ";
		std::cout << tokenExpected << std::endl;
		std::cout << "Found this token : " << std::endl;
		std::cout << "	Lexeme : ";
		std::cout << tokenFound.lexeme << std::endl;
		std::cout << "	Type : ";
		std::cout << tokenFound.type << std::endl;
		std::cout << "------------------------" << std::endl;
	}

	// Methods to print error messages
	// Prints line number error, error token and what is expected
	// Is a short tempered compiler with no error recovery so exits
	void ParseError(Token errorToken, std::string expectedToken, std::string extraMessage)
	{
		std::cout << "Error Parsing in file " << lexer.lexerFileName << std::endl;
		std::cout << "On line number : " << errorToken.tokenLineNumber;
		std::cout << ", found \"" << errorToken.lexeme;
		std::cout << "\", expected to find \"" << expectedToken << "\"";
		std::cout << " in this position." << std::endl;

		// Prints an extra more specific message if passed as argument
		if(extraMessage.length() > 0)
		{
			std::cout << extraMessage << std::endl;
		}
		exit(0);
	}

	void SemanticError(Token errorToken, std::string extraMessage)
	{
		std::cout << "Semantic Error in file " << lexer.lexerFileName << std::endl;
		std::cout << "On line number : " << errorToken.tokenLineNumber << std::endl;

		// Prints an extra more specific message if passed as argument
		if(extraMessage.length() > 0)
		{
			std::cout << extraMessage << std::endl;
		}
		exit(0);
	}

	// The parser has a function to handle each grammar rule of the JACK language
	// The rules are stated at the top of each function

	// Method to start parsing
	void StartParsing()
	{
		// All jack files start with a class declaration
		ClassDeclaration();

		// Expect the EOF at the end of a class as only one class per file
		Token token = lexer.PeekNextToken();
		if(token.type != Token::Types::Eof)
		{
			ParseError(token,"EOF","Only one class can be delcared per JACK file. "
				 "Check the number of \"}\" in your code.");
		}
	}

	// classDeclar -> class identifier { {memberDeclar} }
	void ClassDeclaration()
	{
		Token token = lexer.PeekNextToken();

		// The first token should be class keyword
		if(token.lexeme != "class")
		{
			ParseError(token,"class","JACK files should start with a class declaration.");
		}

		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Next token should be identfier i.e. name of the class
		if(token.type != Token::Types::Identifier)
		{
			ParseError(token,"identifier","The class should have a name.");
		}

		currentScope = token.lexeme; // Current working scope is the class

		// Consume name and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Next token should be { symbol
		if(token.lexeme != "{")
		{
			ParseError(token,"{","The symbol \"{\" should be used to start a class body.");
		}

		lexer.GetNextToken();

		// A classDeclar can have zero or more memberDeclar
		token = lexer.PeekNextToken();

		while(token.lexeme != "}")
		{
			// Call MemberDeclaration to check further grammar
			MemberDeclaration();
			token = lexer.PeekNextToken();
		}

		// End the class declaration with }
		// If not found then there is an error in the source file 
		if(token.lexeme != "}")
		{
			ParseError(token,"}","The symbol \"}\" should be used to end a class body.");
		}

		// Consume "}" at end of class
		lexer.GetNextToken();
	}

	// memberDeclar -> classVarDeclar | subroutineDeclar
	void MemberDeclaration()
	{
		Token token = lexer.PeekNextToken();

		// Member declaration is a class variable declaration
		if(token.lexeme == "static" || token.lexeme == "field")
		{
			ClassVariableDeclaration();
		}

		// Member declaration is a subroutine declaration
		else if(token.lexeme == "constructor" || token.lexeme == "function"
			|| token.lexeme == "method")
		{
			SubroutineDeclaration();
		}

		// A member declaration can only be one of the above
		// If it is neither one of the above there is an error in the source file
		else 
		{
			ParseError(token,"static\", \"field\", \"constructor\", \"function\" or \"method","Have"
				" you closed the body of the class?");
		}
	}

	// classVarDeclar -> (static | field) type identifier {, identifier} ;
	void ClassVariableDeclaration()
	{
		Token token = lexer.PeekNextToken();

		// Must be static or field
		if(token.lexeme != "static" && token.lexeme != "field")
		{
			ParseError(token,"static or field","");
		}

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Must be followed by a type
		Type();

		token = lexer.PeekNextToken();

		// Must be an identifier
		if(token.type == Token::Types::Identifier)
		{
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			// Possibility of declaring more than one identifier at a time
			while(token.lexeme != ";")
			{
				// Identifers must be seprated with a comma
				if(token.lexeme != ",")
				{
					// The error here could either be a missing comma or a semicolon
					ParseError(token,",\" or \";","To end a field or static declaration use \";\""
					 " If trying to declare multiple fields seperate them using commas." 
						 "There is no intializing variables in JACK.");
				}

				// Consume ","
				lexer.GetNextToken();
				token = lexer.PeekNextToken();

				// Must be an identifier in the declaration
				if(token.type != Token::Types::Identifier)
				{
					ParseError(token,"identifier","Did you mean to declare multiple fields "
						"using a \",\" . " 
						 "They should all have different names.");
				}

				// Consume identifier and peek for next loop
				lexer.GetNextToken();
				token = lexer.PeekNextToken();
			}
			// Consume ";"
			lexer.GetNextToken();
		}
		else 
		{
			ParseError(token,"identifier","Fields must have a type followed by a name");
		}
	}

	// type -> int | char | boolean | identifier
	void Type()
	{
		Token token = lexer.PeekNextToken();

		// The jack langauge only has these types
		if(token.lexeme == "int" || token.lexeme == "char" || token.lexeme == "boolean" 
			|| token.type == Token::Types::Identifier || token.lexeme == "void")
		{
			lexer.GetNextToken();
		}

		// The type could also be an Array or a String
		else if(token.lexeme == "Array" || token.lexeme == "String")
		{
			lexer.GetNextToken();
		}

		// Must be an error if not one of these types
		else {
			ParseError(token,"type","You need to specify a type for a variable or field/static."
				"The types in JACK are\n\"int\", \"char\", \"boolean\",\"Array\",\"String\" and"
				"\"void\".You can also create your own types");
		}
	}

	// subroutineDeclar -> (constructor | function | method) (type|void) 
	//						identifier (paramList) subroutineBody
	void SubroutineDeclaration()
	{
		std::string declarationType = ""; // Store type of subroutine
		std::string name; // Store name identifier

		Token token = lexer.PeekNextToken();

		// Subroutine must be constructor, function or method
		if(token.lexeme == "constructor" || token.lexeme == "function"
			|| token.lexeme == "method")
		{
			declarationType = token.lexeme;

			// Consume keyword and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			// Must be either void or of Type
			// Type will also handle the error of void/type being missing
			Type();

			token = lexer.PeekNextToken();

			if(token.type != Token::Types::Identifier)
			{
				ParseError(token,"identifier","Method,function or constructor must have a name");
			}

			name = classTable.tableName;
			name += ".";
			name += token.lexeme;
			currentScope = name; // Current scope is now this subroutine

			writeVMSubCall(name); // Generate code for new function

			// Extra VM code for constructor
			if(declarationType == "constructor")
			{
				// Push number of field variables of class
				VMCode.push_back("push constant " + std::to_string(classTable.offsetCountField));
				VMCode.push_back("call Memory.alloc 1");
				VMCode.push_back("pop pointer 0");
			}

			// Extra VM code for a method
			else if(declarationType == "method")
			{
				// Assign this pointer
				VMCode.push_back("push argument 0");
				VMCode.push_back("pop pointer 0");
			}

			// Consume identifier
			lexer.GetNextToken();

			token = lexer.PeekNextToken();

			// Open bracket must follow
			if(token.lexeme != "(")
			{
				ParseError(token,"(","Must have a parameter list started with a \"(\"");
			}		

			// Consume open bracket and peek
			lexer.GetNextToken();

			// Following brakcets should be parameters
			ParameterList();

			token = lexer.PeekNextToken();

			// Closing bracket to end paramter list
			if(token.lexeme != ")")
			{
				ParseError(token,")","Must end a parameter list with a \")\"");
			}

			// Consume closing bracket
			lexer.GetNextToken();

			// To end the subroutine declaration is it's body
			SubroutineBody();
		}

		// Must be an error if not constructor, function or method
		else
		{
			ParseError(token,"constructor\",\"function\" or \"method","");
		}
	}

	// paramList -> type identifier {, type identifier} | ε
	void ParameterList()
	{
		Token token = lexer.PeekNextToken();

		// The parameter list can be empty
		// There is only a list of parameters if this token is not
		// the end of the parameter list i.e. not a closing bracket
		if(token.lexeme != ")")
		{
			// Start of parameter list is the type of a parameter
			// Error handling of type in Type() method
			Type();

			// Followed by an identifier
			token = lexer.PeekNextToken();

			if(token.type != Token::Types::Identifier)
			{
				ParseError(token,"identifier","Parameters must have a name");
			}

			// Consume identifier and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			// The paramater list may contain zero or more paramaters
			// The while loop will check for more than parameters
			while(token.lexeme != ")")
			{
				// Multiple parameters should be seperated by commas
				if(token.lexeme != ",")
				{
					ParseError(token,",","Multiple parameters should be seperated by a \",\"");
				}

				// Consume ","
				lexer.GetNextToken();

				// Start of a parameter is the type of a parameter
				Type();

				// Followed by an identifier
				token = lexer.PeekNextToken();

				if(token.type != Token::Types::Identifier)
				{
					ParseError(token,"identifier","Each parameter should have a name");
				}

				// Consume identifier and peek
				lexer.GetNextToken();
				token = lexer.PeekNextToken();
			}
		}
	}

	// subroutineBody -> { {statement} } 
	void SubroutineBody()
	{
		Token token = lexer.PeekNextToken();

		// Start of a body is "{"
		if(token.lexeme != "{")
		{
			ParseError(token,"{","Bodies of functions should start with \"{\"");
		}

		// Consume { and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// The body can consist of zero or more statements
		while(token.lexeme != "}")
		{
			Statement();
			token = lexer.PeekNextToken();
		}

		if(!returnStatemntChecked)
		{
			SemanticError(token,"All methods,functions and constructors must have a return statement");
		}

		returnStatemntChecked = false; // Reset returnstatementcheck for new subroutine to use

		// Consume "}"
		lexer.GetNextToken();
	}

	// statement → varDeclarStatement | letStatemnt | ifStatement | 
	//			whileStatement | doStatement | returnStatemnt
	void Statement()
	{
		Token token = lexer.PeekNextToken();

		// If return statement checked, no more statements should be found
		if(returnStatemntChecked)
		{
			SemanticError(token, "Code is unreachable");
		}

		// A statement in the Jack langauge could be any of the following
		// below
		if(token.lexeme == "var")
		{
			VariableDeclarationStatement();
		}

		else if(token.lexeme == "let")
		{
			LetStatement();
		}

		else if(token.lexeme == "if")
		{
			IfStatement();
		}

		else if(token.lexeme == "while")
		{
			WhileStatement();
		}

		else if(token.lexeme == "do")
		{
			DoStatement();
		}

		else if(token.lexeme == "return")
		{
			ReturnStatement();
		}

		// If it is not one of these statements then there must be an error
		else 
		{
			ParseError(token,"statement","A statement in jack can only begin with:\n"
				 "\"var\",\"let\",\"if\",\"while\",\"do\",\"return\".");
		}
	}

	// varDeclarStatement -> var type identifier { , identifier } ;
	void VariableDeclarationStatement()
	{
		Token token = lexer.PeekNextToken();

		// Variable declarations begin with keyword "var"
		if(token.lexeme != "var")
		{
			ParseError(token,"var","To declare a variable use the \"var\" statement.");
		}

		// Consume keyword
		lexer.GetNextToken();

		// Following that is a type
		Type();

		// Then at least one identifier
		token = lexer.PeekNextToken();

		if(token.type != Token::Types::Identifier)
		{
			ParseError(token,"identifier","Variables must have a name.");
		}

		// Consume identifier and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		while(token.lexeme != ";")
		{
			// Multiple variables to be declared using commas
			if(token.lexeme != ",")
			{
				ParseError(token,",\" or \";","To end a variable declaration use \";\" or to declare"
					 "multiple variables use a \",\".");
			}

			// Consume "," and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			// Must be identifier after ","
			if(token.type != Token::Types::Identifier)
			{
				ParseError(token,"identifier","Did you mean to declare multiple variables."
					  "End a variable declaration with \";\" otherwise to declare multiple"
					  "variables each one should have a name.");
			}

			// Consume identifier and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();
		}

		// Consume ";"
		lexer.GetNextToken();
	}

	// letStatemnt -> let identifier [ [ expression ] ] = expression ;
	void LetStatement()
	{
		Token token = lexer.PeekNextToken();
		bool letArray = false; // Set true if LHS is an array

		// Let statement should begin with keyword "let"
		if(token.lexeme != "let")
		{
			ParseError(token,"let","");
		}

		// Consume let keyword and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Must be identifier next
		if(token.type != Token::Types::Identifier)
		{
			ParseError(token,"identifier","The let statement is used to assign a value"
				 " to an identifier. You must name this identifier after the \"let\""
				 " keyword.");
		}

		std::string ident = token.lexeme; // Store name of LHS

		// Consume identifier and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Potentially could be an array
		if(token.lexeme == "[")
		{
			letArray = true; // LHS is an array

			// Assume is an array now
			lexer.GetNextToken();
			
			// Array index is an expression
			Expression();

			// Code for array indexing
			writePushVMVariable(token, ident);
			VMCode.push_back("add");

			// End array with "]"
			token = lexer.PeekNextToken();
			if(token.lexeme != "]")
			{
				ParseError(token,"]","Did you mean to use the array notation. To end an array" 
					 "use \"]\".");
			}

			// Consume "]" and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();			
		}

		// Assume not array or array expression correct
		if(token.lexeme != "=")
		{
			ParseError(token,"=","Must have the \"=\" for a let expression.");
		}

		// Consume "="
		lexer.GetNextToken();
	
		// Followed by expression
		Expression();

		token = lexer.PeekNextToken();

		// Must end with a ";"
		if(token.lexeme != ";")
		{
			ParseError(token,";","You must end a let statement with a \";\".");
		}

		// Consume ";"
		lexer.GetNextToken();

		// Specific VM code when LHS is an array
		if(letArray)
		{
			VMCode.push_back("pop temp 0");
			VMCode.push_back("pop pointer 1");
			VMCode.push_back("push temp 0");
			VMCode.push_back("pop that 0");
		}

		// Generic code
		else
		{
			InitialiseSymbol(ident);
			writePopVMVariable(token,ident);	
		}

	}

	// ifStatement -> if ( expression ) { {statement} } [else { {statement} }]
	void IfStatement()
	{
		Token token = lexer.PeekNextToken();

		// Must start with keyword "if"
		if(token.lexeme != "if")
		{
			ParseError(token,"if","");
		}

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// If statement should have a bracketed condition
		if(token.lexeme != "(")
		{
			ParseError(token,"(","If statements should have a condition with an open"
				 "parentheses, \"(\".");
		}

		lexer.GetNextToken();

		// Expression inside bracket
		Expression();
		token = lexer.PeekNextToken();

		// Closing bracket to end if condition
		if(token.lexeme != ")")
		{
			ParseError(token,")","Must close the condition with a \")\".");
		}

		// VM code to start if statement
		VMCode.push_back("if-goto IF_TRUE" + std::to_string(ifCount));
		VMCode.push_back("goto IF_FALSE" + std::to_string(ifCount));
		VMCode.push_back("label IF_TRUE" + std::to_string(ifCount));

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// If statement must have a body starting with {
		if(token.lexeme != "{")
		{
			ParseError(token,"{","If body should start with a \"{\".");
		}

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		inIf = true;

		// If statement body can be empty or many statements
		while(token.lexeme != "}")
		{
			Statement();
			token = lexer.PeekNextToken();
		}

		inIf = false;

		// Consume } and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// VM code for else part
		VMCode.push_back("goto IF_END" + std::to_string(ifCount));
		VMCode.push_back("label IF_FALSE" + std::to_string(ifCount));

		// If statement can be followed by an else statement
		if(token.lexeme == "else")
		{
			// Consume else keyword and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			// Else must have {
			if(token.lexeme != "{")
			{
				ParseError(token,"{","Else statements should also start their body with a \"{\".");
			}

			// Consume and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			inElse = true;

			// Else statement can be zero or more statements
			while(token.lexeme != "}")
			{
				Statement();
				token = lexer.PeekNextToken();
			}

			inElse = false;

			// Consume }
			lexer.GetNextToken();
		}

		// If return and else make a full return
		if(ifReturn && elseReturn)
		{
			returnStatemntChecked = true;
		}

		// End if label and increment count for next if statement
		VMCode.push_back("label IF_END" + std::to_string(ifCount));
		++ifCount;
	}

	// whileStatement -> while ( expression ) { {statement} }
	void WhileStatement()
	{
		Token token = lexer.PeekNextToken();

		// Must start with keyword "while"
		if(token.lexeme != "while")
		{
			ParseError(token,"while","");
		}

		// Start while loop label
		VMCode.push_back("label WHILE_EXP" + std::to_string(whileLoopCount));

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// While loop must have bracketed condition
		if(token.lexeme != "(")
		{
			ParseError(token,"(","While bodies must have a condition"
				 "starting with a \"(\".");
		}

		// Consume
		lexer.GetNextToken();

		// Condition of loop is an expression
		Expression();
		token = lexer.PeekNextToken();

		// Closing bracket to end condition
		if(token.lexeme != ")")
		{
			ParseError(token,")","To end a while condition use \")\".");
		}

		// VM code to evaluate expression
		VMCode.push_back("not");
		VMCode.push_back("if-goto WHILE_END" + std::to_string(whileLoopCount));

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// While statement must have a body
		if(token.lexeme != "{")
		{
			ParseError(token,"{","While statements should have a body starting"
				 " with \"{\".");
		}

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Body can be zero or a series of statements
		while(token.lexeme != "}")
		{
			Statement();
			token = lexer.PeekNextToken();
		}
		
		// Consume }
		lexer.GetNextToken();

		// End while loop and increment count for next while statements
		VMCode.push_back("goto WHILE_EXP" + std::to_string(whileLoopCount));
		VMCode.push_back("label WHILE_END" + std::to_string(whileLoopCount));
		++whileLoopCount;
	}

	// doStatement -> do subroutineCall ; 
	void DoStatement()
	{
		Token token = lexer.PeekNextToken();

		// Do statement start with "do"
		if(token.lexeme != "do")
		{
			ParseError(token,"do","");
		}

		// Consume
		lexer.GetNextToken();

		// Followed by a subroutine call
		SubroutineCall();

		token = lexer.PeekNextToken();

		// Ended with a ";"
		if(token.lexeme != ";")
		{
			ParseError(token,";","Do statements should end with a \";\".");
		}

		// Consume ";"
		lexer.GetNextToken();
	}

	// returnStatemnt -> return [ expression ] ;
	void ReturnStatement()
	{
		// Set if return
		if(inIf)
		{
			ifReturn = true;
			inIf = false;
		}

		// Set else return
		else if(inElse)
		{
			elseReturn = true;
			inElse = false;
		}

		// Set return
		else 
		{
			returnStatemntChecked = true; // Set true as in a return statement
		}

		bool expressionCheck = false; // Set true when expression found
		Token token = lexer.PeekNextToken();

		// Return statement should start with the return keyword
		if(token.lexeme != "return")
		{
			ParseError(token,"return","");
		}

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();
		
		// Return keyword can be followed by an expression
		if(token.lexeme != ";")
		{
			// Ensure not void return here as expression should not be expected
			if(getReturnType(currentScope) == "void")
			{
				SemanticError(token,"Void methods or functions should not return a value");
			}
			// Assume user intended to return an expression
			Expression();
			expressionCheck = true; // Got the expression
		}

		// Ensure if not a void function an expression has been found
		if(getReturnType(currentScope) != "void" && !expressionCheck)
		{
			SemanticError(token,"Non-void methods or functions should return a value");
		}

		token = lexer.PeekNextToken();

		// Must end with a ";"
		if(token.lexeme != ";")
		{
			ParseError(token,";","Return statements should end with a \";\".");
		}

		// Consume 
		lexer.GetNextToken();

		// If void function must return 0 as VM functions always return a value
		std::string returnType = getReturnType(currentScope);
		if(returnType == "void" || returnType == "notfound")
		{
			VMCode.push_back("push constant 0");
		}

		VMCode.push_back("return");
	}

	// subroutineCall -> identifier [ . identifier ] ( expressionList )
	void SubroutineCall()
	{
		Token token = lexer.PeekNextToken();
		std::string name = ""; // Joint identifiers
		std::string identifier; // First identifier
		std::string method = ""; // Method part of subroutine call

		// Should start with an identifier or Jack API
		if(token.type != Token::Types::Identifier && token.type != Token::Types::JackAPI)
		{
			ParseError(token,"Method name","");
		}

		// Assign identifier
		name = token.lexeme;
		identifier = token.lexeme;

		// Consume and peek
		lexer.GetNextToken();
		token = lexer.PeekNextToken();

		// Possible have a method of a class
		if(token.lexeme == ".")
		{	
			// Consume "." and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			name += "."; // prepare name for second half

			// Must be followed by an identifier
			if(token.type != Token::Types::Identifier && token.type != Token::Types::JackAPI)
			{
				ParseError(token,"Method name","Did you mean to call a method using the \".\" here.");
			}

			// Assing method part
			name += token.lexeme;
			method = token.lexeme;

			//Consume and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken(); 
		}

		// Must be an open bracket in either case
		if(token.lexeme != "(")
		{
			ParseError(token,"(","A subroutine should include parentheses.");
		}

		// Consume
		lexer.GetNextToken();

		// Must have an expression list then peek
		ExpressionList();
		token = lexer.PeekNextToken();

		// End with a close bracket
		if(token.lexeme != ")")
		{
			ParseError(token,")","Remember to close the subroutine call.");
		}

		// Consume
		lexer.GetNextToken();

		// If the identifier is an array must push identifier
		if(getType(identifier) == "Array")
		{
			writePushVMVariable(token, identifier);

			// Special array method
			if(method == "dispose")
			{
				VMCode.push_back("call Array.dispose 1");
				VMCode.push_back("pop temp 0");
				return;
			}
		}

		// Generic VM commands
		writeVMCallMethod(token,name);
		argCheck = 0;
	}

	// expressionList -> expression { , expression } | ε
	void ExpressionList()
	{
		// An expressionlist can be empty
		// An expression list is only called inside parentheses
		// This means if the list is empty the first token should be ")"

		Token token = lexer.PeekNextToken();

		// Only test for list if not a closing bracket
		if(token.lexeme != ")")
		{
			// Starting expression
			Expression();

			// Increment to check actual and expected arguments match
			++argCheck;

			// The list could be a single expression or multiple comma
			// seperated expressions
			token = lexer.PeekNextToken();

			while(token.lexeme != ")")
			{
				if(token.lexeme != ",")
				{
					ParseError(token,",","Did you mean to write multiple expressions. They must be" 
						 "seperated with a \",\"");
				}

				// Consume call expression and peek
				lexer.GetNextToken();
				Expression();
				++argCheck; // Increment for each one found
				token = lexer.PeekNextToken();
			}
		}
	}

	// expression -> relationalExpression { ( & | | ) relationalExpression }
	void Expression()
	{
		// call relational expression
		RelationalExpression();

		// Potentially have multiple relational expressions
		Token token = lexer.PeekNextToken();

		while(token.lexeme == "&" || token.lexeme == "|")
		{
			// Consume "&" or "|" call relational expression and peek
			lexer.GetNextToken();
			RelationalExpression();

			// generate code for operators
			if(token.lexeme == "&")
			{
				VMCode.push_back("and");
			}
			else if(token.lexeme == "|")
			{
				VMCode.push_back("or");
			}

			token = lexer.PeekNextToken();
		}
	}

	// relationalExpression -> ArithmeticExpression { ( = | > | < ) ArithmeticExpression }
	void RelationalExpression()
	{
		// Call arithmetic expression
		ArithmeticExpression();

		// Potentially have multiple arithmetic expressions
		Token token = lexer.PeekNextToken();

		while(token.lexeme == "=" || token.lexeme == ">" || token.lexeme == "<")
		{
			// Consume "=" or "<" or ">" call arithmetic expression and peek
			lexer.GetNextToken();
			ArithmeticExpression();

			// generate code for operators
			if(token.lexeme == "<")
			{
				VMCode.push_back("lt");
			}
			else if(token.lexeme == ">")
			{
				VMCode.push_back("gt");
			}
			else if(token.lexeme == "=")
			{
				VMCode.push_back("eq");
			}

			token = lexer.PeekNextToken();
		}
	}

	// ArithmeticExpression -> term { ( + | - ) term }
	void ArithmeticExpression()
	{
		// Call term
		Term();

		// Potentially have multiple terms
		Token token = lexer.PeekNextToken();

		while(token.lexeme == "+" || token.lexeme == "-")
		{
			// Consume "+" or "-" call Term and peek
			lexer.GetNextToken();
			Term();

			// generate code for operators
			if(token.lexeme == "+")
			{
				VMCode.push_back("add");
			}
			else if(token.lexeme == "-")
			{
				VMCode.push_back("sub");
			}

			token = lexer.PeekNextToken();
		}
	}

	// term -> factor { ( * | / ) factor }
	void Term()
	{
		// Call factor
		Factor();

		// Potentially have multiple relational expressions
		Token token = lexer.PeekNextToken();

		while(token.lexeme == "*" || token.lexeme == "/")
		{
			// Consume "*" or "/" call Factor and peek
			lexer.GetNextToken();
			Factor();

			// generate code for operators
			if(token.lexeme == "*")
			{
				VMCode.push_back("call Math.multiply 2");
			}
			else 
			{
				VMCode.push_back("call Math.divide 2");
			}

			token = lexer.PeekNextToken();
		}
	}

	// factor -> ( - | ~ | ε ) operand
	void Factor()
	{
		Token token = lexer.PeekNextToken();
		std::string symbol = token.lexeme;

		// A factor could start with a "-", "~", or nothing
		if(token.lexeme == "-" || token.lexeme == "~")
		{
			// Consume and peek
			lexer.GetNextToken();
			token = lexer.PeekNextToken();
		}

		// Must be an operand
		Operand();

		// generate code for operators
		if(symbol == "~")
		{
			VMCode.push_back("not");
		}
		else if(symbol == "-")
		{
			VMCode.push_back("neg");
		}
	}

	// operand -> integerConstant | identifier [.identifier ] [ [ expression ] | 
	//	(expressionList ) ] | (expression) | stringLiteral | true | false | null | this
	void Operand()
	{
		Token token = lexer.PeekNextToken();

		bool notMethod = true; // Methods have special case
		bool notArray = true; // Arrays have special case

		// Check type for integer constant
		if(token.type == Token::Types::IntegerConstant)
		{
			// Add VM code for constants
			VMCode.push_back("push constant " + token.lexeme);

			// Consume constant and return
			lexer.GetNextToken();
			return; 
		}

		// Check for identifier
		if(token.type == Token::Types::Identifier)
		{
			std::string ident = token.lexeme; // store identifier
			std::string method = "";

			// Consume and check for .method
			lexer.GetNextToken();
			token = lexer.PeekNextToken();

			// If token is "." 
			if(token.lexeme == ".")
			{
				// Consume "." and peek
				lexer.GetNextToken();
				token = lexer.PeekNextToken();

				// Must be followed by identifier
				if(token.type != Token::Types::Identifier)
				{
					ParseError(token,"identifier","Did you to use a \".\"");
				}

				method = token.lexeme; // Store method name

				// Consume identifier and peek
				lexer.GetNextToken();
				token = lexer.PeekNextToken();
			}

			// Could be followed by an array or a method
			// First check array
			if(token.lexeme == "[")
			{
				notArray = false; // Is an array

				// Consume and call expression then peek
				lexer.GetNextToken();

				Expression();

				token = lexer.PeekNextToken();

				// Must be "]" to end array
				if(token.lexeme != "]")
				{
					ParseError(token,"]","Did you mean to use the array notation. Arrays should end" 
						 "with an \"]\".");
				}

				// Consume end of array
				lexer.GetNextToken();

				// Generate VM for arrays
				writePushVMVariable(token, ident);
				VMCode.push_back("add");
				VMCode.push_back("pop pointer 1");
				VMCode.push_back("push that 0");
			}

			// Else check for a method
			else if(token.lexeme == "(")
			{
				notMethod = false; // Is a method

				// Consume and call expression list and peek
				lexer.GetNextToken();
				ExpressionList();
				token = lexer.PeekNextToken();

				// Must ")" to end method
				if(token.lexeme != ")")
				{
					ParseError(token,")","Methods must end with \")\".");
				}

				// Consume end of method
				lexer.GetNextToken();

				// generate code for a method call
				writeVMCallMethod(token,ident + "." + method);
				argCheck = 0;
			}

			// Not method or array then is a single identifier
			if(notMethod && notArray)
			{
				// Check it has been initialised before being used in expressions
				if(!IsInitialised(ident))
				{
					SemanticError(token, "Variable " + ident +  " has not been initialised");
				}
				writePushVMVariable(token, ident);
			}

			// Return as end of identifier
			return;
		}

		// Check for bracketed expression
		if(token.lexeme == "(")
		{
			// Consume open bracket call expression and peek
			lexer.GetNextToken();
			Expression();
			token = lexer.PeekNextToken();

			// Must end with a closing bracket
			if(token.lexeme != ")")
			{
				ParseError(token,")","Missing a closing parentheses.");
			}

			// Consume close bracket and retrurn
			lexer.GetNextToken();
			return;
		}

		// Check for string 
		if(token.type == Token::Types::StringConstant)
		{
			// Vm code to create string
			VMCode.push_back("push constant " + std::to_string(token.lexeme.length()));
			VMCode.push_back("call String.new 1");

			// Loop through all characters of string
			for(int i = 0; i < token.lexeme.length(); ++i)
			{
				VMCode.push_back("push constant " + std::to_string(token.lexeme[i]));
				VMCode.push_back("call String.appendChar 2");
			}

			// Consume string and return
			lexer.GetNextToken();
			return;
		}

		// Check for keywords
		// Check for "true"
		if(token.lexeme == "true")
		{
			VMCode.push_back("push constant 1");
			VMCode.push_back("neg");

			// Consume and return
			lexer.GetNextToken();
			return;
		}

		// Check for "false"
		if(token.lexeme == "false")
		{
			VMCode.push_back("push constant 0");

			// Consume and return
			lexer.GetNextToken();
			return;
		}

		// Check for "null"
		if(token.lexeme == "null")
		{
			VMCode.push_back("push constant 0");

			// Consume and return
			lexer.GetNextToken();
			return;
		}

		// Check for "this"
		if(token.lexeme == "this")
		{
			VMCode.push_back("push pointer 0");

			// Consume and return
			lexer.GetNextToken();
			return;
		}

		// If operand is not one of these is an error
		ParseError(token,"operand","");
	}

// Private variables
private:
	Lexer lexer;
};
}
