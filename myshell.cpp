/**
 * Simple command-line shell that parses user commands
 * and supports redirection, background execution, and debug output.
 *
 * Brent Anderson
 * 09/14/2026
 * COP4634
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
		delete shell;
	} catch (const std::exception &message) {
		std::cerr << message.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
