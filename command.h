/******************************************************************************
  Title          : command.h
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Interface for the command class
  Purpose        : The Command class represents a command object
  Build with     : Makefile (included)
  Modifications  : 
 
  Notes

*******************************************************************************/

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "babycollection.h"
#include <fstream>          // for file streams


/*******************************************************************************   
                              Command Class Interface
*******************************************************************************/

class Command
{
public:
    /** Command()  A default constructor for the class 
     */
    Command();
    
    /* loadFile() - takes the given file and fills the vector with input stream
     *              also creates the output stream for file named: results.csv
     *
     * @param int   argc   [in]  argument count
     * @param char *argv[] [in]  argument vector
     *
     * @pre   file to be read is included at program arguments
     * @post  the vector will be filled with all availble non-repeat baby data
     */
    void loadFile(int argc, char *argv[]);


    /* userPrompt() - brings up user prompt with given options to select from
     *                prompts are separated into 3 main categories:
     *                Statistical Analysis
     *                Sort Functions
     *                Search Functions
     *                each contains further specifications
     *
     * @param none
     *
     * @pre   data file is loaded into vector
     * @post  commands will be executed according to the 3 main categories
     */
    void userPrompt();


    /* exitFile() - closes the output stream and informs the user 
     *              that the file was saved in current directory
     *
     * @param none
     *
     * @pre   all operations were done as needed
     * @post  data saved into file named: results.csv
     */
    void exitFile();


private:
    /* 3 member functions that perform similar tasks;
     * performStat() - interface for user selection of statistical data
     * by similar logic
     * performSort() - interface for user selection of sort data
     * performSearch() - interface for user selection of search criteria
     *
     * @param none
     *
     * @pre   none
     * @post  appropriate functions are called to do the selected task
     */
    void performStat();
    void performSort();
    void performSearch();

    Babycollection allBabies;       // Babycollection Object for user actions
    
    std::ifstream dataInput;        // input stream
    std::ofstream dataOutput;       // output stream

    // variables that will constantly be used in member functions
    bool flag;                      // to check user actions
    std::string userInput;          // to hold user entry
};


#endif /* __COMMAND_H__ */