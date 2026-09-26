/**
 * Declares helper functions for process creation, command execution,
 * redirection, and child process management.
 *
 * @author Brent Anderson
 * @author Cadence Phillips
 * @date 09/14/2026
 * @info COP4634
 */

#ifndef _PROCESS_HPP
#define _PROCESS_HPP

#include "param.hpp"

namespace process
{
	void waitForProcess(pid_t pid);
	 /**
	 * Creates a child process and executes the command stored in Param.
	 * Handles input/output redirection and foreground/background execution.
	 *
	 * @param parameters pointer to the parsed command parameters
	 */
	void executeCommand(const Param *parameters);
	 /**
	 * Waits for all remaining child processes to terminate.
	 * Used before the shell exits.
	 */
	void waitForAllChildren();
	/**
	 * Signal handler for SIGCHLD
	 * Reaps any terminated background child processes without blocking
	 *
	 * @param int representing signo, the signal number that triggered this handler
	 */
	void sigchldHandler(int signo);

	/**
	 * Registers sigchldHander to handle SIGCHLD signal from background child processes
	 */
	void setupSigchldHandler();
}	

#endif
