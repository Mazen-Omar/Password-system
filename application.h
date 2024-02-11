/* 
 * File:   application.h
 * Author: Mr_Alsaied
 *
 * Created on November 16, 2023, 12:24 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : includes  */
#include "ECU_layer/ecu_layer_init.h"

/* Section : Macro Declaration */
#define _LATC (HWREG8(0xF8B))
#define _TRISC (HWREG8(0xF94))
#define LATC_ADDR (0xF8B)


/* Section : Macro Functions Declaration */
#define HWREG8_ADDR(_x) ((volatile uint8_t *)(_x))
#define SET_BIT_BY_ADDR(REG ,POS) (*REG |= (1<<POS))
#define CLEAR_BIT_BY_ADDR(REG,POS) (*REG &= ~(1<<POS))
#define TOGGLE_BIT_BY_ADDR(REG,POS) (*REG ^= (1<<POS))

/* Section : Data Types Declaration */
extern keypad_t keypad;
extern lcd_4bit_t lcd;

/* Section : Function Declaration */
void application_initialize(void);

#endif	/* APPLICATION_H */

