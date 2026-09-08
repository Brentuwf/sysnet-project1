#ifndef _PARSE_HPP
#define _PARSE_HPP

class Parse {
	private:
		/**
		 * Validates input after it has been passed to the tokenizer
		 * Disallows no space between input and output redirect symbols
		 * @param char *input, character pointer for input string, assumes non empty string is passed
		 * @throw invalid_argument exception if regex returns false
		 */
		void isValidInput(char *input) const;

	public:



};

#endif
