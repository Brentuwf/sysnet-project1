/**
 * Simple command-line shell that parses user commands
 * and supports redirection, background execution, and debug output.
 *
 * @author Brent Anderson
 * @date 09/14/2026
 * @info COP4634
 */

#include <stdexcept>
#include <iostream>
#include <cstdlib>

#include "shell.hpp"

int main(int argc, char **argv) {
	Shell *shell = nullptr;
	try {
		shell = new Shell(argc, argv);
		shell->run();
	} catch (const std::runtime_error &message) {
		std::cerr << message.what() << std::endl;
		delete shell;
		return EXIT_FAILURE;
	}
	delete shell;
	return EXIT_SUCCESS;
}
