/* 
 * File:   mcal_std_types.h
 * Author: Mr_Alsaied
 *
 * Created on November 15, 2023, 11:48 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/* Section : includes  */
#include "std_libraries.h"
#include "compiler.h"

/* Section : Data Types Declaration */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef char sint8;
typedef short sint16;
typedef int sint32;
typedef uint8 Std_ReturnType;

/* Section : Macro Declaration */
#define STD_ON                      0x01
#define STD_OFF                     0x00
#define STD_ACTIVE                  0x01
#define STD_IDLE                    0x00
#define E_OK (Std_ReturnType)       0x01
#define E_NOT_OK (Std_ReturnType)   0x00

/* Section : Macro Functions Declaration */


/* Section : Function Declaration */


#endif	/* MCAL_STD_TYPES_H */

