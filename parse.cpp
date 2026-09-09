#ifndef _PARSE_CPP
#define _PARSE_CPP

#include <cstring>      // strtok(), strcmp()
#include <regex>
#include <stdexcept>

#include "parse.hpp"


/**
 * Constructs a Parse object and parses the command line input.
 *
 * @param input character pointer containing the command line input
 */
Parse::Parse(char *input)
{
	commandParameters = nullptr;

	if (input == nullptr || input[0] == '\0')
		throw std::invalid_argument("Input is empty");

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
	tokensToParam(firstToken);
}


/**
 * Destructor for Parse.
 */
Parse::~Parse()
{
	delete commandParameters;
	commandParameters = nullptr;
}


/**
 * Validates command line input before it is tokenized.
 */
void Parse::isValidInput(char *input) const
{
	/*
	 * Regex pattern breakdown:
	 *
	 * ^\S+            command, one or more non-whitespace characters
	 * (\s+\S+)*       optional arguments, separated by whitespace
	 * (\s*<\s+\S+)?   optional input redirection
	 * (\s*>\s+\S+)?   optional output redirection
	 * (\s*&)?         optional background execution
	 * $               end of string
	 */
	std::regex pattern(
		"^\\S+(\\s+\\S+)*(\\s*<\\s+\\S+)?(\\s*>\\s+\\S+)?(\\s*&)?$"
	);

	if (!std::regex_match(input, pattern))
		throw std::invalid_argument("Input is not valid syntax");
}

/**
 * Processes the tokens and stores their values in the Param object.
 *
 * Normal tokens are added to argumentVector.
 * Tokens beginning with '<' specify input redirection.
 * Tokens beginning with '>' specify output redirection.
 * '&' specifies background execution.
 *
 * @param tokenizedInput pointer to the first token
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
            			if (token[1] == '\0') 
                			throw std::invalid_argument("Input redirect requires a filename");
				/* token + 1 skips the '<' character */
            			commandParameters->setInputRedirect(token + 1);
            			break;
			/* Output redirection: example >output.txt */
        		case '>':
            			if (token[1] == '\0') 
                			throw std::invalid_argument("Output redirect requires a filename");
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


/**
 * Returns the Param object containing the parsed command information.
 *
 * @return pointer to commandParameters
 */
Param *Parse::getParameters() const
{
	return commandParameters;
}


#endif
