#include <cstdlib>
#include "param.hpp"

int main() {
	Param *testParam = new Param();

	testParam->printParams();

	return EXIT_SUCCESS;
}
