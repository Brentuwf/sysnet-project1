
#ifndef _SHELL_HPP
#define _SHELL_HPP

class Shell
{
	private:
		bool debugMode;
		void parseArguments(int argc, char **argv);

	public:
		Shell(int argc, char **argv)
		int run();
};

#endif 
