/**
 * Implements process creation, command execution, redirection,
 * and child process management for the shell.
 *
 * @author Brent Anderson
 * @author Cadence Phillips
 * @date 09/14/2026
 * @info COP4634
 */

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "process.hpp"

namespace process
{

/**
 * Waits for a specific foreground child process to terminate.
 * @param pid process ID of the child to wait for
 */
static void waitForProcess(pid_t pid)
{
	int status = 0;

	while (true) {
		pid_t result = waitpid(pid, &status, 0);

		if (result == pid) /* Child terminated and was successfully reaped */
			return;

		if ((result == -1) && (errno == EINTR)) //waitpaid may be interrupted by a signal, try again
			continue;

		if (result == -1)     /* Any other waitpid error is unexpected */
			std::perror("waitpid");

		return;
	}
}

/**
 * Creates a child process and executes the command stored in Param.
 *
 * The child performs any requested input/output redirection before
 * calling execvp(). The parent waits for foreground processes but
 * immediately returns for background processes.
 *
 * @param parameters pointer to the parsed command parameters
 */
void executeCommand(const Param *parameters)
{
	if (parameters == nullptr) {
		std::fprintf(stderr, "Error: command parameters are NULL\n");
		return;
	}

	char **arguments = parameters->getArguments(); 

	/* A command must exist before attempting to fork/exec */
	if ((arguments == nullptr) || (arguments[0] == nullptr)) {
		std::fprintf(stderr, "Error: no command specified\n");
		delete[] arguments;
		return;
	}

	/* Create the child process */
	pid_t pid = fork();

	if (pid < 0) {
		std::perror("fork");
		delete[] arguments;
		return;
	}

	/*
	 * Child process
	 */
	if (pid == 0) {

		/*
		 * Redirect standard input if an input filename was supplied.
		 */
		if (parameters->getInputRedirect() != nullptr) {

			if (std::freopen(parameters->getInputRedirect(), "r", stdin) == nullptr) {
				std::fprintf(
					     stderr,
					     "Error: cannot redirect input from '%s': %s\n",
					     parameters->getInputRedirect(),
					     std::strerror(errno)
				           );

				delete[] arguments;

				/*
				 * Use _exit() in the child so inherited parent
				 * output buffers are not flushed a second time.
				 */
				_exit(EXIT_FAILURE);
			}
		}

		/*
		 * Redirect standard output if an output filename was supplied.
		 * "w" creates the file if necessary and truncates an existing file.
		 */
		if (parameters->getOutputRedirect() != nullptr) {

			if (std::freopen(parameters->getOutputRedirect(), "w", stdout) == nullptr) {

				std::fprintf(
					     stderr,
					     "Error: cannot redirect output to '%s': %s\n",
					     parameters->getOutputRedirect(),
					     std::strerror(errno)
				            );

				delete[] arguments;
				_exit(EXIT_FAILURE);
			}
		}

		/*
		 * Execute the command.
		 *
		 * execvp() searches the PATH for commands such as ls, cat,
		 * and grep. It also works with a pathname such as ./slow.
		 *
		 * If execvp succeeds, this process image is replaced and
		 * the code below it is never executed.
		 */
		execvp(arguments[0], arguments);

		/*
		 * Reaching this point means execvp failed.
		 * This handles invalid commands such as "cqt".
		 */
		std::fprintf(
			stderr,
			"Error: unable to execute '%s': %s\n",
			arguments[0],
			std::strerror(errno)
		);

		delete[] arguments;
		_exit(EXIT_FAILURE);
	}

	/*
	 * Parent process.
	 *
	 * The child received its own copy of memory during fork(), so the
	 * parent can safely delete its argument pointer array here.
	 */
	delete[] arguments;

	/*
	 * Foreground command:
	 * wait until the child terminates before displaying another prompt.
	 *
	 * Background command:
	 * do not wait here so the shell can immediately continue.
	 */
	if (parameters->getBackground() == 0)
		waitForProcess(pid);
}
/**
 * Waits for all remaining child processes before the shell terminates.
 * This ensures that the parent shell does not exit while background
 * children are still running.
 */
void waitForAllChildren()
{
	int status = 0;

	while (true) {
		pid_t result = waitpid(-1, &status, 0);
    
		if (result > 0) /* One child was successfully waited for */
			continue;
		if ((result == -1) && (errno == EINTR)) /* Retry if interrupted by a signal */
			continue;
		if ((result == -1) && (errno == ECHILD)) /* ECHILD means there are no children left */
			return;

		if (result == -1) {
			std::perror("waitpid");
			return;
		}
	}
}

}
