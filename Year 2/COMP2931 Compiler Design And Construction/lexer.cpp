/*
	CREATED BY : Matthew Cumber
	STUDENT ID : 201131527
	EMAIL : ll16m23c@leeds.ac.uk

	STYLE:
		lowerCamelcase variables
		UpperCamelcase Methods and ClassNames 
		CAPS macros
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

using namespace std::chrono; 

// Macros to replace ASCII numbers
#define SPACE 32
#define STAR 42 // Same as "*" character
#define NEWLINE 10
#define TAB 9
#define CR 13 // Carriage Return
#define COMMENT 47 // Same as "/" character 
#define DOUBLEQUOTE 34
#define UNDERSCORE 95

// Token definition
class Token
{
public:
	Token()
	{
		lexeme = "";
		tokenLineNumber = 0;
		type = Token::Types::Default;
	}
	~Token(){}

	// Methods
	// Print the token in a readable format used for debugging
	void PrintTokenTerminal()
	{
		std::cout << "Token found on line : ";
		std::cout << tokenLineNumber << std::endl;
		std::cout << "Token lexeme : ";
		std::cout << lexeme << std::endl;
		std::cout << "Token Type : ";
		switch(type)
		{
			case 0 :
				std::cout << "Identifier";
				break;
			case 1 :
				std::cout << "IntegerConstant";
				break;
			case 2 :
				std::cout << "Symbol";
				break;
			case 3 :
				std::cout << "Keyword";
				break;
			case 4 :
				std::cout << "EOF";
				break;
			case 5 :
				std::cout << "StringConstant";
				break;
			case 6 :
				std::cout << "Operator";
				break;
			case 7 :
				std::cout << "JackAPI";
				break;
			default:
				std::cout << "Default";
		}
		std::cout << std::endl;
		std::cout << "------------------------" << std::endl;
	}

	// Fields
	enum Types{Identifier,IntegerConstant,Symbol,Keyword,Eof,StringConstant,Operator,JackAPI,Default};
	Types type;
	std::string lexeme;
	int tokenLineNumber;
};

// Lexer definition
class Lexer
{

// Public methods
public:

	// Constructor
	Lexer(){}

	// Print all tokens to the terminal for debugging
	void Print()
	{
		for(Token token : listOfTokens)
		{
			token.PrintTokenTerminal();
		}
	}

	// Initiate lexical analysis
	void InitLexer(std::string fileName)
	{
		Token nextToken;
		fileLineNumber = 1;

		#ifdef DEBUG
			std::cout << "Initialising the Lexer..." << std::endl;
			std::cout << "Attempting to open the file : ";
			std::cout << fileName << std::endl;
			std::cout << "------------------------" << std::endl;
		#endif

		// Open file and consume beginning comments and white space
		Open(fileName);
		lexerFileName = fileName;
		ConsumeSpaceComments();

		// Create the first token
		nextToken = CreateNextToken();

		#ifdef DEBUG
			std::cout << "Beginning lexical analysis..." << std::endl;
		#endif

		// Read source file until fully tokenized
		while(nextToken.type != 4)
		{
			// Add the tokem to the list
			listOfTokens.push_back(nextToken);

			// Clear all space and comments until a new token is found
			ConsumeSpaceComments();

			// Create a new token
			nextToken = CreateNextToken();
		}

		// Add EOF token to list
		listOfTokens.push_back(nextToken);

		// Set Iterator to the start of the list
		listIterator = listOfTokens.begin();

		// Close the open file
		CloseFile();

		#ifdef DEBUG
			Print();
		#endif

		#ifdef DEBUG
			std::cout << "Lexical analysis successful" << std::endl;
			//std::cout << "------------------------" << std::endl;
		#endif
	}

	// Get the next token from the list of tokens
	// The token is "consumed"
	// For use of the Parser
	Token GetNextToken()
	{
		Token nextToken;
		nextToken = *listIterator;
		std::advance(listIterator,1);
		return nextToken;
	}

	// Peek at the next token from the list of tokens
	// The token is not "consumed"
	// For use by the Parser
	Token PeekNextToken()
	{
		Token nextToken;
		nextToken = *listIterator;
		return nextToken;
	}

// Public variables
public:

	// Words that cannot be used as identifier names and have Keyword type
	std::string reservedWords[21] = {"class","constructor","method","function",
	"int","boolean","char","void","var","static","field","let","do","if",
	"else","while","return","true","false","null","this"};

	std::string jackAPI[41] = {"multiply","divide","min","max","sqrt","String","new",
	"dispose","length","charAt","setCharAt","appendChar","eraseLastChar","intValue",
	"setInt","backSpace","doubleQuote","newLine","Array","moveCursor","printChar",
	"printString","printInt","println","clearScreen","setColour","drawPixel","drawLine",
	"drawRectangle","drawCircle","keyPressed","readChar","readLine","readInt","peek",
	"poke","alloc","deAlloc","halt","error","wait"};

	

	// Operators are special symbols
	std::string operators[9] = {"+","-","*","/","&","|","~","<",">"};

	// Symbols allowed in language
	std::string symbols[10] = {"{","}","[","]","(",")",",",";","=","."};

	// File name being analysed
	std::string lexerFileName = "";

// Private methods
private:

	// Open given file
	void Open(std::string fileName)
	{
		file.sync();
		file.open(fileName);
    	if(!file.is_open())
    	{
    		std::cout << "Error Lexical Analysis" << std::endl;
    		std::cout << "There was an error attempting to open the file : ";
    		std::cout << fileName << std::endl;
    		exit(0);
    	}
	}

	// Close the current open file
	void CloseFile()
	{
		file.close();
	}

	// Consumes space and comments
	void ConsumeSpaceComments()
	{
		// Consume space first as this is most common in body of code
		while(file.peek() == SPACE || file.peek() == NEWLINE || file.peek() == TAB || 
			file.peek() == CR)
		{
			// If new line increment line number
			if(file.peek() == NEWLINE)
			{
				++fileLineNumber;
			}

			// Consume
			file.get();
		} // Space consumed

		// Create string to remove single line comment
		std::string singleLineComment;

		// Consume comments
		while(file.peek() == COMMENT)
		{
			// Consume comment initiator
			file.get();

			// Deal with single line comments first
			if(file.peek() == COMMENT)
			{
				// Whole line can be consumed when single line comment found 
				// And increment linenumber
				getline(file,singleLineComment);
				++fileLineNumber;
				continue;
			}

			// Deal with multi line comments now
			if(file.peek() == STAR)
			{
				// Consume star which signifies multiline comment

				// Handle API comments by consuming second star
				if(file.peek() == STAR)
				{
					file.get();
				}

				// Create infite loop to deal with special case of stars in multiline 
				// Comments
				while(true)
				{
					// Loop rest of comment and consume
					while(file.peek() != STAR)
					{
						// Increment line number when new line
						if(file.peek() == NEWLINE)
						{
							++fileLineNumber;
						}

						// Consume comment body
						file.get();
					}

					// Consume "*"
					file.get();

					// Now check we are actually at the end of the comment
					if(file.peek() == COMMENT)
					{
						file.get();
						break; // End infinite loop
					}
					// If reached here then * is apart of comment body so loop 
					// Again until end of comment
				}
			}

			// The / was actually a token so should create and add the token to the list here
			else
			{
				Token nextToken;
				nextToken.lexeme = "/";
				nextToken.type = Token::Types::Operator;
				nextToken.tokenLineNumber = fileLineNumber;
				listOfTokens.push_back(nextToken);
			}
		} // Comments consumed

		// Call itself to consume space left over after comments
		if(file.peek() == COMMENT || file.peek() == SPACE || 
			file.peek() == NEWLINE || file.peek() == TAB || file.peek() == CR)
		{
			ConsumeSpaceComments();
		}
	}

	// Lookup reserved words
	Token LookUpReservedWords(Token token)
	{
		// Check for keywords
		for(int i = 0; i < 21; ++i)
		{
			if(token.lexeme == reservedWords[i])
			{
				token.type = Token::Types::Keyword;
				return token;
			}
		}

		// Lookup Jack API words
		// for(int i = 0; i < 41; ++i)
		// {
		// 	if(token.lexeme == jackAPI[i])
		// 	{
		// 		token.type = Token::Types::JackAPI;
		// 		return token;
		// 	}
		// }

		// else is an operator
		token.type = Token::Types::Identifier;
		return token;
	}

	// Lookup symbol and operator tokens
	Token LookupSymbolsAndOperators(Token token)
	{
		// Look up to find if token is an operator
		for(int i = 0; i < 9; ++i)
		{
			if(token.lexeme == operators[i])
			{
				token.type = Token::Types::Operator;
				return token;
			}
		}

		// Look up to find if token is a symbol
		for(int i = 0; i < 10; ++i)
		{
			if(token.lexeme == symbols[i])
			{
				token.type = Token::Types::Symbol;
				return token;
			}
		}

		// If code execution reached here then the character is an illegal character
		// Produce an informative error to explain this and stop compilation 
		std::cout << "Error Lexical Analysis in file " << lexerFileName << std::endl;
		std::cout << "On line number : " << fileLineNumber << ", Uknown symbol \"";
		std::cout << token.lexeme << "\" found" << std::endl;
		exit(0);
		return token;
	}

	// Create the next token
	Token CreateNextToken()
	{
		Token nextToken;
		int c = file.peek();

		// Begin tokenizing
		// First check for integer constant
		if(isdigit(c) != 0)
		{
			// Keep adding digits until complete token
			while(isdigit(c) != 0)
			{
				nextToken.lexeme += c;
				file.get();
				c = file.peek();
			}

			// Add line number and type to token
			nextToken.type = Token::Types::IntegerConstant;
			nextToken.tokenLineNumber = fileLineNumber;

			// Return integer constant token
			return nextToken;
		}

		// Check for EOF character for special token
		else if(c == EOF)
		{
			nextToken.lexeme += "EOF";
			nextToken.type = Token::Types::Eof;
			nextToken.tokenLineNumber = fileLineNumber;

			// Return EOF token
			return nextToken;
		}

		// Check for alphabetical character or "_"
		else if(isalpha(c) != 0 || c == UNDERSCORE)
		{
			// Start creating the token
			nextToken.lexeme += (char)c;
			file.get();
			c = file.peek();

			// Add to the token until illegal character found
			while(isalpha(c) != 0 || c == UNDERSCORE || isdigit(c) != 0)
			{
				// Keep adding characters
				nextToken.lexeme += (char)c;

				// Consume the characters
				file.get();
				c = file.peek();
			}

			// Lookup identifier to see if a key word to get token type
			nextToken = LookUpReservedWords(nextToken);

			// Add line number to token
			nextToken.tokenLineNumber = fileLineNumber;

			// Return identifier or keyword
			return nextToken;
		}

		// String literal dealt as special case
		else if(c == DOUBLEQUOTE)
		{
			// Consume first "
			file.get();
			c = file.peek();
			while(c != DOUBLEQUOTE)
			{
				// No escape character in JACK so no need to be considered
				nextToken.lexeme += (char)c;
				file.get();
				c = file.peek();
			}

			// Create string token
			nextToken.type = Token::Types::StringConstant;
			nextToken.tokenLineNumber = fileLineNumber;

			// Consume final "
			file.get();

			// Return string token
			return nextToken;
		}

		// The token should now either be a symbol or operator
		else 
		{
			// Begin creating token
			nextToken.lexeme += (char)c;

			// Decide what the token type is
			nextToken = LookupSymbolsAndOperators(nextToken);

			// Finish token creation
			nextToken.tokenLineNumber = fileLineNumber;

			// Consume character
			file.get();

			// Return symbol or operator token
			return nextToken;
		}

		// Code execution should not reach here
		// Unkown symbols dealt with within LookupSymbolsAndOperators
		// but if it does reach here create an error
		std::cout << "Error on line number : " << fileLineNumber << ", near \"";
		std::cout << nextToken.lexeme << "\" found" << std::endl;
		exit(0);
		return nextToken;
	}

// Private variables
private:

	// Used for Lexer to create tokens
	std::ifstream file;
	int fileLineNumber;

	// Used for Parser manipulated by Lexer
	std::list<Token> listOfTokens;
	std::list<Token>::iterator listIterator;
};
}
