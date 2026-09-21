/**
 * Simple command-line shell that parses user commands
 * and supports redirection, background execution, and debug output.
 *
 * @author Brent Anderson
 * @date 09/14/2026
 * @info COP4634
 */

#ifndef _PROCESS_HPP
#define _PROCESS_HPP

namespace process 
{
	/*
	 * functions for fork, exec, and file redirections are going here
	 * does not need memory allocation while use waitpid with WNOHANG to prevent zombies
	 */
	/**
	 * Registers sigchldHander to handle SIGCHLD signal from background child processes
	 */
	void setupSigchldHandler();
};

#endif
