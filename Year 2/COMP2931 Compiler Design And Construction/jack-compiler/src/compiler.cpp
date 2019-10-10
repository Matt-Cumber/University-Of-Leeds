/*
	CREATED BY : Matthew Cumber
	STUDENT ID : 201131527
	EMAIL : ll16m23c@leeds.ac.uk

	STYLE:
		lowerCamelcase variables
		UpperCamelcase Methods and ClassNames 
		CAPS macros
*/

/*
	CURRENT STATUS:
		LEXER 				:	COMPLETE
		PARSER 				:	COMPLETE
		SYMBOL TABLE		:	COMPLETE
		SEMANTIC ANALYSER 	:	INCOMPLETE
		VM GENERATOR 		:	INCOMPLETE
		COMPILING DIRECTORY :	INCOMPLETE
*/

#include "parser.cpp"

namespace COMPILER 
{

// This class compiles all files passed to it
class Compiler
{

// Public methods
public:

	// Constructor
	Compiler(){}

	// Compile a file
	void Compile(std::string fileName)
	{
		#ifdef DEBUG
			std::cout << "Beginning Compilation..." << std::endl;
			std::cout << "------------------------" << std::endl;
		#endif

		// Run parser
		Parser parser;
		parser.Parse(fileName);

		// Create VM file
		parser.generateVMCode();

		#ifdef DEBUG
			std::cout << "------------------------" << std::endl;
			std::cout << "Compilation successful" << std::endl;
			std::cout << "------------------------" << std::endl;
		#endif
	}
};
}

using namespace COMPILER;

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		std::cout << "Enter a file on the command line to compile" << std::endl;
		exit(0);
	}

	Compiler compiler;
	compiler.Compile(argv[1]);

	return 0;
}
