/***********************************************************************
 * Program:
 *    Lab Datalab
 *    Brother Jones, ECEN 324
 * Author:
 *    Colton Kopsa
 * Summary:
 *    descriptive text
 ***********************************************************************/

/*
 * CS:APP Data Lab
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *          Even though you may work as a team, all students should
 *          individually submit a solution.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
  {
    /* Team name: Replace with either:
       Your login ID (Linux Lab username) if working as a one person team
       or, ID1+ID2 where ID1 is the login ID of the first team member
       and ID2 is the login ID of the second team member.
       Example: joestudent+zmename */
    "kopsac+wkshumway",
    /* Student name 1: Replace with the name of first team member */
    "Colton Kopsa",
    /* Login ID 1: Replace with the login ID of first team member */
    "kopsac",

    /* The following should only be changed if there are two team members */
    /* Student name 2: Name of the second team member */
    "Wellesley Shumway",
    /* Login ID 2: Login ID of the second team member */
    "wkshumway"
  };


/*
 * STEP 3: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1

 0110
 0101
 1000
 */
int bitNor(int x, int y) {
  return ~x & ~y;
}
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 0100 1011
 0101 1010
 ---- ----
 0100 1010
 ---- ----
 1011 0101
 */
int bitXor(int x, int y) {
  return ~(x & y) & ~(~x & ~y);
}
/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 0101 0100
 0101 0101
 ---- ----
 0000 0001

 0101 1010
 0101 1010
 ---- ----
 0101 1010

 1111
 */
int isNotEqual(int x, int y) {
  return !!(x ^ y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return (x >> (8 * n)) & 0xFF;
}
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  return (x << 31) >> 31;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
1110111101
1111110111
0001111111
0001110111
1110000000
0001111111

 */
int logicalShift(int x, int n) {
  return (x >> n) & ~((1 << 31) >> n << 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 0111 = 7 = 3
 1110 = 14 = 3
 1011 = 11 = 3
 1101 = 13 = 3
 */
int bitCount(int x) {
  // 0000 0000 0000 0000 0000 0000 0000 0000
  // 0001 0001 0001 0001 0001 0001 0001 0001
  int mask = 0x11111111;
  int countMask = 0xF;
  int count = 0;
  int bitCount = 0;

  count = (x & mask) + count;
  x = x >> 1;
  count = (x & mask) + count;
  x = x >> 1;
  count = (x & mask) + count;
  x = x >> 1;
  count = (x & mask) + count;

  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);
  count = count >> 4;
  bitCount += (countMask & count);

  return bitCount;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 1101
 0010
 1111
 */
int bang(int x) {
  return (~(x | (~x + 1)) >> 31) & 1;
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4
 00110000
 11010000
 00010000
 */
int leastBitPos(int x) {
  return x & (~x + 1);
}
/*
 * TMax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1 << 31);
}
/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  return !(x >> 31);
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 if (x - y is positive)

 65 - 85 = -20
 5 - 6
 0101
 1010
 1111
 0001
 0000
 */
int isGreater(int x, int y) {
  return (x ^ y) >> 31 & 1;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 00010
 11111
 00001

 11111
 00001
 00001
 0011
 0000
 0000
 */
int divpwr2(int x, int n) {
  int mask = (1 << n) + ~0;
  int optionalOne = (x >> 31) & mask;
  return (optionalOne + x) >> n;
}
/*
 * abs - absolute value of x (except returns TMin for TMin)
 *   Example: abs(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 10110111
 11111111

 10110111
 01001001
 00000000
 01001001

 */
int abs(int x) {
  int negOne = x >> 31;
  return (x + (negOne & ((~x + 1) + (~x + 1))));
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 2147483647 < x + y
 -2147483648 > x + y
 0 0 0 = 1
 0 0 1 = 0
 0 1 0 = 1
 0 1 1 = 1
 1 0 0 = 1
 1 0 1 = 1
 1 1 0 = 0
 1 1 1 = 1
 */
int addOK(int x, int y) {
  int xSign = x >> 31 & 1;
  int ySign = y >> 31 & 1;
  int aSign = (x + y) >> 31 & 1;
  return (!xSign & !aSign) | (ySign & aSign) | (xSign & !ySign);
}
