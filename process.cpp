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
#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>
#include <csignal>
#include <cerrno>

#include "process.hpp"

void process::sigchldHandler(int signo)
{
	/* removed warning for unused parameter */
	(void)signo;

	/* preserves error number */
	int savedErrno = errno;  
	pid_t pid;
	int status;
 
       	/* reaps terminated background child processes, out error message if child exited abnormally
	 * uses write syscall instead of printf or cout to prevent locking of buffers 
	 */ 
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		if ((WIFEXITED(status) && WEXITSTATUS(status) != 0) || WIFSIGNALED(status)) {
			const char message[] = "Background child exited abnormally\n";
			write(STDERR_FILENO, message, sizeof(message) - 1);
		}
	}
	
	/* guard clause for waitpid failing, ignores ECHILD errno as having no 
	 * child processes to wait on is not an error condition for reaping background 
	 * processes
	 */
	if (pid == -1 && errno != ECHILD) {
        	const char message[] = "waitpid failed in SIGCHLD handler\n";
        	write(STDERR_FILENO, message, sizeof(message) - 1);
    	}

	errno = savedErrno;  
}

void process::setupSigchldHandler()
{
	struct sigaction sa;

	sa.sa_handler = sigchldHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
 
	if (sigaction(SIGCHLD, &sa, nullptr) == -1)
		throw std::runtime_error("failed to register SIGCHLD handler");
}
