/**
 * Sets ups variables needed for the parsing and execution for the shell and run the main
 * loop for running parsing input and running commands in the shell
 *
 * @author Brent Anderson 
 * @author Cadence Phillips
 * @date 09/14/2026
 * @info COP4634
 */

#ifndef _SHELL_CPP
#define _SHELL_CPP

#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "shell.hpp"
#include "parse.hpp"
#include "param.hpp"
#include "process.hpp"

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
        	throw std::runtime_error("Unknown argument '" + std::string(argv[1]) + "' Only -Debug is accepted");

	/* safe, guard clauses will return on args that are not equal to -Debug */
    	debugMode = (argc == 2);
}

void Shell::run()
{
	std::string input = "";

	/* memory is allocated and freed every loop, no need for class level scope */
	char *inputCString = nullptr;
	Parse *parser = nullptr;
	Param *parameters = nullptr;
	
	char **argumentsVector = nullptr;
	bool isBackground = false;
	char *inputRedirectFile = nullptr;
	char *outputRedirectFile = nullptr;
	
	/* handles waiting for background processes using signal handler */	
	process::setupSigchldHandler();	

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
			argumentsVector = parameters->getArguments();
			inputRedirectFile = parameters->getInputRedirect();
			outputRedirectFile = parameters->getOutputRedirect();
			isBackground = parameters->getBackground();

			/* Temporary Part I testing */
			if (debugMode)
				parameters->printParams();

			pid_t pid = fork();
			
			if (pid < 0)
				throw std::runtime_error("failed to create new process");

			if (pid == 0) {
				//if (inputRedirectFile != nullptr)
					// function call for file redirect

				//if (outputRedirectFile != nullptr)
					// function call for file redirect
				
				if (execvp(argumentsVector[0], argumentsVector) == -1 ) {
					perror(argumentsVector[0]);
					_exit(EXIT_FAILURE);
				}
			} else {
				int status;
				
				if (!isBackground) 
					if (waitpid(pid, &status, 0) == -1)
						throw std::runtime_error("waitpid failed");
			}
		}
		catch (const std::exception& message) {
			std::cerr << message.what() << std::endl;
		}

		/* Clean up to prevent memory leaks on additional shell commands */
		delete parser;
		delete[] inputCString;
		delete[] argumentsVector; 

		inputCString = nullptr;
		parser = nullptr;
		parameters = nullptr;
		argumentsVector = nullptr;
		isBackground = false;
		inputRedirectFile = nullptr;
		outputRedirectFile = nullptr;
	} while(true);
	
}

#endif 
