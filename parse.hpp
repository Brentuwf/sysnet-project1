#ifndef _PARSE_HPP
#define _PARSE_HPP

#include "param.hpp"

class Parse {
	private:
		Param *commandParameters;
		/**
		 * Validates input after it has been passed to the tokenizer
		 * Disallows no space between input and output redirect symbols
		 * @param char *input, character pointer for input string, assumes non empty string is passed
		 * @throw invalid_argument exception if regex returns false
		 */
		void isValidInput(char *tokenizedInput) const;
		char *tokenizer(char *input);
		void tokensToParam(char *tokenizedInput);

	public:
		Parse(char *input);
		~Parse();
		Param *getParameters() const;


};

#endif
