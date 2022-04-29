/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  2. Performs right shifts arithmetically and a negative shift value results in zero.
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


 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES, FOLLOW THE DIRECTIONS in README.md
 */


#endif
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return ~(~(x & ~ y) & ~(~ x & y));
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
    int word;
    word = 73;//Creates a word that is 01001001 in binary
    word = 9 | (word << 6);//Shifts the word 6 to the right and or's it with 9 to set the first 6 digits to the correct bits
    word = 9 | (word << 6);//Repeats so that all 32 bits are filled with the correct value
    word = 9 | (word << 6);
    word = 9 | (word << 6);
    return word;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  In general, a shift (left or right) by a negative number is undefined behavior.
 *  For this problem alone, you can assume that a left shift with a negative value is OK.
 *  and the resulting behavior is e.g. (0xf << -1 is 0). You may see an error raised
 *  at runt-time but you can ignore that error.
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
    int num;
    num = (!!n) << 31;//the double ! makes it so that if n contains any 1's then it returns 1 or 0, if n is all 0's, then shifts that over 31 to get 
    num = num >> (n+~0);//the correct value in the MSB. Then shifts the num back by n-1 because of the 1 possibly in the MSB.
    return num;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int nBitPos, mBitPos, nByte, mByte, mask, ans, bytes, nMask, mMask;
    nBitPos = n<<3;//Multiplies m and n by 8 to convert to bit positions
    mBitPos = m<<3;
    nMask = 0xff<<nBitPos;//Creates a mask of 1's in the first byte and shifts it over to the the n byte
    mMask = 0xff<<mBitPos;
    nByte = ((((nMask)&x)>>nBitPos)&0xff)<<mBitPos;//&'s the mask with x to get the nByte, shifts it back to the first byte, &'s it with the mask to 
    mByte = ((((mMask)&x)>>mBitPos)&0xff)<<nBitPos;//set everything else to 0's then shifts it into the m position
    mask = mMask|nMask;//Creates a mask of where the n and m bytes are and then ~'s it to get a mask of where the n and m bytes aren't
    mask = ~mask;
    ans = mask&x;//Gets the other 2 bytes of x
    ans = ans|mByte|nByte;//Or's all 3 together to combine it all
    return ans;
    
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    int num;
    num = x << 31;//Shifts the LSB into the MSB
    num = num >> 31;//Shifts the MSB all the way back, making the whole word the MSB
    return num;
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
    int num, num2;
    num2 = ((1<<n)+(~0));//Multiplies 1 by 2^n, then subtracts 1
    num = num2 & (x>>31);//If x is negagtive it will make num2 negative and if not it will make num 0
    num2 = (x+num)>>n;//Adds x and num together and then shifts by n to effectively divide by 2^n
    return num2;
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    return !(x^y);//XOR returns 0 when x and y are the same, so if you ! that you get 1 when x and y are the same
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
    int neg, num, msbX, msbY, msbXOR;
    neg = x + (~y+1);//Adds x and negative y, so that if they are the same, this will be 0 and 0 will be returned
    num = neg >> 31;
    msbX = x >>31;//Gets the MSB of x and y
    msbY = y >> 31;
    msbXOR = (msbX ^ msbY);//XOR's them together so that if they if they have different MSB's this will be 1
    num = !msbXOR&num;//Sets num equal to this so that if x and y are the same num will be 0 and 1 if not
    return num | (msbXOR & !msbY);//Or's num with this so if the MSB of y is 0 and x!=y then this will result in 1
}
/* 
 * rempwr2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) {
//x - (divpwr2(x, n) << n)
    int num, num2, num3;
    num2 = ((1<<n)+~0);
    num = num2 & (x>>31);
    num2 = (x+num)>>n;//First part is same as divpwr2
    num3 = num2 << n;//Shifts the num back by n to multiply by 2^n 
    num3 = x + (~num3+1);//Then subtracts that from x to get the remainder
    return num3;
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  return ((x+x)&~((x^(x+x)) >> 31))|(((x^(x+x)) >> 31)&((1 << 31) + ((x+x) >> 31)));
  //Up to OR: Checks if x overflowed and if so it saturates it to TMax
  //Next part: Checks if x overflowed in the other direction and saturates it to TMin
  //If x doesn't overflow then it doesn't get saturated
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return (((~x+1)|x)>>31&1)^1;//Or's x and negative x becasue if x is 0 then this will return 0 and if not it will have an MSB of 1. Shift that over 31 to get the MSB in the lSB. And it with 1 to get make it 1 or 0, then XOR it with 1 to make it 0 if x contains any 1's and 1 if not
}
/* reverseBits - reverse the bits in a 32-bit integer,
              i.e. b0 swaps with b31, b1 with b30, etc
 *  Examples: reverseBits(0x11111111) = 0x88888888
 *            reverseBits(0xdeadbeef) = 0xf77db57b
 *            reverseBits(0x88888888) = 0x11111111
 *            reverseBits(0)  = 0
 *            reverseBits(-1) = -1
 *            reverseBits(0x9) = 0x90000000
 *  Legal ops: ! ~ & ^ | + << >> and unsigned int type
 *  Max ops: 90
 *  Rating: 4
 */
int reverseBits(int x) {
unsigned int mask, ans;
ans = x;//Make x unsigned so that you can right shift it without filling with 0
ans = (ans<<16)|(ans>>16);//Swap the first half and the second half
mask = (255<<24)|(255<<8);//Create a mask so that you can swap the first and second quarter and the third and fourth quarter
ans = ((ans&mask)>>8)|((ans&~mask)<<8);//Then repeat until your swaping individual bits
mask = (15<<28)|(15<<20)|(15<<12)|(15<<4);
ans = ((ans&mask)>>4)|((ans&~mask)<<4);
mask = (204<<24)|(204<<16)|(204<<8)|204;
ans = ((ans&mask)>>2)|((ans&~mask)<<2);
mask = (170<<24)|(170<<16)|(170<<8)|170;
ans = ((ans&mask)>>1)|((ans&~mask)<<1);
return ans;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int mask, mask2, mask3, mask4, mask5;
    x = x | (x >> 1);//This section fills x with 1's up until the last one. EX: 010001 will turn into 011111
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    mask = (85<<24)|(85<<16)|(85<<8)|85;//Creates a mask where every other bit is a 1, starting with the LSB (01010101)
    mask2 = (51<<24)|(51<<16)|(51<<8)|51;//Creates a mask where every two bits are a 1, starting with the LSB (00110011)
    mask3 = (15<<24)|(15<<16)|(15<<8)|15;//Creates a mask where every four bits are a 1, starting with the LSB (00001111)
    mask4 = (255<<16)|255;//Creates a mask where every eight bits are a 1, starting with the LSB (11111111)
    mask5 = (255<<8)|255;//Creates a mask where every eight bits are a 1, starting with the LSB (11111111)
    x = (x & mask) + ((x >> 1) & mask);//Finds the bit position of the last 1 (1 closest to MSB)
    x = (x & mask2) + ((x >> 2) & mask2);//Shifts x and &'s it with the mask to see if there is a 1 somewhere in that set of bits
    x = (x & mask3) + ((x >> 4) & mask3);//Then adds that to x&mask to get bit position
    x = (x & mask4) + ((x >> 8) & mask4);
    x = (x & mask5) + ((x >> 16) & mask5);
    x = x + ~0;//Subtracts 1 because the log base 2 of a number equals the bit position of its last 1 minus 1
    return x; 
}
/*
 * Extra credit
 */
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
