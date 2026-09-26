/**
 * Declares helper functions for process creation, command execution,
 * redirection, and child process management.
 *
 * @author Brent Anderson
 * @author Cadence Phillips
 * @date 09/26/2026
 * @info COP4634
 */

#ifndef _PROCESS_HPP
#define _PROCESS_HPP

#include "param.hpp"

namespace process
{
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
	 * Registers sigchldHander to handle SIGCHLD signal from background child processes
	 * @throw std::runtime_error if registering sigchld handler fails
	 */
	void setupSigchldHandler();
}	

#endif
