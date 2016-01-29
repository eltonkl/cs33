/* 
 * CS:APP Data Lab 
 * 
 * Elton Leong
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  //Make x positive, if x was -1 it is now 0
  int X = x ^ (x >> 31);
  //If X is 0, XExtended is all 0's, otherwise all 1's
  int XExtended = ((!!X) << 31) >> 31;
  int result = 0;
  //If X is larger than 2^16, then it needs a minimum of 2 + 16 bits in tc
  result = result + ((!!(X >> 16)) << 4);
  //If X / 2^(8 + result) is larger than 2^(8 + result), 
  //then it needs a minimum of 2 + 8 bits in tc
  result = result + ((!!(X >> (8 + result))) << 3);
  //So on and so forth..
  result = result + ((!!(X >> (4 + result))) << 2);
  result = result + ((!!(X >> (2 + result))) << 1);
  result = result + !!(X >> (1 + result));
  //Adding the other 2 bits mentioned above
  result = result + 2;
  //!X evaluates to 1 and (...) evaluates to 0, if the original x was 0 or -1
  return (result & XExtended) | !X;
}
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
  //sgn is all 0's if x is positive, or all 1's if negative
  int sgn = x >> 31;
  //Masking the sign bit
  int masked = x & ~(1 << 31);
  
  //(masked & ~sgn) evaluates to 0 if the number was negative in sm
  //((~masked + 1) & sgn) evaluates to 0 if the number was positive in sm
  return (masked & ~sgn) | ((~masked + 1) & sgn);
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  //If x is nonnegative, x >> 31 evaluates to 0, and !0 == 1
  //If x is negative, x >> 31 is sign-extended, evaluating to -1, and !(-1) == 0
  return !(x >> 31);
}
/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  //This solution isn't very elegant... but it works
  //If n is 0, nExtended is all 0's, otherwise all 1's
  int nExtended = ((!!n) << 31) >> 31;
  
  //For the sake of optimization, all subtractions had the +1 rolled into the
  //other constant, so 33 + ~n is equivalent to 32 - n
  //((33 + ~n) & nExtended) evaluates to (32 - n) if n != 0
  //Otherwise it evaluates to 0
  //This serves to guard against a (32 - 0) bit shift, which is undefined
  
  //lowBits is the emulation of a logical right shift
  //If n is 0, then (... | ~nExtended) evaluates to 0xffffffff
  //This prevents lowBits from being masked by the emulated logical right shift,
  //which otherwise functions correctly when n != 0
  int lowBits = (x >> n) & (~(~0 << ((33 + ~n) & nExtended)) | ~nExtended);
  
  int highBits = x << ((33 + ~n) & nExtended);
  //If n is 0, then zero out highBits
  highBits = highBits & nExtended;
  
  return highBits | lowBits;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  //If x is negative, sgn is all 1's, otherwise all 0's
  int sgn = x >> 31;
  //2^n - 1
  int bias = (1 << n) + ~0;
  //Adding bias biases the value of x towards 0 if x is negative
  //(sgn & bias) evaluates to 0 if x is positive, or 1 if x is negative
  return (x + (sgn & bias)) >> n;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  //Generating bitmask programmatically because only allowed to use 0-255
  int magic = 0xAA;
  magic = magic + (magic << 8);
  magic = magic + (magic << 16);
  //Masking to keep only the odd bits
  x = x & magic;
  //If all odd bits are turned on, then this becomes -1 + 1
  x = ~x + magic + 1;
  //!0 == 1
  return !x;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //(~x & y) is the 0's in x and the 1's in y
  //(~y & x) is the 1's in x and the 0's in y
  //The 1 bits in the two resulting strings need to be combined into one string
  //~(~x & y) turns on the bits that were the same in x and y or 1's in x and 
  //0's in y
  //~(y & x) turns on the bits that were the same in x and y or 0's in x and 
  //1's in y
  //&ing the previous two bit strings leaves on only the bits that were the same
  //in x and y, and then ~ing that leaves only the non-identical bits set to 1
  return ~(~(~x & y) & ~(~y & x));
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  //Tmin + Tmin equals 0, so the expression becomes 0 ^ 1
  return !x ^ !(x + x);
}
