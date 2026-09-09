#ifndef _PARSE_HPP
#define _PARSE_HPP

#include "param.hpp"

class Parse {
	private:
		Param *commandParameters;
		void isValidInput(char *tokenizedInput) const;
		/**
		 * Validates the command line input.
		 * @param tokenizedInput character pointer containing the input string
		 * @throw invalid_argument exception if the input does not match the expected command syntax
		 */
		void tokensToParam(char *tokenizedInput);
		/**
		 * Processes the tokens and stores their values in a Param object.
		 * @param tokenizedInput pointer to the first token
		 */

	public:
		Parse(char *input);
		~Parse(); //Destructor
		Param *getParameters() const;
};
#endif
