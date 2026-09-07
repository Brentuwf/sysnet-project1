#include <cstdlib>
#include <iostream>
#include "param.hpp"

int main(int argc, char* argv[]) {
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
