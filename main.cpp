/*******************************************************************************
  Title          : main.cpp
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Main file that runs setup, interface and exit directions
  Purpose        : Program to analyze, sort and search NYC Baby-name data
  Build with     : Makefile (included)
  Modifications  : 

  Notes
*******************************************************************************/

#include "command.h"


int main(int argc, char *argv[])
{
	Command Interface;
	
	Interface.loadFile(argc, argv);
	Interface.userPrompt();
    Interface.exitFile();

	return 0;
}
