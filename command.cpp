/******************************************************************************
  Title          : command.cpp
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Implementation for the command class
  Purpose        : To provide implementation for handling user selections
  Build with     : Makefile (included)
  Modifications  : 
 
  Notes
  		The reason why a string variable was used for userInput was because 
  		the user entry verification step fails otherwise. For char userInput, 
  		it would accept 1e or 222222, because it started with 1 or 2 and etc.
  		Due to this constraint, a switch statement could not have been used
 		as switch statements only works with primitive data types.
*******************************************************************************/

#include "command.h"

// default constructor 
Command::Command()
{
	std::cout << "Creating Command Object..." << std::endl;
}


void Command::loadFile(int argc, char *argv[])
{
	// makes sure user provides appropriate # of arguments 
	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " argument" << std::endl;
	}

	else { 
		// As specified, the first argument is the dataset
		dataInput.open(argv[1]);				// open dataset
		dataOutput.open("results.csv");			// open output file
		
		// Checking for successful open
		if (dataInput.fail()) {
			std::cerr << "The file " << argv[1] << " could not be opened" << std::endl;
		}

		// Variable Declarations
		// Corresponding variable types to hold expected data types from file
		int tempYear = 0;
		std::string tempGender = "";					// input will be in string
		std::string tempEthnicity = "";					// input will be in string
		std::string tempName = "";
		int tempCount = 0;
		int tempRank = 0;

		int baby_arrIndex = 0;	// index holder to be passed to addBaby function
		char tempComma;			// dummy to hold commas


		std::string dummyLine;				// dummy variable for file headline
		getline(dataInput, dummyLine);		// capture the headline in its entirety

		// keeps input going until there is nothing left
		while (dataInput >> tempYear) 
		{
			dataInput >> tempComma;		// dummy for comma
			
			getline(dataInput, tempGender, ',');		// capture gender data & stop at comma
			
			getline(dataInput, tempEthnicity, ',');		// capture ethnicity & stop at comma
			
			getline(dataInput, tempName, ',');			// capture name & stop at comma

			dataInput >> tempCount;						// capture count
			dataInput >> tempComma;						// stop at comma

			dataInput >> tempRank;						// capture rank (no comma after rank)

			// send to function to add current baby data to vector	
			allBabies.addBaby(baby_arrIndex, dataOutput, tempYear, tempGender, 
							  tempEthnicity, tempName, tempCount, tempRank);
			

			baby_arrIndex++;	// increase index by 1 each time 
		}
	}
}


void Command::userPrompt()
{
	// Function Variables
	// always resets for safety
	flag = true;		// for while loop
	userInput = "";		// empty string to hold user entry

 	while(flag)			// equates while(true) aka always
 	{
 		// main user prompt
 		std::cout << "\n" << "Choose (1) Statistical Analysis\n" <<
 						"       (2) Sort Functions\n" <<
 						"       (3) Search Functions\n" << //endl;
 						"       (E) Exit\n\n" <<
 						"Entry: ";
 		
 		// take user entry	
 		std::cin >> userInput;

 		// verify user entry is of appropriate type
 		if(userInput == "1" || userInput == "2" || userInput == "3" || 
 		   userInput == "E" || userInput == "e")
 		{
 			flag = false;  // if not, while loop runs again
 		}
 	}

 	// check for exit first
 	if(userInput == "E" || userInput == "e")
 	{
 		std::cout << std::endl;		// print empty line for neatness in console
		exit(0);					// exit entirely
 	}

 	else if(userInput == "1")
 	{
 		performStat();				// go to the Stats selection
 	}

 	else if(userInput == "2")
 	{
 		performSort();				// go to the Sort selection
 	}

 	else if(userInput == "3")
 	{
 		performSearch();			// go to the Search selection
 	}
}


void Command::performStat()
{
	// Function Variables
	// always resets for safety
	flag = true;		// for while loop
	userInput = "";		// empty string to hold user entry

 	while(flag)			// equates while(true) aka always
 	{
 		// Stats user prompt
 		std::cout << "\n" << "Choose (1) Stats by YEAR\n" <<
 				"       (2) Stats by GENDER\n" <<
 				"       (3) Stats by ETHNICITY\n" <<
 				"       (4) All Stats\n" <<
 				"       (E) Exit\n\n" <<
 				"Entry: ";
 		
 		// take user entry
 		std::cin >> userInput;

 		// verify user entry is of appropriate type
 		if(userInput == "1" || userInput == "2" || userInput == "3" || 
 		   userInput == "4" || userInput == "E" || userInput == "e")
 		{
 			flag = false;	// if not, while loop runs again
 		}
 	}

 	// check for exit first
 	if(userInput == "E" || userInput == "e")
 	{
 		std::cout << std::endl;		// print empty line for neatness in console
		exit(0);					// exit entirely
 	}

 	else if(userInput == "1")
 	{
 		// always resets for safety
 		flag = true;				// for while loop
		userInput = "";				// empty string to hold user entry
		int year_userInput = 0;		// used to send user year to function

 		while(flag)					// equates while(true) aka always
 		{
 			// Stats-Year user prompt
 			std::cout << "\n" << "Choose (1) Stats for 2011\n" <<
 					"       (2) Stats for 2012\n" <<
 					"       (3) Stats for 2013\n" <<
 					"       (4) Stats for 2014\n" <<
 					"       (5) Stats for 2015\n" <<
 					"       (6) Stats for 2016\n" <<
 					"       (7) Stats for ALL Years\n" <<
 					"       (E) Exit\n\n" <<
 					"Entry: ";
 			
 			// take user entry
 			std::cin >> userInput;

 			// verify user entry is of appropriate type
 			if(userInput == "1" || userInput == "2" || userInput == "3" || 
 			   userInput == "4" || userInput == "5" || userInput == "6" ||
 			   userInput == "7" || userInput == "E" || userInput == "e")
 			{
 				flag = false;		// if not, while loop runs again
 			}
 		}

 		// check for exit first
 		if(userInput == "E" || userInput == "e")
 		{
 			std::cout << std::endl;		// print empty line for neatness in console
			exit(0);					// exit entirely
 		}

 		// sets variable to user selected Year
 		else if(userInput == "1")
 		{
 			year_userInput = 2011;
 		}

 		else if(userInput == "2")
 		{
 			year_userInput = 2012;
 		}

 		else if(userInput == "3")
 		{
 			year_userInput = 2013;
 		}

 		else if(userInput == "4")
 		{
 			year_userInput = 2014;
 		}

 		else if(userInput == "5")
 		{
 			year_userInput = 2015;
 		}

 		else if(userInput == "6")
 		{
 			year_userInput = 2016;
 		}

 		// if user chose All, just run stats for all Years
 		else if(userInput == "7")
 		{
 			allBabies.stats_allYears(dataOutput);	// user chose no Year, all
 			exitFile();								// must run before exit(0)
			exit(0);								// exit entirely
 		}											// such that file directions are printed
													// exit(0) will skip "Interface.exitFile();"
													// in main file

 		// run function & pass user selected Year to it
 		allBabies.stats_byYear(dataOutput, year_userInput);
 	}


 	else if(userInput == "2")
 	{
 		// always resets for safety
 		flag = true;				// for while loop
		userInput = "";				// empty string to hold user entry
		Gender gen_userInput = anyGender;		// used to send user Gender to function

 		while(flag)					// equates while(true) aka always
 		{
 			// Stats-Gender user prompt
 			std::cout << "\n" << "Choose (1) Stats for MALES\n" <<
 					"       (2) Stats for FEMALES\n" <<
 					"       (3) Stats for ALL Genders\n" <<
 					"       (E) Exit\n\n" <<
 					"Entry: ";
 			
 			// take user entry
 			std::cin >> userInput;

 			// verify user entry is of appropriate type
 			if(userInput == "1" || userInput == "2" || userInput == "3" || 
 			   userInput == "E" || userInput == "e")
 			{
 				flag = false;			// if not, while loop runs again
 			}
 		}

 		// check for exit first
 		if(userInput == "E" || userInput == "e")
 		{
 			std::cout << std::endl;			// print empty line for neatness in console
			exit(0);						// exit entirely
 		}									

 		// sets variable to user selected Gender
		else if(userInput == "1")
 		{
 			gen_userInput = male;
 		}

 		else if(userInput == "2")
 		{
 			gen_userInput = female;
 		}

 		// if user chose All, just run stats for all Genders
 		else if(userInput == "3")
 		{
 			allBabies.stats_allGenders(dataOutput);	// user chose no Gender, All
 			exitFile();								// must run before exit(0)
			exit(0);								// such that file directions are printed									
 		}											// exit(0) will skip "Interface.exitFile();"
													// in main file

 		// run function & pass user selected Gender to it
 		allBabies.stats_byGender(dataOutput, gen_userInput);
 	}


 	else if(userInput == "3")
 	{
 		// always resets for safety
 		flag = true;				// for while loop
		userInput = "";				// empty string to hold user entry
		Ethnicity eth_userInput = anyEthnicity;	// used to send user Ethnicity to function

 		while(flag)					// equates while(true) aka always
 		{
 			// Stats-Ethnicity user prompt
 			std::cout << "\n" << "Choose (1) Stats for ASIAN AND PACIFIC ISLANDERS\n" <<
 					"       (2) Stats for BLACK NON HISPANICS\n" <<
 					"       (3) Stats for HISPANICS\n" <<
 					"       (4) Stats for WHITE NON HISPANICS\n" <<
 					"       (5) Stats for ALL Ethnicities\n" <<
 					"       (E) Exit\n\n" <<
 					"Entry: ";
 			
 			// take user entry
 			std::cin >> userInput;

 			// verify user entry is of appropriate type
 			if(userInput == "1" || userInput == "2" || userInput == "3" || 
 			   userInput == "4" || userInput == "5" || userInput == "E" || 
 			   userInput == "e")
 			{
 				flag = false;		// if not, while loop runs again
 			}
 		}

 		// check for exit first
 		if(userInput == "E" || userInput == "e")
 		{
 			std::cout << std::endl;
			exit(0);
 		}

 		// sets variable to user selected Ethnicity
		else if(userInput == "1")
 		{
 			eth_userInput = asian;
 		}

 		else if(userInput == "2")
 		{
 			eth_userInput = black;
 		}

 		else if(userInput == "3")
 		{
 			eth_userInput = hispanic;
 		}

 		else if(userInput == "4")
 		{
 			eth_userInput = white;
 		}

 		// if user chose All, just run stats for all Ethnicities
 		else if(userInput == "5")
 		{
 			allBabies.stats_allEthnicities(dataOutput);	// user chose no Ethnicity, All
 			exitFile();									// must run before exit(0)
			exit(0);									// such that file directions are printed
 		}												// exit(0) will skip "Interface.exitFile();"
														// in main file

 		// run function & pass user selected Ethnicity to it
 		allBabies.stats_byEthnicity(dataOutput, eth_userInput);
 	}

 	else if(userInput == "4")
 	{
 		allBabies.stats_All(dataOutput);
 	}
}


void Command::performSort()
{
	// always resets for safety
	flag = true;				// for while loop
	userInput = "";				// empty string to hold user entry

	while(flag)					// equates while(true) aka always
	{
		// Sort user prompt
		std::cout << "\n" << "Choose (1) Sort by YEAR\n" <<
 				"       (2) Sort by GENDER\n" <<
 				"       (3) Sort by ETHNICITY\n" <<
 				"       (4) Sort by NAME\n" <<
 				"       (5) Sort by COUNT\n" <<
 				"       (6) Sort by RANK\n" << //endl;
 				"       (E) Exit\n\n" <<
 				"Entry: ";
 		
 		// take user entry
 		std::cin >> userInput;

 		// verify user entry is of appropriate type
 		if(userInput == "1" || userInput == "2" || userInput == "3" || userInput == "4" || 
 		   userInput == "5" || userInput == "6" || userInput == "E" || userInput == "e")
 		{
 			flag = false;		// if not, while loop runs again
 		}
 	}

 	// check for exit first
 	if(userInput == "E" || userInput == "e")
 	{
 		std::cout << std::endl;
		exit(0);
 	}

 	// calls functions for user selected Sort type
 	else if(userInput == "1")
 	{
 		allBabies.sort_byYear(dataOutput);		// calls function to sort by Year
 	}

 	else if(userInput == "2")
 	{
 		allBabies.sort_byGender(dataOutput);	// calls function to sort by Gender
 	}

 	else if(userInput == "3")
 	{
 		allBabies.sort_byEthnicity(dataOutput);	// calls function to sort by Ethnicity
 	}

 	else if(userInput == "4")
 	{
 		allBabies.sort_byName(dataOutput);		// calls function to sort by Name
 	}

 	else if(userInput == "5")
 	{
 		allBabies.sort_byCount(dataOutput);		// calls function to sort by Count
 	}

 	else if(userInput == "6")
 	{
 		allBabies.sort_byRank(dataOutput);		// calls function to sort by Rank
 	} 	
}


void Command::performSearch()
{
	// always resets for safety
	flag = true;				// for while loop
	userInput = "";				// empty string to hold user entry

 	while(flag)					// equates while(true) aka always
 	{
 		// Search user prompt
 		std::cout << "\n" << "Choose (1) Search by YEAR\n" <<
 				"       (2) Search by GENDER\n" <<
 				"       (3) Search by ETHNICITY\n" <<
 				"       (4) Search by NAME\n" <<
 				"       (E) Exit\n\n" <<
 				"Entry: ";
 		
 		// take user entry	
 		std::cin >> userInput;

 		// verify user entry is of appropriate type
 		if(userInput == "1" || userInput == "2" || userInput == "3" || 
 		   userInput == "4" || userInput == "E" || userInput == "e")
 		{
 			flag = false;		// if not, while loop runs again
 		}
 	}

 	// check for exit first
 	if(userInput == "E" || userInput == "e")
 	{
 		std::cout << std::endl;
		exit(0);
 	}

 	else if(userInput == "1")
 	{
 		// always resets for safety
 		flag = true;				// for while loop
		userInput = "";				// empty string to hold user entry
		int year_userInput = 0;		// used to send user year to function

 		while(flag)					// equates while(true) aka always
 		{
 			// Search-Year user prompt
 			std::cout << "\n" << "Choose (1) Search for 2011\n" <<
 					"       (2) Search for 2012\n" <<
 					"       (3) Search for 2013\n" <<
 					"       (4) Search for 2014\n" <<
 					"       (5) Search for 2015\n" <<
 					"       (6) Search for 2016\n" <<
 					"       (E) Exit\n\n" <<
 					"Entry: ";
 			
 			// take user entry
 			std::cin >> userInput;

 			// verify user entry is of appropriate type
 			if(userInput == "1" || userInput == "2" || userInput == "3" || 
 			   userInput == "4" || userInput == "5" || userInput == "6" ||
 			   userInput == "E" || userInput == "e")
 			{
 				flag = false;		// if not, while loop runs again
 			}
 		}

 		// check for exit first
 		if(userInput == "E" || userInput == "e")
 		{
 			std::cout << std::endl;
			exit(0);
 		}	

 		// sets variable to user selected Year
 		else if(userInput == "1")
 		{
 			year_userInput = 2011;
 		}

 		else if(userInput == "2")
 		{
 			year_userInput = 2012;
 		}

 		else if(userInput == "3")
 		{
 			year_userInput = 2013;
 		}

 		else if(userInput == "4")
 		{
 			year_userInput = 2014;
 		}

 		else if(userInput == "5")
 		{
 			year_userInput = 2015;
 		}

 		else if(userInput == "6")
 		{
 			year_userInput = 2016;
 		}

 		// run function & pass user selected Year to it
 		allBabies.search_byYear(dataOutput, year_userInput);
 	}


 	else if(userInput == "2")
 	{
 		// always resets for safety
 		flag = true;				// for while loop
		userInput = "";				// empty string to hold user entry
		Gender gen_userInput = anyGender;	// used to send user Gender to function

 		while(flag)					// equates while(true) aka always
 		{
 			// Search-Gender user prompt
 			std::cout << "\n" << "Choose (1) Search for MALE\n" <<
 					"       (2) Search for FEMALE\n" <<
 					"       (E) Exit\n\n" <<
 					"Entry: ";
 			
 			// take user entry
 			std::cin >> userInput;

 			// verify user entry is of appropriate type
 			if(userInput == "1" || userInput == "2" || 
 			   userInput == "E" || userInput == "e")
 			{
 				flag = false;		// if not, while loop runs again
 			}
 		}

 		// check for exit first
 		if(userInput == "E" || userInput == "e")
 		{
 			std::cout << std::endl;
			exit(0);
 		}

 		// sets variable to user selected Gender
		else if(userInput == "1")
 		{
 			gen_userInput = male;
 		}

 		else if(userInput == "2")
 		{
 			gen_userInput = male;
 		}

 		// run function & pass user selected Gender to it
 		allBabies.search_byGender(dataOutput, gen_userInput);
 	}


 	else if(userInput == "3")
 	{
 		// always resets for safety
 		flag = true;				// for while loop
		userInput = "";				// empty string to hold user entry
		Ethnicity eth_userInput = anyEthnicity;	// used to send user Ethnicity to function

 		while(flag)					// equates while(true) aka always
 		{
 			// Search-Ethnicity user prompt
 			std::cout << "\n" << "Choose (1) Search for ASIAN AND PACIFIC ISLANDER\n" <<
 					"       (2) Search for BLACK NON HISPANIC\n" <<
 					"       (3) Search for HISPANIC\n" <<
 					"       (4) Search for WHITE NON HISPANIC\n" <<
 					"       (E) Exit\n\n" <<
 					"Entry: ";
 			
 			// take user entry
 			std::cin >> userInput;

 			// verify user entry is of appropriate type
 			if(userInput == "1" || userInput == "2" || userInput == "3" || 
 			   userInput == "4" || userInput == "E" || userInput == "e")
 			{
 				flag = false;		// if not, while loop runs again
 			}
 		}

 		// check for exit first
 		if(userInput == "E" || userInput == "e")
 		{
 			std::cout << std::endl;
			exit(0);
 		}

 		// sets variable to user selected Ethnicity
		else if(userInput == "1")
 		{
 			eth_userInput = asian;
 		}

 		else if(userInput == "2")
 		{
 			eth_userInput = black;
 		}

 		else if(userInput == "3")
 		{
 			eth_userInput = hispanic;
 		}

 		else if(userInput == "4")
 		{
 			eth_userInput = white;
 		}

 		// run function & pass user selected Ethnicity to it
 		allBabies.search_byEthnicity(dataOutput, eth_userInput);
 	}

 	else if(userInput == "4")
 	{
 		// always resets for safety
 		flag = true;					// for while loop
		std::string findName = "";		// empty string to hold user entry

 		while(flag)						// equates while(true) aka always
 		{
 			// Search-Name user prompt
 			std::cout << "\n" << "Enter a NAME: ";
 			
 				// take user entry
 				std::cin >> findName;

 				// place a space inbetween for consle neatness
 				std::cout << std::endl;

 				// verify user entry is of appropriate type
 				// a non-empty string
 				if(findName != "")
 				{
 					flag = false;	// if not, while loop runs again
 				}
 		}

 		// sets user entered name to capital letters
  		// makes searching for names in the vector trivial as all names
  		// were saved in all capital letters during vector entry
  		// can accept Amy, AMY, amy, aMy and etc and will match to AMY
		for(int i = 0; i < findName.size(); i++) 
		{
    		findName.at(i) = toupper(findName.at(i));
		}

		// run function & pass user entered Name to it
 		allBabies.search_byName(dataOutput, findName);
 	}
}


void Command::exitFile()
{
	// close output stream
	dataOutput.close();

	// inform user where file is saved to and under what name
	std::cout << "File saved in currect directory as: results.csv" << std::endl << std::endl;
}