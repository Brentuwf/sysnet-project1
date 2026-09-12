/**
 * Simple command-line shell that parses user commands
 * and supports redirection, background execution, and debug output.
 *
 * Brent Anderson
 * 09/14/2026
 * COP4634
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

#include "param.hpp"
#include "parse.hpp"

int main(int argc, char **argv) {

	std::string input = "";
	char *inputCString = nullptr;
	bool debugMode = false;

	Parse *parser = nullptr;
	Param *parameters = nullptr;

	if (argc > 2) {
        	std::cerr << "Error: Too many arguments. Only -Debug is accepted." << std::endl;
        	return EXIT_FAILURE;
    	}

    	if ((argc == 2) && (std::strcmp(argv[1], "-Debug") != 0)) {
        	std::cerr << "Unknown argument '" << argv[1] << "' Only -Debug is accepted" << std::endl;
        	return EXIT_FAILURE;
   	}

	/* safe, guard clauses will return on args that are not equal to -Debug */
    	debugMode = (argc == 2);
	
	do {
		std::cout << "$$$ ";
		getline(std::cin, input);

		if (input.empty()) {
			std::cout << "Input is empty" << std::endl;
			continue;
		}

		/* Exit shell when user enters "exit" */
		if (input == "exit")
			break;

		/* inputCString will be passed to parser */
		inputCString = new char[input.length() + 1];
		std::strcpy(inputCString, input.c_str());

		/* Parser function calls */
		try {
			parser = new Parse(inputCString);

			/* Get the parsed command parameters */
			parameters = parser->getParameters();

			/* Temporary Part I testing */
			if (debugMode)
				parameters->printParams();

			// future logic for fork and execv/execvp
		}
		catch (const std::exception& message) {
			std::cerr << message.what() << std::endl;
		}

		/* Clean up to prevent memory leaks on additional shell commands */
		delete parser;
		delete[] inputCString;

		inputCString = nullptr;
		parser = nullptr;
		parameters = nullptr;

	} while(true);
	
	return EXIT_SUCCESS;
}
