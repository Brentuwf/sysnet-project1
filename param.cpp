/**
 *  param.hpp
 *  
 *  Thomas Reichherzer
 *  Copyright 2009 UWF - CS. All rights reserved.
 *
 */

#ifndef _PARAM_CPP
#define _PARAM_CPP

#include <iostream>

#include "param.hpp"

Param::Param() 
{
	inputRedirect = outputRedirect = NULL;
	background = 0;
	argumentCount = 0;
}

void Param::addArgument(char *newArgument)
{
	// finish this
}

char** Param::getArguments()
{
	// finish this
	return NULL;
}

void Param::setInputRedirect(char *newInputRedirect)
{
	//finish this
}

void Param::setOutputRedirect(char *newOutputRedirect)
{
	//finish this
}
		
void Param::setBackground(int newBackground)
{
	//finish this
}

char* Param::getInputRedirect()
{
	return inputRedirect;
}
		
		
char* Param::getOutputRedirect()
{
	return outputRedirect; 
}

		
int Param::getBackground()
{
	return background;
}


void Param::printParams() 
{
	std::cout << "InputRedirect: [" 
	     << (inputRedirect != NULL) ? inputRedirect : "NULL";
	std::cout << "]" 
	     << std::endl 
		 <<	"OutputRedirect: [" 
		 << (outputRedirect != NULL) ? outputRedirect : "NULL";
	std::cout << "]" 
	     << std::endl 
		 << "Background: [" 
		 << background 
		 << "]" 
		 << std::endl 
		 << "ArgumentCount: [" 
		 << argumentCount 
		 << "]" 
		 << std::endl;
	for (int i = 0; i < argumentCount; i++)
		std::cout << "ArgumentVector[" 
			 << i 
			 << "]: [" 
			 << argumentVector[i] 
			 << "]" 
			 << std::endl;
}

#endif

