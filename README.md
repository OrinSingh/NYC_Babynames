# NYC_Babynames
**Program to analyze, sort and search NYC Baby-name data.**

The program has three primary functions; analysis, sorting and searching. Overarching these three primary functions is a simple text based user interface via the terminal console. The interface presents the user with the option of selecting the type of primary function they want to do. When selected, a subsequent interface based on what the user chose will appear. This will then present the user with sub-selections of the primary functions. Two of the primary functions (Statistical Analysis and Sort) will then further provide a new interface to further specify what the user wants to do. Then based on selection, the sub-functions of the given primary function will be called and the results will be placed in a newly created file named: results.csv in the current directory. The full breakdown can be found on my [website](https://orinsingh.com/nyc_babynames/).
[Dataset](https://data.cityofnewyork.us/Health/Popular-Baby-Names/25th-nujf) is from [NYC Open Data](https://opendata.cityofnewyork.us)

Dataset was last updated on August 17, 2018, according to the site.
As of current time(August 29, 2018), this dataset includes years 2011-2016.
Thus the current version of the program is meant to work with years 2011-2016.

**There are two ways to compile the program:**
1. Use the included [makefile](https://github.com/OrinSingh/NYC_Babynames/blob/master/Makefile) to compile the program in terminal by typing in: *make*
2. In the terminal type in: *g++ main.cpp babyname.cpp babycollection.cpp command.cpp -o output*

To run the program in the current directory, in the terminal type in: *./output*

**Note:** *allStats.csv, sort_byGender.csv and search_byEthnicity(Hispanic).csv* are all example files.
