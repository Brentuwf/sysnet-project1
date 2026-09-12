#ifndef _SHELL_CPP
#define _SHELL_CPP

#include <iostream>
#include <string>
#include <cstring>

#include "shell.hpp"
#include "parse.hpp"
#include "param.hpp"

Shell::Shell(int argc, char **argv)
{
	debugMode = false;
	parseArguments(argc, argv);	

}

void Shell::parseArguments(int argc, char **argv)
{
	if (argc > 2) 
        	throw std::runtime_error("Error: Too many arguments Only -Debug is accepted");

    	if ((argc == 2) && (std::strcmp(argv[1], "-Debug") != 0)) 
        	throw std::runtime_error("Unknown argument '" + argv[1] + "' Only -Debug is accepted");

	/* safe, guard clauses will return on args that are not equal to -Debug */
    	debugMode = (argc == 2);
}

int Shell::run()
{
	std::string input = "";
	char *inputCString = nullptr;

	Parse *parser = nullptr;
	Param *parameters = nullptr;

		
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
		delete[] inputCString;
		delete parser;

		inputCString = nullptr;
		parser = nullptr;
		parameters = nullptr;

	} while(true);
	
	return EXIT_SUCCESS;


}
#endif 
