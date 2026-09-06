#ifndef _PARSE_CPP
#define _PARSE_CPP

#include <regex>

#include "parse.hpp"

bool Parse::isValidInput(char *input) const
{
	/*  Regex pattern breakdown:
         * ^\S+            command, one or more non-whitespace, no leading whitespace
         * (\s+\S+)*       optional arguments, zero or more space-separated tokens
         * (\s*<\s+\S+)?   optional input redirect < file requires single space
         * (\s*>\s+\S+)?   optional output redirect > file requires single space
         * (\s*&)?         optional background execution
         * $               end of string
	 */
        std::regex pattern("^\\S+(\\s+\\S+)*(\\s*<\\s+\\S+)?(\\s*>\\s+\\S+)?(\\s*&)?$");

	return std::regex_match(input, pattern);
}




#endif 
