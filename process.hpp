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
	void executeCommand(const Param *parameters);
	 /**
	 * Creates a child process and executes the command stored in Param.
	 * Handles input/output redirection and foreground/background execution.
	 *
	 * @param parameters pointer to the parsed command parameters
	 */
	void reapBackgroundProcesses();
	 /**
	 * Checks for terminated background child processes and reaps them
	 * without blocking the shell.
	 */
	void waitForAllChildren();
	 /**
	 * Waits for all remaining child processes to terminate.
	 * Used before the shell exits.
	 */
}	

#endif
