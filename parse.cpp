/**
 * Parses and validates shell command input and stores the results in a Param object.
 *
 * Brent Anderson and Cadence Phillips
 * 09/14/2026
 * COP4634
 */

#ifndef _PARSE_CPP
#define _PARSE_CPP

#include <cstring>      
#include <regex>
#include <stdexcept>

#include "parse.hpp"

Parse::Parse(char *input)
{
	commandParameters = nullptr;

	/*
	 * Validate BEFORE tokenizing because strtok() changes
	 * the original input string.
	 */
	isValidInput(input);

	/* Create an empty Param object to hold parsed values */
	commandParameters = new Param();

	/* Get the first token */
	char *firstToken = std::strtok(input, " \t\n");

	/* Process the first token and all remaining tokens */
	try {
		tokensToParam(firstToken);
	} catch (const std::out_of_range &message) {
		delete commandParameters;
		throw;
	}
}

Parse::~Parse()
{
	delete commandParameters;
	commandParameters = nullptr;
}

void Parse::isValidInput(char *input) const
{
	/**
 	 * Regular Expression Breakdown 
 	 *
 	 * ^ Forces the match to begin the beginning of the input 
 	 * 
 	 * \s* Allow leading whitespace, tokenizer will take care of parsing it  
 	 * 
 	 * ([^\s<>&]+)? First command, allows characters as long as they are not whitespace, <, >, or &.
 	 * 
 	 * (\s+[^\s<>&]+)* Allows zero or more command-line arguments, requires one or morespacing between arguments   
	 *
	 * (\s*<[^\s<>&]+)? Input redirection, Enforces no space between redirect and filename 
 	 * 
 	 * (\s*>[^\s<>&]+)? Output redirection, Enforces no space between redirect and filename 
 	 * 
 	 * (\s*&\s*)? Background execution 
 	 * 
 	 * $ Enforces background execution token must be the last token
 	 */	
	std::regex pattern(R"(^\s*([^\s<>&]+)?(\s+[^\s<>&]+)*(\s*<[^\s<>&]+)?(\s*>[^\s<>&]+)?(\s*&\s*)?\s*$)");

	if (!std::regex_match(input, pattern))
		throw std::invalid_argument("Input is not valid syntax");
}

/**
 * Assumes input has been processed through isValidInput and is valid 
 *
 * Normal tokens are added to argumentVector
 * Tokens beginning with '<' specify input redirection
 * Tokens beginning with '>' specify output redirection
 * '&' specifies background execution
 *
 */
void Parse::tokensToParam(char *tokenizedInput)
{
	char *token = tokenizedInput;
	
	while (token != nullptr) {
    		switch (token[0]) {
			/* Background execution */
        		case '&':
            			commandParameters->setBackground(1);
            			break;
			/* Input redirection: example <input.txt */
        		case '<':
				/* token + 1 skips the '<' character */
            			commandParameters->setInputRedirect(token + 1);
            			break;
			/* Output redirection: example >output.txt */
        		case '>':
				/* token + 1 skips the '>' character */
            			commandParameters->setOutputRedirect(token + 1);
            			break;
			/* Normal command or argument */
        		default:
            			commandParameters->addArgument(token);
            			break;
		}
		/* Get the next token */
    		token = std::strtok(nullptr, " \t\n");
	}
}

Param *Parse::getParameters() const
{
	return commandParameters;
}


#endif
