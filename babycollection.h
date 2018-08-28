/*******************************************************************************
  Title          : babycollection.h
  Author         : Orin Singh
  Created on     : August  21, 2018
  Description    : Interface to the Babycollection class
  Purpose        : To provide methods for storing and sorting baby names
  Build with     : Makefile (included)
  Modifications  : 

  Notes

*******************************************************************************/

#ifndef __BABYCOLLECTION_H__
#define __BABYCOLLECTION_H__


#include "babyname.h"     // for enumerated types specified there and etc.
#include <vector>         // will be using Vector to store Babynames


/*******************************************************************************   
                        Babycollection Class Interface
*******************************************************************************/


class Babycollection
{
public:
    /** Babycollection() - default constructor */
    Babycollection();

    /* addBaby() - adding method to babyname vector for the class
     *             assigns given values to the member variables
     *
     * @param int       indx      [in]   the index
     * @param ostream & s         [out]  the printed file
     * @param int       year      [in]   birth year 
     * @param Gender    gender    [in]   baby's gender 
     * @param Ethnicity ethnicity [in]   mother's ethnicity 
     * @param string    name      [in]   name of baby
     * @param int       count     [in]   frequency
     * @param int       rank      [in]   rank
     *
     * @pre   none
     * @post  object is assigned all valid values
     */
    void addBaby(int indx, 
                 std::ostream & s,
                 int year,
                 std::string gender,
                 std::string ethnicity,
                 std::string name,
                 int count,
                 int rank);


    /* 7 member functions that perform similar tasks;
     * stats_byYear() - method for calculating data for given year
     * by similar logic
     * stats_byXYZ() - method for calculating data for given XYZ
     * stats_allYears() - method for calculating data for all years
     * by similar logic
     * stats_allXYZ() - method for calculating data for all XYZ
     * stats_byYear() - method for calculating all data
     *
     * @param ostream & s         [out]  the printed file
     * @param int       year      [in]   birth year 
     * @param Gender    gender    [in]   baby's gender 
     * @param Ethnicity ethnicity [in]   mother's ethnicity 
     *
     * @pre   none
     * @post  All calculated stats are printed to file
     */
    void stats_byYear(std::ostream & s, const int year);
    void stats_byGender(std::ostream & s, const Gender gen);
    void stats_byEthnicity(std::ostream & s, const Ethnicity eth);
    void stats_allYears(std::ostream & s);
    void stats_allGenders(std::ostream & s);
    void stats_allEthnicities(std::ostream & s);
    void stats_All(std::ostream & s);
    

    /* 6 member functions that perform similar tasks;
     * sort_byYear() - method for sorting in order of year
     * by similar logic
     * sort_byXYZ() - method for sorting in order of XYZ
     *
     * @param ostream & s [out]  the printed file
     *
     * @pre   none
     * @post  babyList is sorted by XYZ
     */
    void sort_byYear(std::ostream & s);
    void sort_byGender(std::ostream & s);
    void sort_byEthnicity(std::ostream & s);
    void sort_byName(std::ostream & s);
    void sort_byCount(std::ostream & s);
    void sort_byRank(std::ostream & s);


    /* 4 member functions that perform similar tasks;
     * search_byYear() - method for searching for given year
     * by similar logic
     * search_byXYZ() - method for searching for given XYZ
     *
     * @param ostream & s         [out]  the printed file
     * @param int       year      [in]   birth year 
     * @param Gender    gender    [in]   baby's gender 
     * @param Ethnicity ethnicity [in]   mother's ethnicity 
     * @param string    name      [in]   name of baby
     *
     * @pre   none
     * @post  babies in babyList with XYZ is printed to file
     */
    void search_byYear(std::ostream & s, const int year);
    void search_byGender(std::ostream & s, const Gender gen);
    void search_byEthnicity(std::ostream & s, const Ethnicity eth);
    void search_byName(std::ostream & s, const std::string name);

    
private:
    /* convert_genderString() - method for taking input stream as string
     *                          and then using that to save to enum Gender types
     *
     * @param const string gen [in]  baby's gender
     *
     * @pre   none
     * @post  object is assigned enum Gender value
     */
    Gender convert_genderString(const std::string gen);


    /* convert_ethnicityString() - method for taking input stream as string
     *                             and then using that to save to enum Ethnicity types
     *
     * @param const string eth [in]  mother's ethnicity
     *
     * @pre   none
     * @post  object is assigned enum Ethnicity value
     */
    Ethnicity convert_ethnicityString(const std::string eth);


    /* printVector() - method for printing the entire babyList vector onto the 
     *                 given ostream assuming it is already open for writing, 
     *                 in the format specified 
     *
     * @param ostream s     [inout]  ostream opened for  writing
     * @param Data    recon [in]     order for  writing
     *
     * @pre   the object has valid data
     * @post  if the object has valid data, then it is written to ostream 
     *        in the specified format and the ostream is updated
     */
    void printVector(std::ostream & s, const Data recon);


    std::vector<Babyname> babyList;  // Vector of type Babyname
    Babyname tempBaby;               // Temporary Babyname Object for assignments

    // flags that will constantly be used in member functions
    bool tempBool;          // used for validation
    bool trip;              // used for validation
};

#endif /* __BABYCOLLECTION_H__ */