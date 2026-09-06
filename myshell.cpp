#include <cstdlib>
#include <cstdio>
#include "param.hpp"

int main(int argc, char* argv[]) {
	Param *testParam = new Param();

	for (int i = 0; i < argc; i++) 
                testParam->addArgument(argv[i]);

	testParam->printParams();

	char **testGetArguments = testParam->getArguments();

	for (int i = 0; i < argc; i++) 
		fprintf(stdout, "%s\n", testGetArguments[i]);

	delete[] testGetArguments;

	delete testParam;

	return EXIT_SUCCESS;
}
