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
#include <cstring>
#include <stdexcept>

#include "param.hpp"

Param::Param() 
{
	inputRedirect = nullptr;
	outputRedirect = nullptr;
	background = 0;
	argumentCount = 0;

	for (int i = 0; i < MAXARGS; ++i)
		argumentVector[i] = nullptr;
}

Param::~Param() 
{
	for (int i = 0; i < argumentCount; ++i)
		delete[] argumentVector[i];
}

void Param::addArgument(char *newArgument)
{
	/* header guard to prevent adding nullptr */
	if (newArgument == nullptr)
		throw std::invalid_argument("newArgument is NULL");
	
	/* header guard to prevent going out of bounds or overiding the string terminator*/
	if (argumentCount >= MAXARGS -1)
		throw std::out_of_range("Input tokens are greater than the maximum ammount");

	argumentVector[argumentCount] = strdup(newArgument);
	argumentCount++;
}

char** Param::getArguments() const
{
	char **argumentsVector = new char*[argumentCount + 1];

	/* shallow copy, caller only needs to delete memeory for the array of char * */	
	for (int i = 0; i < argumentCount; ++i)
		argumentsVector[i] = argumentVector[i];

	argumentsVector[argumentCount] = (char *) NULL; /* Needed for execv/execvp */

	return argumentsVector;
}

void Param::setInputRedirect(char *newInputRedirect)
{
	inputRedirect = newInputRedirect;	
}

void Param::setOutputRedirect(char *newOutputRedirect)
{
	outputRedirect = newOutputRedirect;
}
		
void Param::setBackground(int newBackground)
{
	background = newBackground;
}

char* Param::getInputRedirect() const
{
	return inputRedirect;
}
		
		
char* Param::getOutputRedirect() const
{
	return outputRedirect; 
}

		
int Param::getBackground() const
{
	return background;
}


void Param::printParams() const
{
	std::cout << "InputRedirect: [" 
	     << (inputRedirect != nullptr) ? inputRedirect : "NULL";
	std::cout << "]" 
	     << std::endl 
		 <<	"OutputRedirect: [" 
		 << (outputRedirect != nullptr) ? outputRedirect : "NULL";
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

