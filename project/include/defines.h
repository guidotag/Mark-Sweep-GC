/*
 * Defines and typedefs.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__

typedef enum bool{
	TRUE = 1, FALSE = 0
} bool;

typedef unsigned char uchar;
typedef unsigned int uint;

#define MAX_ADDR_LENGTH					16					/* Maximum length in hexa of a memory address */
#define DEFAULT_MARK_SWEEP				mark_sweep_fast		/* Mark-sweep function used when calling new */
#define MIN_ID							0					/* Minimum key used when building the address' dictionary */ 

#endif
