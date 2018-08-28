/*******************************************************************************
  Title          : babyname.cpp
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Implementation of the Babyname class
  Purpose        : To provide implementation for processing baby names
  Build with     : Makefile (included)
  Modifications  : 

  Notes
*******************************************************************************/

#include "babyname.h"


// default constructor 
Babyname::Babyname()
{
  std::cout << "Creating Babyname Object..." << std::endl;
}


bool Babyname::set( int           year, 
                    Gender        gender, 
                    Ethnicity     ethnicity,
                    std::string   name,
                    int           count,
                    int           rank
                  )
{
  // Automatically false to reset when recalled
  // Will be called multiple times
  
  bool valid_year =       false;
  bool valid_gender =     false;
  bool valid_ethnicity =  false;
  bool valid_name =       false;
  bool valid_count =      false;
  bool valid_rank =       false;
  

  // checks to see if one of the possible years
  // if true, parameter is within specified values
  if (year == 2011 || year == 2012 || year == 2013 || 
      year == 2014 || year == 2015 || year == 2016) 
  {
    valid_year = true;
  }

  // checks to see if one of the possible genders
  // if true, parameter is within specified values
  if (gender == female || gender == male) 
  {
    valid_gender = true;
  }

  // checks to see if one of the possible ethnicities
  // if true, parameter is within specified values
  if (ethnicity == asian || ethnicity == black || ethnicity == hispanic ||
      ethnicity == white) 
  {
    valid_ethnicity = true;
  }

  // checks to see if the string contains something (a name)
  // if true, parameter is within specified values
  if (name != "") 
  {
    valid_name = true;
  }

  // checks to see if count is value (i.e. non-negative)
  // if true, parameter is within specified values
  if (0 <= count) 
  {
    valid_count = true;
  }

  // checks to see if its of valid rank value
  // if true, parameter is within specified values
  if (0 < rank) 
  {
    valid_rank = true;
  }

  // if all parameters are within specified ranges (all true)
  if (valid_year == true && valid_gender == true && valid_ethnicity == true
      && valid_name == true && valid_count == true && valid_rank == true) 
  {
    // write all object values
    Baby.birthYear = year;
    Baby.babyGender = gender;
    Baby.motherEthnicity = ethnicity;
    Baby.babyName = name;
    Baby.nameCount = count;
    Baby.nameRank = rank;

    return true;
  }

  // all parameters are NOT within specified ranges (NOT all true)
  return false;  
}



void Babyname::get( int           &  year, 
                    Gender        &  gender, 
                    Ethnicity     &  ethnicity,
                    std::string   &  name,
                    int           &  count,
                    int           &  rank
                  )
{

  // Automatically false to reset when recalled
  // Will be called multiple times
  // Redone because of post condition that all ojects assigned are valid
  
  bool valid_birthYear =        false;
  bool valid_babyGender =       false;
  bool valid_motherEthnicity =  false;
  bool valid_babyName =         false;
  bool valid_nameCount =        false;
  bool valid_nameRank =         false;
  

  // checks to see if one of the possible years
  // if true, parameter is within specified values
  if (Baby.birthYear == 2011 || Baby.birthYear == 2012 || Baby.birthYear == 2013 || 
      Baby.birthYear == 2014 || Baby.birthYear == 2015 || Baby.birthYear == 2016) 
  {
    valid_birthYear = true;
  }

  // checks to see if one of the possible genders
  // if true, parameter is within specified values
  if (Baby.babyGender == female || Baby.babyGender == male) 
  {
    valid_babyGender = true;
  }

  // checks to see if one of the possible ethnicities
  // if true, parameter is within specified values
  if (Baby.motherEthnicity == asian || Baby.motherEthnicity == black || 
      Baby.motherEthnicity == hispanic || Baby.motherEthnicity == white) 
  {
    valid_motherEthnicity = true;
  }

  // checks to see if the string contains something (a name)
  // if true, parameter is within specified values
  if (Baby.babyName != "") 
  {
    valid_babyName = true;
  }

  // checks to see if count is value (i.e. non-negative)
  // if true, parameter is within specified values
  if (0 <= Baby.nameCount) 
  {
    valid_nameCount = true;
  }

  // checks to see if its of valid rank value (0<)
  // if true, parameter is within specified values
  if (0 < Baby.nameRank) 
  {
    valid_nameRank = true;
  }

  // if all parameters are with specified ranges (all true)
  if (valid_birthYear == true && valid_babyGender == true && 
      valid_motherEthnicity == true && valid_babyName == true && 
      valid_nameCount == true && valid_nameRank == true) 
  {
    //write all object values to parameters
    year = Baby.birthYear;
    gender = Baby.babyGender;
    ethnicity = Baby.motherEthnicity;
    name = Baby.babyName;
    count = Baby.nameCount;
    rank = Baby.nameRank; 
  }
}



void Babyname::print (std::ostream & s, const Data reconfigure)
{ 
  // holder variables to convert from enum types (Gender & Ethnicity)
  // blank string variable to print out in words (instead of the enumerated values)
  // Automatically blank to reset when recalled
  // Will be called multiple times
  std::string tempGender = "";
  std::string tempEthnicity = "";

  // Determines which of the Genders to print as the Gender
  switch(Baby.babyGender)
  {
    case male:
      tempGender = "MALE";
      break;
    case female:
      tempGender = "FEMALE";
      break;
    case anyGender:                   // for unexpected results
      tempGender = "undefined";
      break;
  }

  // Determines which of the Ethnicities to print as the Ethnicity
  switch(Baby.motherEthnicity)
  {
    case asian:
      tempEthnicity = "ASIAN AND PACIFIC ISLANDER";
      break;
    case black:
      tempEthnicity = "BLACK NON HISPANIC";
      break;
    case hispanic:
      tempEthnicity = "HISPANIC";
      break;
    case white:
      tempEthnicity = "WHITE NON HISPANIC";
      break;
    case anyEthnicity:                // for unexpected results
      tempEthnicity = "undefined";
      break;
  }

  // Determines the order in which to print by
  switch(reconfigure)
  {
    case byDefault:     //Order: Year,Gender,Ethnicity,Name,Count,Rank
      s << Baby.birthYear << "," << tempGender << "," << tempEthnicity << "," 
        << Baby.babyName << "," << Baby.nameCount << "," << Baby.nameRank 
        << std::endl;
      break;
    case byYear:        //Order: Year,Ethnicity,Gender,Name,Count,Rank
      s << Baby.birthYear << "," << tempEthnicity << "," << tempGender << "," 
        << Baby.babyName << "," << Baby.nameCount << "," << Baby.nameRank 
        << std::endl;
      break;
    case byGender:      //Order: Gender,Year,Ethnicity,Name,Count,Rank
      s << tempGender << "," << Baby.birthYear << "," << tempEthnicity << "," 
        << Baby.babyName << "," << Baby.nameCount << "," << Baby.nameRank 
        << std::endl;
      break;
    case byEthnicity:   //Order: Ethnicity,Year,Gender,Name,Count,Rank
      s << tempEthnicity << "," << Baby.birthYear << "," << tempGender << "," 
        << Baby.babyName << "," << Baby.nameCount << "," << Baby.nameRank 
        << std::endl;
      break;
    case byName:        //Order: Name,Ethnicity,Gender,Year,Count,Rank
      s << Baby.babyName << "," << tempEthnicity << "," << tempGender << "," 
        << Baby.birthYear << "," << Baby.nameCount << "," << Baby.nameRank 
        << std::endl;
      break;
    case byCount:       //Order: Count,Rank,Year,Ethnicity,Gender,Name
      s << Baby.nameCount << "," << Baby.nameRank << "," << Baby.birthYear << "," 
        << tempEthnicity << "," << tempGender << "," << Baby.babyName 
        << std::endl;
      break;
    case byRank:        //Order: Rank,Count,Year,Ethnicity,Gender,Name
      s << Baby.nameRank << "," << Baby.nameCount << "," << Baby.birthYear << "," 
        << tempEthnicity << "," << tempGender << "," << Baby.babyName 
        << std::endl;
      break;
  }
}


bool isRepeat(const Babyname & lt, const Babyname & rt)
{
  // Compares all attributes of both babies
  // If a match on every attribute, then babie must be a repeat
  if ((lt.Baby.birthYear == rt.Baby.birthYear) && 
      (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
      (lt.Baby.babyGender == rt.Baby.babyGender) && 
      (lt.Baby.babyName == rt.Baby.babyName) && 
      (lt.Baby.nameCount == rt.Baby.nameCount) && 
      (lt.Baby.nameRank == rt.Baby.nameRank)) 
  {
    return true;
  }

  return false;
}


/*******************************************************************************   
                            match_byXYZ Function Group
*******************************************************************************/

bool match_byYear(const Babyname & lt, const int year)
{
  // If User Selected YEAR matches current Baby's YEAR
  // If True, match found
  if(lt.Baby.birthYear == year)
  {
    return true;
  }

  return false;
}


bool match_byGender(const Babyname & lt, const Gender gen)
{
  // If User Selected GENDER matches current Baby's GENDER
  // If True, match found
  if(lt.Baby.babyGender == gen)
  {
    return true;
  }

  return false;
}


bool match_byEthnicity(const Babyname & lt, const Ethnicity eth)
{
  // If User Selected ETHNICITY matches current Baby's ETHNICITY
  // If True, match found
  if(lt.Baby.motherEthnicity == eth)
  {
    return true;
  }

  return false;
}


bool match_byName(const Babyname & lt, const std::string name)
{
  // If User Input NAME matches current Baby's NAME
  // If True, match found
  if(lt.Baby.babyName == name)
  {
    return true;
  }

  return false;
}