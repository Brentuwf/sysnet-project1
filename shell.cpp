#ifndef _SHELL_CPP
#define _SHELL_CPP

#include <iostream>
#include <string>
#include <cstring>

#include "shell.hpp"
#include "parse.hpp"
#include "param.hpp"

Shell::Shell(int argc, char **argv)
{
	debugMode = false;
	parseArguments(argc, argv);	

}

void Shell::parseArguments(int argc, char **argv)
{
	if (argc > 2) 
        	throw std::runtime_error("Error: Too many arguments Only -Debug is accepted");

    	if ((argc == 2) && (std::strcmp(argv[1], "-Debug") != 0)) 
        	throw std::runtime_error("Unknown argument '" + argv[1] + "' Only -Debug is accepted");

	/* safe, guard clauses will return on args that are not equal to -Debug */
    	debugMode = (argc == 2);
}

#endif 
