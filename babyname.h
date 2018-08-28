/*******************************************************************************
  Title          : babyname.h
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Interface to the Babyname class
  Purpose        : To provide methods for processing baby names
  Build with     : Makefile (included)
  Modifications  : 

  Notes

  This header file provides the interface to the Babyname class, as well as to
  a few types that are required in order to use this class, specifically the 
  following enumerated types:
                              Gender
                              Ethnicity
                              Data
  

  friend bool less_byYear(const Babyname & lt, const Babyname & rt );
  friend bool less_byGender(const Babyname & lt, const Babyname & rt );
  friend bool less_byEthnicity(const Babyname & lt, const Babyname & rt );
  friend bool less_byName(const Babyname & lt, const Babyname & rt );
  friend bool less_byCount(const Babyname & lt, const Babyname & rt );
  friend bool less_byRank(const Babyname & lt, const Babyname & rt );

  are defined in "babycollection.cpp" under "less_byXYZ friend Function Group"
*******************************************************************************/

#ifndef __BABYNAME_H__
#define __BABYNAME_H__

#include <iostream>     // for basic input/output functions
#include <string>       // for use of the "string" object type


/*******************************************************************************   
                                 Exported Types
*******************************************************************************/

/** Gender
    This is an enumerated type to represent two possible genders plus a 
    wildcard value named "any" that means either gender.
*/
typedef enum
{
    male = 0,
    female,
    anyGender
} Gender;

/** Ethnicity
    This represents the different ethnic groups that might be associated to an
    individual name in the dataset. The wildcard "any" represents any ethnic
    group.
*/
typedef enum
{
    asian = 0,
    black,
    hispanic,
    white,
    anyEthnicity
} Ethnicity;

/** Data
    This represents the different printing orders that will be associated to
    specific sorting functions for the dataset. No wildcard as this is 
    programmer controlled.
*/
typedef enum
{
    byDefault = 0,
    byYear,
    byGender,
    byEthnicity,
    byName,
    byCount,
    byRank
} Data;


/*******************************************************************************   
                              Babyname Class Interface
*******************************************************************************/

class Babyname
{
public:
    /** Babyname() - default constructor */
    Babyname();
 
    /* set() - set method for the class
     *         assigns given values to the member variables, while validating values.
     *         Method ensures that all parameters are within the allowed ranges
     *
     * @param int       year      [in]  birth year 
     * @param Gender    gender    [in]  baby's gender 
     * @param Ethnicity ethnicity [in]  mother's ethnicity 
     * @param string    name      [in]  name of baby
     * @param int       count     [in]  frequency
     * @param int       rank      [in]  rank
     *
     * @pre   none
     * @post  object is assigned all valid values
     * @return bool    true if all values were set successfully; false otherwise
     */
    bool set( int          year, 
              Gender       gender, 
              Ethnicity    ethnicity,
              std::string  name,
              int          count,
              int          rank
            );


    /* get() - get method for the class
     *         retrieves values of the member variables, and passes to corresponding
     *         parameters.
     *
     * @param int       year      [out]  birth year 
     * @param Gender    gender    [out]  baby's gender 
     * @param Ethnicity ethnicity [out]  mother's ethnicity 
     * @param string    name      [out]  name of baby
     * @param int       count     [out]  frequency
     * @param int       rank      [out]  rank
     *
     * @pre   none
     * @post  object is assigned all valid values
     */
    void get( int          &  year, 
              Gender       &  gender, 
              Ethnicity    &  ethnicity,
              std::string  &  name,
              int          &  count,
              int          &  rank
            );


    /* print() - prints the baby name data onto the given ostream 
     *           assuming it is already open for writing, in the format specified 
     *
     * @param ostream s           [inout]  ostream opened for  writing
     * @param Data    reconfigure [in]     order for  writing
     *
     * @pre   the object has valid data
     * @post  if the object has valid data, then it is written to ostream 
     *        in the specified format and the ostream is updated
     */
    void print (std::ostream & s, const Data reconfigure);


    /* isRepeat() - verifies that the current line of input is not a 
     *              repeat (repeated baby)
     *
     * @param Babyname & lt [in]  old babies being checked
     * @param Babyname & rt [in]  new baby being checked
     *
     * @pre   there is at least one baby
     * @post  if the baby is already in the vector, return true
     *        else return false
     */
    friend bool isRepeat(const Babyname & lt, const Babyname & rt);


    /* 4 friend functions that perform similar tasks;
     * Each is given one Babyname object by constant reference and
     * a different baby attribute to match by
     * returns true or false depending on whether a match was
     * found with the input attribute
     *
     * match_byYear(lt, rt) is true if and only if:
     *    the referenced baby met the given attribute (year)
     * match_byXYZ ( lt, Gender/Ethnicity/name) has the similar logic 
     *    except in the attribute it checks for (Gender/Ethnicity/name)
     *
     * @param Babyname  & lt   [in]  baby being checked
     * @param int         year [in]  what year to check for
     * @param Gender      gen  [in]  what Gender to check for
     * @param Ethnicity   eth  [in]  what Ethnicity to check for
     * @param std::string gen  [in]  what name to check for
     *
     * @pre   there is at least one baby in the vector
     * @post  if the baby is matched in the vector, return true
     *        else return false
     */
    friend bool match_byYear(const Babyname & lt, const int year);
    friend bool match_byGender(const Babyname & lt, const Gender gen);
    friend bool match_byEthnicity(const Babyname & lt, const Ethnicity eth);
    friend bool match_byName(const Babyname & lt, const std::string name);


    /* 6 friend functions that perform similar tasks;
     * Each is given two Babyname objects by constant reference and
     * returns true or false depending on whether one is less than or equal to
     * the other. 
     *
     * less_byYear(lt, rt) is true if and only if: 
     *    birth year of lt < birth year of rt 
     *     or they are equal and ethnicity of lt < ethnicity of rt, 
     *     or they are equal and gender of lt < gender of rt, 
     *     or they are equal and name of lt < name of rt.
     * less_byXYZ ( lt, rt) has the similar logic except in the
     *     order it ranks by.
     *
     * @param Babyname & lt [in]  baby being checked
     * @param Babyname & rt [in]  baby being checked against
     *
     * @pre   two valid babies
     * @post  if the baby is less in the vector, return true
     *        else return false
     */
    friend bool less_byYear(const Babyname & lt, const Babyname & rt );
    friend bool less_byGender(const Babyname & lt, const Babyname & rt );
    friend bool less_byEthnicity(const Babyname & lt, const Babyname & rt );
    friend bool less_byName(const Babyname & lt, const Babyname & rt );
    friend bool less_byCount(const Babyname & lt, const Babyname & rt );
    friend bool less_byRank(const Babyname & lt, const Babyname & rt );
   

private:
  // Struct with attributes that a "BABY" must contain
  // local and never used anywhere else
  struct
  {
    int          birthYear;        // 2011 through 2014
    Gender       babyGender;       // male or female
    Ethnicity    motherEthnicity;  // asian, black, hispanic, or white
    std::string  babyName;         // any valid string
    int          nameCount;        // >= 0
    int          nameRank;         // > 0
  } Baby;
};


#endif /* __BABYNAME_H__ */