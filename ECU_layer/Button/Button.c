/* 
 * File:   Button.c
 * Author: Mr_Alsaied
 *
 * Created on 27 January 2024, 03:48 AM
 */

#include "Button.h"


/**
 * @brief Initializing the button direction which is GPIO_DIRECTION_INPUT
 * @param btn from Button_t type
 * @return the status of the function
 */
Std_ReturnType Button_initialize(const Button_t* btn)
{
    Std_ReturnType ret = E_NOT_OK;
    if(btn == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_initialize(&btn->button);
        ret = E_OK;
    }
    return ret;
}


/**
 * @brief reading the logic on the button
 * @param btn , _st
 * @return the status of the function
 * @return the state of the button in _st pointer
 */ 
Std_ReturnType Button_read(const Button_t* btn ,Button_state_t* _st)
{
    Std_ReturnType ret = E_NOT_OK;
    logic_t button_logic = GPIO_LOW;
    if(btn == NULL || _st == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_read_logic(&(btn->button) ,&button_logic);
        if(btn->active == BUTTON_ACTIVE_HIGH)
        {
            if(button_logic == GPIO_LOW)
            {
                *_st = BUTTON_RELEASED;
            }
            else
            {
                *_st = BUTTON_PRESSED;
            }
        }
        else if(btn->active == BUTTON_ACTIVE_LOW)
        {
            if(button_logic == GPIO_LOW)
            {
                *_st = BUTTON_PRESSED;     
            }
            else
            {
                *_st = BUTTON_RELEASED;
            }
        }
        else
        {
            /* Nothing */
        }
        ret = E_OK;
    }
    return ret;
}
