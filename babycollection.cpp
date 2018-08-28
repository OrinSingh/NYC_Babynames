/*******************************************************************************
  Title          : babycollection.cpp
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Implementation of the Babycollection class
  Purpose        : To provide implementation for processing baby names
  Build with     : Makefile (included)
  Modifications  : 
 
  Notes

*******************************************************************************/

#include "babycollection.h"
#include <iomanip>      // for std::setprecision function
#include <algorithm>    // for std::sort function


// default constructor 
Babycollection::Babycollection()
{
  std::cout << "Creating Babycollection Object..." << std::endl;
}

void Babycollection::addBaby(int            indx, 
                             std::ostream & s,
                             int            year,
                             std::string    gender,
                             std::string    ethnicity,
                             std::string    name,
                             int            count,
                             int            rank)
{
  // automatically false to reset when recalled
  // will be called multiple times 
  trip = false;


  Gender enum_gender = anyGender;           // for converted Gender
  Ethnicity enum_ethnicity = anyEthnicity;  // for converted Ethnicity

  // Converts std::string gender to type Gender
  // Converts std::string ethnicity to type Ethnicity
  enum_gender = convert_genderString(gender);
  enum_ethnicity = convert_ethnicityString(ethnicity);
  

  // sets all names to CAPITAL letters
  for(size_t i = 0; i < name.size(); i++) 
  {
    name.at(i) = toupper(name.at(i));
  }

  // temporary Babyname object to hold the data to push into vector
  tempBaby.set(year, enum_gender, enum_ethnicity, name, count, rank);
  
  // first baby cannot be a repeat
  if(indx == 0)
  {
    babyList.push_back(tempBaby);
  }

  // checking before every input here forward for repeats
  else
  {
    for(size_t i = 0; i < babyList.size(); i++)
    {
      // friend function from Babyname class to determind repeats
      tempBool = isRepeat(babyList.at(i), tempBaby);

      if(tempBool == true)
      {
        trip = true;
      }
    }

    // if flag not tripped, not repeat, add baby
    if(trip == false)
    {
      babyList.push_back(tempBaby);
    }
  }
}

// takes data from the stream and converts into enumerated type
// type Gender specified in babyname.h file, on top
Gender Babycollection::convert_genderString(const std::string gen)
{
  if (gen == "FEMALE" || gen == "Female" || gen == "female") 
  {
    return female;
  }

  else if (gen == "MALE" || gen == "Male" || gen == "male") 
  {
    return male;
  }

  return anyGender;            // for wildcard values
}


// takes data from the stream and converts into enumerated type
// type Ethnicity specified in babyname.h file, on top
Ethnicity Babycollection::convert_ethnicityString(const std::string eth)
{
  if (eth == "ASIAN AND PACIFIC ISLANDER" || eth == "ASIAN AND PACI") 
  {
    return asian;
  }

  else if (eth == "BLACK NON HISPANIC" || eth == "BLACK NON HISP") 
  {
    return black;
  }

  else if (eth == "HISPANIC" || eth == "HISP") 
  {
    return hispanic;
  }

  else if (eth == "WHITE NON HISPANIC" || eth == "WHITE NON HISP") 
  {
    return white;
  }

  return anyEthnicity;        // for wildcard values
}

// method for printing the entire babyList vector in the order specified
void Babycollection::printVector(std::ostream & s, const Data recon)
{
  for(size_t i = 0; i < babyList.size(); i++)
  {
    babyList.at(i).print(s, recon);
  }  
}

/*******************************************************************************   
                    stats_byXYZ/stats_allXYZ Function Group
*******************************************************************************/

void Babycollection::stats_byYear(std::ostream & s, const int year)
{
  // Variable Declaratons
  // type double due to decimal results
  // set all to zero
  double numBabies =      0,
         alt_numBabies =  0,
         numMales =       0,
         numFemales =     0,
         numAsian =       0,
         numBlack =       0,
         numHispanic =    0,
         numWhite =       0,
         perYear =        0,
         perMale =        0,
         perFemale =      0,
         perAsian =       0,
         perBlack =       0,
         perHispanic =    0,
         perWhite =       0;

  // Variables to hold termporary data that will be generated
  int temp_year = 0;                  // dummy
  Gender temp_gen = anyGender;        // used
  Ethnicity temp_eth = anyEthnicity;  // used
  std::string temp_name = "";         // dummy
  int temp_count = 0;                 // used
  int temp_rank = 0;                  // dummy

  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byYear(babyList.at(i), year);    // find match

    if(tempBool == true) 
    {
      babyList.at(i).get(temp_year, temp_gen, temp_eth, temp_name, temp_count, temp_rank);

      numBabies = numBabies + temp_count;     // extract and keep only count from match

      // extract gender data and keep count according to gender
      switch(temp_gen)
      {
        case male:
          numMales = numMales + temp_count;
          break;
        case female:
          numFemales = numFemales + temp_count;
          break;
        case anyGender:
          std::cout << "undefined" << std::endl;    // for unexpected wildcards
          break;
      }

      // extract the ethnicity data and keep count according to ethnicity
      switch(temp_eth)
      {
        case asian:
          numAsian = numAsian + temp_count;
          break;
        case black:
          numBlack = numBlack + temp_count;
          break;
        case hispanic:
          numHispanic = numHispanic + temp_count;
          break;
        case white:
          numWhite = numWhite + temp_count;
          break;
        case anyEthnicity:
          std::cout << "undefined" << std::endl;    // for unexpected wildcards
          break;
      }
    }

    // keep count of the # of babies that weren't a match to find %total match
    else if(tempBool == false) 
    {
      babyList.at(i).get(temp_year, temp_gen, temp_eth, temp_name, temp_count, temp_rank);

      alt_numBabies = alt_numBabies + temp_count;     // extract and keep only count
    }
  }

  // Calculations Section
  // (#Match/#Total)*100
  perYear = ((numBabies/(numBabies + alt_numBabies))*100);

  // (#Gender/#Match)*100
  perMale = ((numMales/numBabies)*100);
  perFemale = ((numFemales/numBabies)*100);
  
  // (#Ethnicity/#Match)*100
  perAsian = ((numAsian/numBabies)*100);
  perBlack = ((numBlack/numBabies)*100);
  perHispanic = ((numHispanic/numBabies)*100);
  perWhite = ((numWhite/numBabies)*100);


  // Output Section
  // allows full number to show during repeated calls in the stats_allXYZ functions
  s << std::setprecision(6);
  
  // display the number of babies that were a match for the given year
  s << numBabies << "," << "" << "," << "babies were born in" << "," << year << std::endl;

  // display all values in decimal form to 4 sigfigs for percent values
  s << std::setprecision(4);

  // displaying the percent of given years babies from total babies
  s << perYear << "%" << "," << "" << "," << "babies were born in" << "," << year << std::endl;

  // displaying the percent genders of the given year
  s << perMale << "%" << "," << year << "," << "babies were born" << "," << "MALE" << std::endl;
  s << perFemale << "%" << "," << year << "," << "babies were born" << "," << "FEMALE" << std::endl;

  // displaying the percent ethnicities of the given year
  s << perAsian << "%" << "," << year << "," << "babies were born" << "," << "ASIAN AND PACIFIC ISLANDER" << std::endl;
  s << perBlack << "%" << "," << year << "," << "babies were born" << "," << "BLACK NON HISPANIC" << std::endl;
  s << perHispanic << "%" << "," << year << "," << "babies were born" << "," << "HISPANIC" << std::endl;
  s << perWhite << "%" << "," << year << "," << "babies were born" << "," << "WHITE NON HISPANIC" << std::endl << std::endl;
}


void Babycollection::stats_byGender(std::ostream & s, const Gender gen)
{
  // temporary holder for given Gender
  // used to print out determined Gender
  std::string tempGen = "";

  // determines what Gender to print
  switch(gen)
  {
    case male:
      tempGen = "MALE";
      break;
    case female:
      tempGen = "FEMALE";
      break;
    case anyGender:
      tempGen = "undefined";
      break;
  }

  // Variable Declaratons
  // type double due to decimal results
  // set all to zero
  double numBabies =      0,
         alt_numBabies =  0,
         num2011 =        0,
         num2012 =        0,
         num2013 =        0,
         num2014 =        0,
         num2015 =        0,
         num2016 =        0,
         numAsian =       0,
         numBlack =       0,
         numHispanic =    0,
         numWhite =       0,
         perGender =      0,
         per2011 =        0,
         per2012 =        0,
         per2013 =        0,
         per2014 =        0,
         per2015 =        0,
         per2016 =        0,
         perAsian =       0,
         perBlack =       0,
         perHispanic =    0,
         perWhite =       0;
         
  // Variables to hold termporary data that will be generated
  int temp_year = 0;                    // used
  Gender temp_gen = anyGender;          // dummy
  Ethnicity temp_eth = anyEthnicity;    // used
  std::string temp_name = "";           // dummy
  int temp_count = 0;                   // used
  int temp_rank = 0;                    // dummy

  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byGender(babyList.at(i), gen);       // find match

    if(tempBool == true) 
    {
      babyList.at(i).get(temp_year, temp_gen, temp_eth, temp_name, temp_count, temp_rank);

      numBabies = numBabies + temp_count;         // extract and keep only count from match

      // extract year data and keep count according to year
      switch(temp_year)
      {
        case 2011:
          num2011 = num2011 + temp_count;
          break;
        case 2012:
          num2012 = num2012 + temp_count;
          break;
        case 2013:
          num2013 = num2013 + temp_count;
          break;
        case 2014:
          num2014 = num2014 + temp_count;
          break;
        case 2015:
          num2015 = num2015 + temp_count;
          break;
        case 2016:
          num2016 = num2016 + temp_count;
          break;
      }

      // extract the ethnicity data and keep count according to ethnicity
      switch(temp_eth)
      {
        case asian:
          numAsian = numAsian + temp_count;
          break;
        case black:
          numBlack = numBlack + temp_count;
          break;
        case hispanic:
          numHispanic = numHispanic + temp_count;
          break;
        case white:
          numWhite = numWhite + temp_count;
          break;
        case anyEthnicity:
          std::cout << "undefined" << std::endl;       // for unexpected wildcards
          break;
      }
    }

    // keep count of the # of babies that weren't a match to find %total match
    else if(tempBool == false) 
    {
      babyList.at(i).get(temp_year, temp_gen, temp_eth, temp_name, temp_count, temp_rank);

      alt_numBabies = alt_numBabies + temp_count;     // extract and keep only count
    }
  }

  // Calculations Section
  // (#Match/#Total)*100
  perGender = ((numBabies/(numBabies + alt_numBabies))*100);

  // (#Year/#Match)*100
  per2011 = ((num2011/numBabies)*100);
  per2012 = ((num2012/numBabies)*100);
  per2013 = ((num2013/numBabies)*100);
  per2014 = ((num2014/numBabies)*100);
  per2015 = ((num2015/numBabies)*100);
  per2016 = ((num2016/numBabies)*100);
  
  // (#Ethnicity/#Match)*100
  perAsian = ((numAsian/numBabies)*100);
  perBlack = ((numBlack/numBabies)*100);
  perHispanic = ((numHispanic/numBabies)*100);
  perWhite = ((numWhite/numBabies)*100);

  // Output Section
  // allows full number to show during repeated calls in the stats_allXYZ functions
  s << std::setprecision(6);

  // display the number of babies that were a match for the given Gender
  s << numBabies << "," << "" << "," << "babies were born" << "," << tempGen << std::endl;

  // display all values in decimal form to 4 sigfigs for percent values
  s << std::setprecision(4);

  // displaying the percent of given Gender babies from total babies
  s << perGender << "%" << "," << "" << "," << "babies were born" << "," << tempGen << std::endl;

  // displaying the percent ethnicities of the given Gender
  s << perAsian << "%" << "," << tempGen << "," << "babies were born" << "," << "ASIAN AND PACIFIC ISLANDER" << std::endl;
  s << perBlack << "%" << "," << tempGen << "," << "babies were born" << "," << "BLACK NON HISPANIC" << std::endl;
  s << perHispanic << "%" << "," << tempGen << "," << "babies were born" << "," << "HISPANIC" << std::endl;
  s << perWhite << "%" << "," << tempGen << "," << "babies were born" << "," << "WHITE NON HISPANIC" << std::endl;

  // displaying the percent years of the given Gender
  s << per2011 << "%" << "," << tempGen << "," << "babies were born in" << "," << "2011" << std::endl;
  s << per2012 << "%" << "," << tempGen << "," << "babies were born in" << "," << "2012" << std::endl;
  s << per2013 << "%" << "," << tempGen << "," << "babies were born in" << "," << "2013" << std::endl;
  s << per2014 << "%" << "," << tempGen << "," << "babies were born in" << "," << "2014" << std::endl;
  s << per2015 << "%" << "," << tempGen << "," << "babies were born in" << "," << "2015" << std::endl;
  s << per2016 << "%" << "," << tempGen << "," << "babies were born in" << "," << "2016" << std::endl << std::endl;
}


void Babycollection::stats_byEthnicity(std::ostream & s, const Ethnicity eth)
{
  // temporary holder for given Ethnicity
  // used to print out determined Ethnicity
  std::string tempEth = "";

  // determines what Ethnicity to print
  switch(eth)
  {
    case asian:
      tempEth = "ASIAN AND PACIFIC ISLANDER";
      break;
    case black:
      tempEth = "BLACK NON HISPANIC";
      break;
    case hispanic:
      tempEth = "HISPANIC";
      break;
    case white:
      tempEth = "WHITE NON HISPANIC";
      break;
    case anyEthnicity:
      tempEth = "undefined";
      break;
  }

  // Variable Declaratons
  // type double due to decimal results
  // set all to zero
  double numBabies =      0,
         alt_numBabies =  0,
         numMales =       0,
         numFemales =     0,
         num2011 =        0,
         num2012 =        0,
         num2013 =        0,
         num2014 =        0,
         num2015 =        0,
         num2016 =        0,
         perEth =         0,
         perMale =        0,
         perFemale =      0,
         per2011 =        0,
         per2012 =        0,
         per2013 =        0,
         per2014 =        0,
         per2015 =        0,
         per2016 =        0;
         
  // Variables to hold termporary data that will be generated
  int temp_year = 0;                    // used
  Gender temp_gen = anyGender;          // used
  Ethnicity temp_eth = anyEthnicity;    // dummy
  std::string temp_name = "";           // dummy
  int temp_count = 0;                   // used
  int temp_rank = 0;                    // dummy

  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byEthnicity(babyList.at(i), eth);      // find match

    if(tempBool == true) 
    {
      babyList.at(i).get(temp_year, temp_gen, temp_eth, temp_name, temp_count, temp_rank);

      numBabies = numBabies + temp_count;       // extract and keep only count from match

      // extract year data and keep count according to year
      switch(temp_year)
      {
        case 2011:
          num2011 = num2011 + temp_count;
          break;
        case 2012:
          num2012 = num2012 + temp_count;
          break;
        case 2013:
          num2013 = num2013 + temp_count;
          break;
        case 2014:
          num2014 = num2014 + temp_count;
          break;
        case 2015:
          num2015 = num2015 + temp_count;
          break;
        case 2016:
          num2016 = num2016 + temp_count;
          break;
      }

      // extract Gender data and keep count according to Gender
      switch(temp_gen)
      {
        case male:
          numMales = numMales + temp_count;
          break;
        case female:
          numFemales = numFemales + temp_count;
          break;
        case anyGender:
          std::cout << "undefined" << std::endl;      // for unexpected wildcards
          break;
      }
    }

    // keep count of the # of babies that weren't a match to find %total match
    else if(tempBool == false) 
    {
      babyList.at(i).get(temp_year, temp_gen, temp_eth, temp_name, temp_count, temp_rank);

      alt_numBabies = alt_numBabies + temp_count;     // extract and keep only count
    }
  }

  // Calculations Section
  // (#Match/#Total)*100
  perEth = ((numBabies/(numBabies + alt_numBabies))*100);

  // (#Gender/#Match)*100
  perMale = ((numMales/numBabies)*100);
  perFemale = ((numFemales/numBabies)*100);

  // (#Year/#Match)*100
  per2011 = ((num2011/numBabies)*100);
  per2012 = ((num2012/numBabies)*100);
  per2013 = ((num2013/numBabies)*100);
  per2014 = ((num2014/numBabies)*100);
  per2015 = ((num2015/numBabies)*100);
  per2016 = ((num2016/numBabies)*100);
  
  // Output Section
  // allows full number to show during repeated calls in the stats_allXYZ functions
  s << std::setprecision(6);

  // display the number of babies that were a match for the given Ethnicity
  s << numBabies << "," << "" << "," << "babies were born" << "," << tempEth << std::endl;

  // display all values in decimal form to 4 sigfigs for percent values
  s << std::setprecision(4);

  // displaying the percent of given Ethnicity babies from total babies
  s << perEth << "%" << "," << "" << "," << "babies were born" << "," << tempEth << std::endl;

  // displaying the percent genders of the given Ethnicity
  s << perMale << "%" << "," << tempEth << "," << "babies were born" << "," << "MALE" << std::endl;
  s << perFemale << "%" << "," << tempEth << "," << "babies were born" << "," << "FEMALE" << std::endl;

  // displaying the percent years of the given Ethnicity
  s << per2011 << "%" << "," << tempEth << "," << "babies were born in" << "," << "2011" << std::endl;
  s << per2012 << "%" << "," << tempEth << "," << "babies were born in" << "," << "2012" << std::endl;
  s << per2013 << "%" << "," << tempEth << "," << "babies were born in" << "," << "2013" << std::endl;
  s << per2014 << "%" << "," << tempEth << "," << "babies were born in" << "," << "2014" << std::endl;
  s << per2015 << "%" << "," << tempEth << "," << "babies were born in" << "," << "2015" << std::endl;
  s << per2016 << "%" << "," << tempEth << "," << "babies were born in" << "," << "2016" << std::endl << std::endl;
}


void Babycollection::stats_allYears(std::ostream & s)
{
  // calls the stats_byYear function for every year
  stats_byYear(s, 2011);    // provides year 2011
  stats_byYear(s, 2012);    // ...           2012
  stats_byYear(s, 2013);    // ...           2013
  stats_byYear(s, 2014);    // ...           2014
  stats_byYear(s, 2015);    // ...           2015
  stats_byYear(s, 2016);    // ...           2016
}


void Babycollection::stats_allGenders(std::ostream & s)
{
  // calls the stats_byGender function for every Gender
  stats_byGender(s, male);      // provides Gender male
  stats_byGender(s, female);    // ...             female
}


void Babycollection::stats_allEthnicities(std::ostream & s)
{
  // calls the stats_byEthnicity function for every Ethnicity
  stats_byEthnicity(s, asian);      // provides the Ethnicity asian
  stats_byEthnicity(s, black);      // ...                    black
  stats_byEthnicity(s, hispanic);   // ...                    hispanic
  stats_byEthnicity(s, white);      // ...                    white
}


void Babycollection::stats_All(std::ostream & s)
{
  // calls all stats_allXYZ functions
  stats_allYears(s);
  stats_allGenders(s);
  stats_allEthnicities(s);
}

/*******************************************************************************   
                        less_byXYZ friend Function Group
*******************************************************************************/
// Defined here such that it could be used by the std::sort() in the 
// <algorithm> library. Won't find the comparator functions elsewhere
// Count and Rank not used for first 4 functions in the logic because its irrelevant

// Comparator for determing how to sort by Year
bool less_byYear(const Babyname & lt, const Babyname & rt )
{
  // sort by YEAR of lt < YEAR of rt
  if (lt.Baby.birthYear < rt.Baby.birthYear) 
  {
    return true;
  }

  // or they are equal then sort by ETHNICITY of lt < ETHNICITY of rt
  else if ((lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity < rt.Baby.motherEthnicity)) 
  {
      return true;
  }

  // or they are equal then sort by GENDER of lt < GENDER of rt
  else if ((lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender < rt.Baby.babyGender)) 
  {
    return true;
  }

  // or they are equal then sort by NAME of lt < NAME of rt
  else if ((lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.babyName < rt.Baby.babyName)) 
  {
    return true;
  }

  return false; 
}

// Comparator for determing how to sort by Gender
bool less_byGender(const Babyname & lt, const Babyname & rt ) 
{
  // sort by GENDER of lt < GENDER of rt
  if (lt.Baby.babyGender < rt.Baby.babyGender) 
  {
    return true;
  }

  // or they are equal then sort by YEAR of lt < YEAR of rt
  else if ((lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.birthYear < rt.Baby.birthYear)) 
  {
      return true;
  }

  // or they are equal then sort by ETHNICITY of lt < ETHNICITY of rt
  else if ((lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity < rt.Baby.motherEthnicity)) 
  {
    return true;
  }

  // or they are equal then sort by NAME of lt < NAME of rt
  else if ((lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyName < rt.Baby.babyName))
  {
    return true;
  }

  return false;
}

// Comparator for determing how to sort by Ethnicity
bool less_byEthnicity(const Babyname & lt, const Babyname & rt ) 
{
  // sort by ETHNICITY of lt < ETHNICITY of rt
  if (lt.Baby.motherEthnicity < rt.Baby.motherEthnicity)
  {
    return true;
  }

  // or they are equal then sort by YEAR of lt < YEAR of rt
  else if ((lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.birthYear < rt.Baby.birthYear)) 
  {
      return true;
  }

  // or they are equal then sort by GENDER of lt < GENDER of rt
  else if ((lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.babyGender < rt.Baby.babyGender)) 
  {
    return true;
  }

  // or they are equal then sort by NAME of lt < NAME of rt
  else if ((lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.babyName < rt.Baby.babyName)) 
  {
    return true;
  }

  return false;
}

// Comparator for determing how to sort by Name
bool less_byName(const Babyname & lt, const Babyname & rt )
{
  // sort by NAME of lt < NAME of rt
  if (lt.Baby.babyName < rt.Baby.babyName) 
  {
    return true;
  }

  // or they are equal then sort by ETHNICITY of lt < ETHNICITY of rt
  else if ((lt.Baby.babyName == rt.Baby.babyName) && 
           (lt.Baby.motherEthnicity < rt.Baby.motherEthnicity)) 
  {
      return true;
  }

  // or they are equal then sort by GENDER of lt < GENDER of rt
  else if ((lt.Baby.babyName == rt.Baby.babyName) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender < rt.Baby.babyGender))
  {
    return true;
  }

  // or they are equal then sort by YEAR of lt < YEAR of rt
  else if ((lt.Baby.babyName == rt.Baby.babyName) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.birthYear < rt.Baby.birthYear))
  {
    return true;
  }

  return false; 
}

// Comparator for determing how to sort by Count
// Rank not used because its correlated with the Count
bool less_byCount(const Babyname & lt, const Babyname & rt ) 
{
  // sort by COUNT of lt < COUNT of rt
  if (lt.Baby.nameCount < rt.Baby.nameCount) 
  {
    return true;
  }

  // or they are equal then sort by YEAR of lt < YEAR of rt
  else if ((lt.Baby.nameCount == rt.Baby.nameCount) && 
           (lt.Baby.birthYear < rt.Baby.birthYear)) 
  {
      return true;
  }

  // or they are equal then sort by ETHNICITY of lt < ETHNICITY of rt
  else if ((lt.Baby.nameCount == rt.Baby.nameCount) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity < rt.Baby.motherEthnicity)) 
  {
    return true;
  }

  // or they are equal then sort by GENDER of lt < GENDER of rt
  else if ((lt.Baby.nameCount == rt.Baby.nameCount) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender < rt.Baby.babyGender)) {
    return true;
  }

  // or they are equal then sort by NAME of lt < NAME of rt
  else if ((lt.Baby.nameCount == rt.Baby.nameCount) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.babyName < rt.Baby.babyName)) 
  {
    return true;
  }

  return false;
}

// Comparator for determing how to sort by Rank
// Count not used because its correlated with the Rank
bool less_byRank(const Babyname & lt, const Babyname & rt ) 
{
  // sort by RANK of lt < RANK of rt
  if (lt.Baby.nameRank < rt.Baby.nameRank) 
  {
    return true;
  }

  // or they are equal then sort by YEAR of lt < YEAR of rt
  else if ((lt.Baby.nameRank == rt.Baby.nameRank) && 
           (lt.Baby.birthYear < rt.Baby.birthYear)) 
  {
      return true;
  }

  // or they are equal then sort by ETHNICITY of lt < ETHNICITY of rt
  else if ((lt.Baby.nameRank == rt.Baby.nameRank) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity < rt.Baby.motherEthnicity)) 
  {
    return true;
  }

  // or they are equal then sort by GENDER of lt < GENDER of rt
  else if ((lt.Baby.nameRank == rt.Baby.nameRank) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender < rt.Baby.babyGender)) 
  {
    return true;
  }

  // or they are equal then sort by NAME of lt < NAME of rt
  else if ((lt.Baby.nameRank == rt.Baby.nameRank) && 
           (lt.Baby.birthYear == rt.Baby.birthYear) && 
           (lt.Baby.motherEthnicity == rt.Baby.motherEthnicity) && 
           (lt.Baby.babyGender == rt.Baby.babyGender) && 
           (lt.Baby.babyName < rt.Baby.babyName)) 
  {
    return true;
  }

  return false;
}

/*******************************************************************************   
                          sort_byXYZ Function Group
*******************************************************************************/

void Babycollection::sort_byYear(std::ostream & s)
{ 
  // use sort() form the <algorithm> library on the vector
  // using the less_byYear comparator
  std::sort(babyList.begin(), babyList.end(), less_byYear);
  
  // print vector in order of year
  printVector(s, byYear);
}


void Babycollection::sort_byGender(std::ostream & s)
{
  // use sort() form the <algorithm> library on the vector
  // using the less_byGender comparator
  std::sort(babyList.begin(), babyList.end(), less_byGender);

  // print vector by order of Gender
  printVector(s, byGender);
}


void Babycollection::sort_byEthnicity(std::ostream & s)
{
  // use sort() form the <algorithm> library on the vector
  // using the less_byEthnicity comparator
  std::sort(babyList.begin(), babyList.end(), less_byEthnicity);

  // print vector by order of Ethnicity
  printVector(s, byEthnicity);
}


void Babycollection::sort_byName(std::ostream & s)
{
  // use sort() form the <algorithm> library on the vector
  // using the less_byName comparator
  std::sort(babyList.begin(), babyList.end(), less_byName);

  // print vector by order of Name
  printVector(s, byName);
}


void Babycollection::sort_byCount(std::ostream & s)
{
  // use sort() form the <algorithm> library on the vector
  // using the less_byCount comparator
  std::sort(babyList.begin(), babyList.end(), less_byCount);

  // print vector by order of Count
  printVector(s, byCount);
}


void Babycollection::sort_byRank(std::ostream & s)
{
  // use sort() form the <algorithm> library on the vector
  // using the less_byRank comparator
  std::sort(babyList.begin(), babyList.end(), less_byRank);

  // print vector by order of Rank
  printVector(s, byRank);
}

/*******************************************************************************   
                          search_byXYZ Function Group
*******************************************************************************/

void Babycollection::search_byYear(std::ostream & s, const int year)
{
  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byYear(babyList.at(i), year);    // find match

    if (tempBool == true) 
    {
      babyList.at(i).print(s, byDefault);   // print data in default order
    }
  }  
}


void Babycollection::search_byGender(std::ostream & s, const Gender gen)
{
  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byGender(babyList.at(i), gen);   // find match

    if (tempBool == true) 
    {
      babyList.at(i).print(s, byDefault);   // print data in default order
    }
  }  
}


void Babycollection::search_byEthnicity(std::ostream & s, const Ethnicity eth)
{
  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byEthnicity(babyList.at(i), eth);    // find match

    if (tempBool == true) 
    {
      babyList.at(i).print(s, byDefault);   // print data in default order
    }
  }  
}


void Babycollection::search_byName(std::ostream & s, const std::string name)
{
  // go through entire vector
  for(size_t i = 0; i < babyList.size(); i++)
  {
    tempBool = match_byName(babyList.at(i), name);      // find match

    if (tempBool == true) 
    {
      babyList.at(i).print(s, byDefault);   // print data in default order
    }
  } 
}