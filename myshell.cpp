#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include "param.hpp"
#include "parse.hpp"

int main(int argc, char **argv) {

	std::string input;
	bool debugMode = false;

	if (argc > 2) {
        	std::cerr << "Error: Too many arguments. Only -Debug is accepted." << std::endl;
        	return 1;
    	}

    	if ((argc == 2) && (strcmp(argv[1], "-Debug") == 0)) {
 		debugMode = true;
        } else {
        	std::cerr << "Unknown argument '" << argv[1] << "' Only -Debug is accepted" << std::endl;
        	return 1;
        }
	
	do {
		std::cout << "$$$ ";
		getline(std::cin, input);

		/* Exit shell when user enters "exit" */
		if (input == "exit")
			break;

		/* inputCString will be passed to parser */
		char *inputCString = new char[input.length() + 1];
		std::strcpy(inputCString, input.c_str());

		/* Parser function calls */
		try {
			Parse parser(inputCString);

			/* Get the parsed command parameters */
			Param *parameters = parser.getParameters();

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
		inputCString = nullptr;

	} while(true);

	/* test below remove before submission */
	Param *testParam = new Param();

	for (int i = 0; i < argc; i++) {
		try {
			testParam->addArgument(argv[i]);
		}
		catch (std::invalid_argument& message) {
			std::cerr << message.what() << std::endl;
		}
		catch (std::out_of_range& message) {
			std::cerr << message.what() << std::endl;
		}
	}

	testParam->printParams();

	char **testGetArguments = testParam->getArguments();

	delete[] testGetArguments;

	delete testParam;

	return EXIT_SUCCESS;
}
