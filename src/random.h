#ifndef RANDOM_H
#define RANDOM_H 1

/*** Constants Definition ***/
#define MULTIPLIER 16807
#define MODULUS    2147483647

/*** Methods Declaration ***/
void set_randomi(long);		/* initialize constants and seed                                 */
long randomi(long, long );	/* generate a random integer in the interval [a,b] (b >= a >= 0) */

#endif /* RANDOM_H */
