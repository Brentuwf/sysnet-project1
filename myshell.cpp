#include <cstdlib>
#include "param.hpp"

int main(int argc, char* argv[]) {
	Param *testParam = new Param();

	testParam->printParams();

	return EXIT_SUCCESS;
}
