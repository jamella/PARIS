#include <stdio.h>
#include "keyMath.h"

/*
 * Print the number in hex.
 * Prints from Most Significant Int to Least Significant Int so that the MSB is
 * to the left.
 */
void printNumHex(uint32_t buf[NUM_INTS]){
   int i;
   for (i = 0; i < NUM_INTS; ++i) {
   /*for(i = NUM_INTS - 1; i >= 0; --i){*/
      printf("%08x ", buf[i]);
   }
   puts("");
}

/*
 * Print the number in binary
 */
void printNumBin(uint32_t buf[NUM_INTS]){
   int i;
   for (i = 0; i < NUM_INTS; ++i) {
   /*for(i = 0; i < NUM_INTS; i++){*/
      printByteBin(buf[i]);
      printf(" ");
   }
   puts("");
}


/*
 * Print an individual whichInt in binary.
 */
void printByteBin(uint32_t b){
   int i;
   for (i = 0; i < NUM_INTS; ++i) {
   /*for(i = 0; i < 32; i++){*/
      printf("%d", 0 == (b & (1 << i)) ? 0 : 1);
   }
}

/*
 * Shifts the passed number 1 to the right.
 */
void rightShift(uint32_t value[NUM_INTS]) {
   int whichInt, bitToShift, lastBitToShift = 0;

    for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) { 
   /*for (whichInt = NUM_INTS - 1; whichInt >= 0; --whichInt) {*/
      bitToShift = value[whichInt] & 1;
      value[whichInt] >>= 1;
      value[whichInt] |= lastBitToShift<<31;
      lastBitToShift = bitToShift;
   }
}

/*
 * Shifts the passed number 1 to the left.
 */
void leftShift(uint32_t value[NUM_INTS]) {
   int whichInt, bitToShift, lastBitToShift = 0;

    for (whichInt = NUM_INTS - 1; whichInt >= 0; --whichInt) {
   /*for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) {*/
      bitToShift = value[whichInt] & 0x80000000;
      value[whichInt] <<= 1;
      value[whichInt] |= lastBitToShift != 0;
      lastBitToShift = bitToShift;
   }
}

/*
 * ANDs the first and second numbers, and stores the result in the third.
 */
void AND(uint32_t u[NUM_INTS], uint32_t v[NUM_INTS], uint32_t w[NUM_INTS]) {
   int whichInt;

   for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) 
      w[whichInt] = u[whichInt] & v[whichInt]; 
}

/*
 * ORs the first two numbers, and stores the result in the third.
 */
void OR(uint32_t u[NUM_INTS], uint32_t v[NUM_INTS], uint32_t w[NUM_INTS]) {
   int whichInt;

   for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) 
      w[whichInt] = u[whichInt] | v[whichInt];
}

/*
 * Checks if the two numbers are equal. Use as if it were a normal = operator
 * Returns 1 if they are, 0 otherwise.
 */
int equalTo(uint32_t u[NUM_INTS], uint32_t v[NUM_INTS]) {
   int whichInt, equal = 1;

   for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) {
      if (u[whichInt] != v[whichInt]) {
         equal = 0;
         break;
      }
   }
   return equal;
}

/*
 * Checks if a nuber == 0.
 * Returns 1 if it is, 0 otherwise.
 */
int equalsZero(uint32_t v[NUM_INTS]) {
   int whichInt, equal = 1;

   for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) {
      if (v[whichInt] != 0) {
         equal = 0;
         break;
      }
   }
   return equal;
}

/*
 * Returns the lowest bit of the number.
 */
#define LSB(v) (v[NUM_INTS - 1] & 1)
/*#define LSB(v) (v[0] & 1)*/
/*
   int LSB(uint32_t v[NUM_INTS]) {
   return v[0] & 1;
   }
   */


/*
 * Assigns the second value to the first value. Like an = sign.
 */
void assign(uint32_t v[NUM_INTS], uint32_t u[NUM_INTS]) {
   int whichInt;

   for (whichInt = 0; whichInt < NUM_INTS; ++whichInt)
      v[whichInt] = u[whichInt]; 
}

/*
 * Finds if the first number is greater then the second.
 */
int greaterThan(uint32_t u[NUM_INTS], uint32_t v[NUM_INTS]) {
   int whichInt = 0;
   /*int whichInt = NUM_INTS - 1;*/

   while  (whichInt < NUM_INTS && u[whichInt] == v[whichInt]) 
      ++whichInt;
      /*--whichInt;*/

   return u[whichInt] > v[whichInt];
}

/*
 * Subtracts the second number from the first.
 */
void subtract(uint32_t u[NUM_INTS], uint32_t v[NUM_INTS], uint32_t w[NUM_INTS]) {
   int whichInt; 
   uint8_t carry = 0;
   uint32_t mask = 1<<(sizeof(int)*8 - 1), temp;
   uint8_t a, b;

   for (whichInt = NUM_INTS - 1; whichInt >= 0; --whichInt) {
   /*for (whichInt = 0; whichInt < NUM_INTS; ++whichInt) {*/
      a = (u[whichInt] & mask) != 0;
      b = (~v[whichInt] & mask) != 0;
      temp = ~v[whichInt] + u[whichInt] + (whichInt==(NUM_INTS-1)) + carry;
      /*temp = ~v[whichInt] + u[whichInt] + (whichInt==0) + carry;*/
      carry = (a & b) || ((a ^ b) & !(temp & mask));
      w[whichInt] = temp;
   }
}

void gcd1024(uint32_t u[NUM_INTS], uint32_t v[NUM_INTS], uint32_t w[NUM_INTS]) {
   /*
        printf("u\n");
        printNumHex(u);
        printf("\nv\n");
        printNumHex(v);
        printf("\nw\n");
        printNumHex(w);
        */
    int shift = 0;
    uint32_t temp[NUM_INTS];
    uint32_t t[NUM_INTS];

    /* GCD(0,x) := x */
    if (equalsZero(u) || equalsZero(v)) {
        OR(u, v, w);
        return;
    }

    /* Let shift := lg K, where K is the greatest power of 2
     *         dividing both u and v. */
    /* don't really need to OR the whole values...just check OR of LSB*/
    OR(u, v, temp);
    while (!LSB(temp)) {
       rightShift(u);
       rightShift(v);
       /* don't really need to OR the whole values...just check OR of LSB*/
       OR(u, v, temp);
       ++shift;
    }

    while (!LSB(u))
        rightShift(u);

    /* From here on, u is always odd. */
    do {
        while (!LSB(v))   /* Loop X */
            rightShift(v);

        if (greaterThan(u, v)) {
           assign(t, v);
           assign(v, u);
           assign(u, t);
        }  // Swap u and v.
        subtract(v, u, v);
    } while (!equalsZero(v));

    for (; shift > 0; --shift)
       leftShift(u);
    assign(w, u);
}
/*
 * This function adds two buffers together.
 * Returns the carry bit, or -1 on failure.
 */
//FIXME add a macro here for a 2 parameter vzn (writes to 1st or 2nd)
int bufAdd(bigNum_t* out, bigNum_t* u, bigNum_t* v){
   int i;

   if(!u || !v || !out || !out->b || !u->b || !v->b || out->len != v->len || v->len != u->len){
      return -1;
   }

   //might it be advantageous to do this in uint32_t's? use hardware math?
   int res = -1;
   out->b[0] = 0x00;
   for(i = 0; i < u->len - 1; i++){
      //do we just add each one, sub the result from 255, and add that?
      res = u->b[i] + v->b[i];
      out->b[i] += res & 0x00FF;
      u->b[i+1] = (res & 0xFF00) >> 8;
      printf("by no shift = 0x%04x\n", u->b[i+1]);
   }
   //do the last one manually (to check for overflow)
   printf("i was %d\n", i);
   res += u->b[i] + v->b[i];
   out->b[i] = res & 0x00FF;

   return (res & 0xFF00) >> 8;
}
