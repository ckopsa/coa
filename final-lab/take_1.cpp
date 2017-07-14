/***********************************************************************
* Program:
*    Lab CalendarOptimize, Optimizing a Calendar Program
*    Brother Jones, ECEN 324
* Author:
*    Colton Kopsa
* Summary:
*    Optimizations:
*    - Streamlined isLeapYear logic 
*    - Replaced chained if statements with arrays where applicable
*    - Combined print statements to lower function call amount
*    - Removed function call to numDaysInYear and handled calculation in line
*    
*    Final Results:
*    USER/FILE: take_1
*     -clocked at:  253.30ms
*      -correctness: 100.0%
*      OPTIMIZED:
*       -clocked at:  159.53ms
*        -correctness: 100.0%
*
* Notes:
*    - Your goal is to optimize this program to minimize the run time.
*
*    - Copy this file to a directory you wish to work in:
*        cd ~/someDirectoryYouCreated
*        cp /home/ecen324/calendarOptimize/starter.cpp .
*
*    - You can do pretty much anything with the code you want, as
*      long as it is contained within this file and obeys the following
*      rules:.
*      - Have:  #include "/home/ecen324/calendarOptimize/lab_consts.h"
*      - Use "pos += sprintf(calendar + pos, ..., ...)" for outputting the
*        calendars. You can change how and when your code writes to the
*        output, but you MUST use something of this form in order for the
*        lab to compile with the testing program provided (testCalOpt).
*      - You MUST have "void make_calendars(int[], int[], char*);" defined
*        in this file for your code to compile for the lab.
*      - If you want your program to be compiled with any special compiler
*        options when tested, you must include the line found below this
*        header that says:
*           This code is to be compiled with: CAL_COMPILE_OPT=" ... "
*        You will change what is between the " " to have your desired options.
*
*    - Month numbers are 1-12
*    - Years numbers are >= 1753
*
*    - You test your optimizations by doing:
*         /home/ecen324/calendarOptimize/testCalOpt
*      This tests all of the *.cpp files in current directory.
*      or if you want to add options to the g++ compile of your code:
*         CAL_COMPILE_OPT="-Opt1 -Opt2 ..." /home/ecen324/calendarOptimize/testCalOpt -o
*      To see more options for the test program execute:
*         /home/ecen324/calendarOptimize/testCalOpt -h
*
*    - Submit your fastest code using the "submit" command.  The code will
*      fail to compile, but that is OK.
*
************************************************************************/

/***********************************************************************
 * This code is to be compiled with: CAL_COMPILE_OPT=" ... "
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cassert>

// Get lab specific variables --You must include this #include--
#include "/home/ecen324/calendarOptimize/lab_consts.h"

using namespace std;

// The year the current calendar began to be valid
#define yearSeed 1753
// Just for kicks and giggles
#define buckRogers 2200

/**********************************************************************
 * Determines if leap year from year
 * Code from: https://stackoverflow.com/questions/3220163/how-to-find-leap-year-programatically-in-c
 ***********************************************************************/
bool isLeapYear(int year)
{
  if ((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0))
    {
      return true;
    }
  return false;
}


/**********************************************************************
 * Calculates number of days in month given month and year
 ***********************************************************************/
int numDaysInMonth(int month, int year, bool leapYear)
{
  int days[] = {
    0,  // skip first slot
    31, // 1
    28, // 2
    31, // 3
    30, // 4
    31, // 5
    30, // 6
    31, // 7
    31, // 8
    30, // 9
    31, // 10
    30, // 11
    31  // 12
  };
	if (leapYear)
    return 29;
  else
    return days[month];
}

/**********************************************************************
 * Coomputes offset given month and year
 * Offset is from Monday because Jan 1, 1753 was a Monday.
 ***********************************************************************/
int computeOffset(int month, int year)
{
  int days = 0;
  bool leapYear;

  // Add up the days associated with each year
  for (int cYear = yearSeed; cYear < year; cYear++)
    {
      days += isLeapYear(cYear) ? 366 : 365;
    }

  // Add up the days associated with each month
  for (int cMonth = 1; cMonth < month; cMonth++)
    {
      leapYear = isLeapYear(year);
      days += numDaysInMonth(cMonth, year, leapYear);
    }

  return days % 7;
}

/**********************************************************************
 * Displays month header
 ***********************************************************************/
int displayHeader(int month, int year, char *calendar, int pos)
{
  const char * months[] = {
    "",          // skip first slot
    "January",   // 1
    "February",  // 2
    "March",     // 3
    "April",     // 4
    "May",       // 5
    "June",      // 6
    "July",      // 7
    "August",    // 8
    "September", // 9
    "October",   // 10
    "November",  // 11
    "December"   // 12
  };
  // Write the month and year
  pos += sprintf(calendar + pos, "\n%s, %i\n", months[month], year);
  return pos;
}

/********************************************************************
 * Displays table following header
 *******************************************************************/
int displayTable(int numDays, int offset, char *calendar, int pos)
{
  // Special case offset==6. We don't want a blank first line
  if (offset == 6)
    offset = -1;

  pos += sprintf(calendar + pos, "  Su  Mo  Tu  We  Th  Fr  Sa\n");

  // Display the individual locations on the calendar grid
  int dow = 0; // day of week
  int dom;
  for (dom = -offset; dom <= numDays; dom++, dow++)
    {
      // Display the number or not
      if (dom > 0)
        pos += sprintf(calendar + pos, "% 4i", dom);
      else
        pos += sprintf(calendar + pos, "    ");

      // Display the end-of-row marker
      if (dow % 7 == 6)
        pos += sprintf(calendar + pos, "\n");
    }

  // Extra ENDL as necessary
  if (dow % 7 != 0)
    pos += sprintf(calendar + pos, "\n");

  return pos;
}


/**********************************************************************
 * Displays header and table
 ***********************************************************************/
void display(int month, int year, char *calendar)
{
  int pos = 0;
  int offset = computeOffset(month, year);
  bool leapYear = isLeapYear(year);

  // Header
  pos += displayHeader(month, year, calendar, pos);

  // Body of the table
  pos += displayTable(numDaysInMonth(month, year, leapYear), offset, calendar, pos);

  return;
}


/**********************************************************************
 * YOU MUST HAVE THIS FUNCTION SIGNATURE DEFINED TO COMPILE YOUR CODE
 * This is used by the driver to test your optimizations
 ***********************************************************************/
void make_calendars(int months[], int years[], char *calendars)
{
  for (int i = 0; i < NUM_CALS; i++)
    display(months[i], years[i], calendars + i * CAL_LENGTH);
}
