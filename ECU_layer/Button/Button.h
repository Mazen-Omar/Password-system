/* 
 * File:   Button.h
 * Author: Mr_Alsaied
 *
 * Created on 27 January 2024, 03:48 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/* Includes section */
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "Button_cnfg.h"

/* Macro declaration section */


/* Macro function declaration */


/* Data types declaration section */
typedef enum
{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED,
}Button_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH = 1,
    BUTTON_ACTIVE_LOW = 0,
}Button_active_t;

typedef struct
{
    pin_config_t    button;
    Button_state_t  state;
    Button_active_t active;
}Button_t;

/* Section : Functions declarations */
Std_ReturnType Button_initialize(const Button_t* obj);
Std_ReturnType Button_read(const Button_t* obj ,Button_state_t* state);


#endif	/* BUTTON_H */

