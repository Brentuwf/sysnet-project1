#ifndef _PARSE_CPP
#define _PARSE_CPP

#include <cstring>      // strtok()
#include <regex>
#include <stdexcept>

#include "parse.hpp"


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
		throw std::invalid_argument("Input does is not valid syntax");
}

char *Parse::tokenizer(char *input)
{
	// Separate tokens using spaces, tabs, and newline characters.
	return std::strtok(input, " \t\n");
}

#endif

/**
 * Begins tokenizing the command line input.
 * strtok() returns the first token when the input string is supplied.
 * Additional tokens can later be retrieved by calling:
 *
 *     std::strtok(nullptr, " \t\n");
 *
 * @param input character pointer containing the command line input
 * @return pointer to the first token, or nullptr if no token exists
 */
