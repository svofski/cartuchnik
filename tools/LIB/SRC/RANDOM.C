/*
 * Include some standard vectrex functions first!
 */
#include <vectrex.h>

/*
 * return a random (pseudo) character
 *
 * This may LOCK in the case another function is called with this
 * function as a parameter, AND that other function also requires
 * register A.
 * In that case you must assign a variable first!
 */
unsigned char random()
{
  get_random();         /* vectrex BIOS function */
  return __A;           /* pseudo register, declared in <vectrex.h> */
}
