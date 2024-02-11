/* 
 * File:   keypad.h
 * Author: Mr_Alsaied
 *
 * Created on 04 February, 2024, 05:35 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include "keypad_cnfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"


#define KEYPAD_ROWS_NUMBER          4
#define KEYPAD_COLUMNS_NUMBER       4


typedef struct
{
    pin_config_t keypad_rows_pin[KEYPAD_ROWS_NUMBER];
    pin_config_t keypad_columns_pin[KEYPAD_COLUMNS_NUMBER];
}keypad_t;

Std_ReturnType keypad_initialize(const keypad_t* kpd);
Std_ReturnType keypad_get_value(const keypad_t* _keypad_obj, uint8* value);


#endif	/* KEYPAD_H */