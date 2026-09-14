/**
 * Defines the Shell class used to set up and run the main loop for the shell 
 *
 * @author Brent Anderson 
 * @author Cadence Phillips
 * @date 09/14/2026
 * @info COP4634
 */

#ifndef _SHELL_HPP
#define _SHELL_HPP

class Shell
{
	private:
		bool debugMode; /* true if the shell is running in debug mode, false otherwise */
		/**
		 * Parses the command line arguments for the shell to determine if the shell is to be 
		 * run in debug mode
		 * -Debug is the only option implemented
		 *
		 * @param int for number of command line arguments
		 * @param char** for the command line arguments array 
		 *
        	 * @throw runtime_error exception if invalid command line arguments are passed
		 */
		void parseArguments(int argc, char **argv);

	public:
		/**
		 * Constructor for the shell object
		 * Calls parseArguments function to determine if the shell is to
		 * be run in debug mode
		 *
		 * @param int for number of command line arguments
		 * @param char** for the command line arguments array 
		 */
		Shell(int argc, char **argv);
		/**
		 * Contains the main loop for reading in user input, parsing, and executing commands
		 */
		void run();
};

#endif 
