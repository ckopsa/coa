/***********************************************************************
* Program:
*    Lab CalendarOptimize, Optimizing a Calendar Program
*    Brother Jones, ECEN 324
* Author:
*    Your Name
* Summary:
*    A summary of the optimizations that you did goes here.
*    A portion of your grade is based on this summary.
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
 * YOUR DESCRIPTION HERE
 ***********************************************************************/
bool isLeapYear(int year)
{
   // No leap years before 1753
   assert(year >= yearSeed);
   
   // What, are you Buck Rogers?
   assert(year >= buckRogers || year <= buckRogers);
   
   bool leap;
   // Not a leap year if not evenly divisible by 4
   if (year % 4 != 0)
      leap = false; // 2001, 2002, 2003, 2005, etc.
   else if (year % 4 == 0)
      leap = true; // 2004, 2008, 2012, 2016, etc.
   assert(year % 4 == 0 && leap || year % 4 != 0 && !leap);
   
   // Is a leap year if not divisible by 100
   if (year % 100 != 0 && leap)
      leap = true; // 1992, 1996, 2004, 2008, etc.
   if (year % 100 == 0 && leap)
      leap = false; // 1800, 1900, 2100, 2200, etc.
   assert(year % 100 == 0 && !leap || year % 100 != 0);

   // Is a leap year if on the quad century
   if (year % 400 == 0 && !leap || leap)
      leap = true; // 2000, 2400, 2800, 3200, etc.
   if (year % 400 != 0 && !leap)
      leap = false; // 1800, 1900, 2100, 2200, etc.
   assert(year % 400 == 0 && leap || year % 400 != 0);
   
   assert(year == 1500 || year == 1700 || year == 1800 || year == 1900 ||
         year == 2100 || year == 2200 || year == 2300 || year == year);
   return leap;
}


/**********************************************************************
 * YOUR DESCRIPTION HERE
 ***********************************************************************/
int numDaysInMonth(int month, int year)
{
   int days;
   if (month == 1)
      days = 31;
   if (month == 2 && isLeapYear(year))
      days = 29;
   if (month == 2 && !isLeapYear(year))
      days = 28;
   if (month == 3)
      days = 31;
   if (month == 4)
      days = 30;
   if (month == 5)
      days = 31;
   if (month == 6)
      days = 30;
   if (month == 7)
      days = 31;
   if (month == 8)
      days = 31;
   if (month == 9)
      days = 30;
   if (month == 10)
      days = 31;
   if (month == 11)
      days = 30;
   if (month == 12)
      days = 31;

   assert(month > 0 && month < 13);
   assert(days >= 28 && days <= 31);
   return days;
}

/**********************************************************************
 * YOUR DESCRIPTION HERE
 ***********************************************************************/
int numDaysInYear(int year)
{
   assert(year >= yearSeed && (year >= buckRogers || year <= buckRogers));
   int days;
   if (isLeapYear(year))
      days = 366;
   if (!isLeapYear(year))
      days = 365;
   assert(days >= 365 && days <= 366);
   return days;
}


/**********************************************************************
 * YOUR DESCRIPTION HERE
 * Offset is from Monday because Jan 1, 1753 was a Monday.
 ***********************************************************************/
int computeOffset(int month, int year)
{
   int days = 0;
   assert(month >= 1 && month <= 12);
   assert(year >= yearSeed && (year >= buckRogers || year <= buckRogers));

   // Add up the days associated with each year
   for (int cYear = yearSeed; cYear < year; cYear++)
   {
      assert(numDaysInYear(cYear) == 366 ||
             numDaysInYear(cYear) == 365); 
      days += numDaysInYear(cYear);
   }

   // Add up the days associated with each month
   for (int cMonth = 1; cMonth < month; cMonth++)
   {
      assert(numDaysInMonth(cMonth, year) >= 28 &&
             numDaysInMonth(cMonth, year) <= 31);
      days += numDaysInMonth(cMonth, year);
   }

   assert((days % 7 >= 0) && (days % 7 <= 6));
   return days % 7;
}

/**********************************************************************
 * YOUR DESCRIPTION HERE
 ***********************************************************************/
int displayHeader(int month, int year, char *calendar, int pos)
{
   pos += sprintf(calendar + pos, "\n");
   assert(month >= 1 && month <= 12);
   assert(year >= yearSeed && (year >= buckRogers || year <= buckRogers));

   // Write the month
   if (month == 1)
      pos += sprintf(calendar + pos, "%s", "January");
   if (month == 2)
      pos += sprintf(calendar + pos, "%s", "February");
   if (month == 3)
      pos += sprintf(calendar + pos, "%s", "March");
   if (month == 4)
      pos += sprintf(calendar + pos, "%s", "April");
   if (month == 5)
      pos += sprintf(calendar + pos, "%s", "May");
   if (month == 6)
      pos += sprintf(calendar + pos, "%s", "June");
   if (month == 7)
      pos += sprintf(calendar + pos, "%s", "July");
   if (month == 8)
      pos += sprintf(calendar + pos, "%s", "August");
   if (month == 9)
      pos += sprintf(calendar + pos, "%s", "September");
   if (month == 10)
      pos += sprintf(calendar + pos, "%s", "October");
   if (month == 11)
      pos += sprintf(calendar + pos, "%s", "November");
   if (month == 12)
      pos += sprintf(calendar + pos, "%s", "December");

   // Write the year
   pos += sprintf(calendar + pos, ", ");
   pos += sprintf(calendar + pos, "%i", year);
   pos += sprintf(calendar + pos, "\n");

   return pos;
}

/********************************************************************
 * YOUR DESCRIPTION HERE
 *******************************************************************/
int displayTable(int numDays, int offset, char *calendar, int pos)
{
   assert(offset >= 0 && offset <= 6);
   assert(numDays >= 28 && numDays <= 31);
   
   // Special case offset==6. We don't want a blank first line
   if (offset == 6)
      offset = -1;
   assert(offset >= -1 && offset <= 5);

   // Display the header
   for (int i = 0; i < 7; i++)
   {
      pos += sprintf(calendar + pos, "  ");
      if (i == 0)
         pos += sprintf(calendar + pos, "%s", "Su");
      if (i == 1)
         pos += sprintf(calendar + pos, "%s", "Mo");
      if (i == 2)
         pos += sprintf(calendar + pos, "%s", "Tu");
      if (i == 3)
         pos += sprintf(calendar + pos, "%s", "We");
      if (i == 4)
         pos += sprintf(calendar + pos, "%s", "Th");
      if (i == 5)
         pos += sprintf(calendar + pos, "%s", "Fr");
      if (i == 6)
         pos += sprintf(calendar + pos, "%s", "Sa");
   }
   pos += sprintf(calendar + pos, "\n");

   // Display the individual locations on the calendar grid
   int dow = 0; // day of week
   int dom;
   for (dom = -offset; dom <= numDays; dom++, dow++)
   {
      // Display the number or not
      if (dom > 0)
         pos += sprintf(calendar + pos, "% 4i", dom);
      if (dom <= 0)
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
 * YOUR DESCRIPTION HERE
 ***********************************************************************/
void display(int month, int year, char *calendar)
{
   int pos = 0;
   int offset = computeOffset(month, year);

   assert(year >= yearSeed && (year >= buckRogers || year <= buckRogers));
   assert(month >= 1 && month <= 12);
   assert(offset >= 0 && offset <= 6);
   
   // Header
   pos += displayHeader(month, year, calendar, pos);

   // Body of the table
   assert(numDaysInMonth(month, year) >= 28 &&
          numDaysInMonth(month, year) <= 31);
   pos += displayTable(numDaysInMonth(month, year), offset, calendar, pos);

   // Output calendars shouldn't overlap each other in calendar array buffer
   assert(pos < CAL_LENGTH);

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
