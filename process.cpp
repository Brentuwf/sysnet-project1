/**
 * Simple command-line shell that parses user commands
 * and supports redirection, background execution, and debug output.
 *
 * @author Brent Anderson
 * @date 09/14/2026
 * @info COP4634
 */

/*
 * additionall includes from sys/ for fork/exec/and redirects
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <csignal>

#include "process.hpp"

void process::setupSigchldHandler()
{
	struct sigaction sa;

	sa.sa_handler = sigchldHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
 
	sigaction(SIGCHLD, &sa, nullptr);
}
