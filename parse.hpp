/**
 * This program prompts the user for two input values to compute the average of the two values.
 *
 * @author Thomas Reichherzer
 * @date 8/12/2016
 * @info Course COP3014
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
