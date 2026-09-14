/**
 * Defines the Parse class used to validate and parse shell command input
 *
 * @author Brent Anderson  
 * @author Cadence Phillips
 * @date 09/14/2026
 * @info COP4634
 */

#ifndef _PARSE_HPP
#define _PARSE_HPP

#include "param.hpp"

class Parse {
	private:
		Param *commandParameters; /* Param object for storing parameters after tokenization */
		/**
		 * Validates the command line input
		 *
		 * @param tokenizedInput character pointer containing the input string
		 * @throw invalid_argument exception if the input does not match the expected command syntax
		 */
		void isValidInput(char *tokenizedInput) const;

		/**
		 * Processes the tokens and stores their values in a Param object
		 * @param tokenizedInput pointer to the first token
		 */
		void tokensToParam(char *tokenizedInput);
		
	public:
		/**
 		 * Constructs a Parse object and parses the command line input
 		 *
 		 * @param input character pointer containing the command line input
		 *
		 * @throw out_of_range exception from param class if input is greater than 32 tokens 
 		 */
		Parse(char *input);

		/**
 		 * Destructor for Parse
		 * Responsible for cleaning up param object the constructor creates
 		 */
		~Parse();

		/**
 		 * Returns the Param object containing the parsed command information
 		 *
 		 * @return pointer to commandParameters
 		 */
		Param *getParameters() const;
};
#endif
