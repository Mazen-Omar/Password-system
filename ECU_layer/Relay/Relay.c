/* 
 * File:   Relay.c
 * Author: Mr_Alsaied
 *
 * Created on 29 January, 2024, 08:14 PM
 */

#include "Relay.h"


/**
 * 
 * @param rly
 * @return 
 */
Std_ReturnType Relay_initialize(const Relay_t* rly)
{
    Std_ReturnType ret = E_OK;
    if(rly == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t obj = {.port = rly->relay_port, .pin = rly->relay_pin , 
                             .direction = GPIO_DIRECTION_OUTPUT, .logic = rly->relay_status};
        gpio_pin_initialize(&obj);
    }
    
    return ret;
}

/**
 * 
 * @param rly
 * @return 
 */
Std_ReturnType Relay_turn_on(const Relay_t* rly)
{
    Std_ReturnType ret = E_OK;
    if(rly == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        //SET_BIT(*(lat_registers[rly->relay_port]), rly->relay_pin);     //my way
        pin_config_t obj = {.port = rly->relay_port, .pin = rly->relay_pin , 
                             .direction = GPIO_DIRECTION_OUTPUT, .logic = rly->relay_status};
        gpio_pin_write_logic(&obj, GPIO_HIGH);
    }
    
    return ret;
}

/**
 * 
 * @param rly
 * @return 
 */
Std_ReturnType Relay_turn_off(const Relay_t* rly)
{
    Std_ReturnType ret = E_OK;
    if(rly == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
       // CLEAR_BIT(*lat_registers[rly->relay_port], rly->relay_pin);
        pin_config_t obj = {.port = rly->relay_port, .pin = rly->relay_pin , 
                             .direction = GPIO_DIRECTION_OUTPUT, .logic = rly->relay_status};
        gpio_pin_write_logic(&obj, GPIO_LOW);
        
    }
    
    return ret;
}


/**
 * 
 * @param rly
 * @return 
 */
Std_ReturnType Relay_toggle(const Relay_t* rly)
{
   Std_ReturnType ret = E_OK;
    if(rly == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(rly->relay_status)
        {
            case RELAY_ON_STATUS:
                Relay_turn_off(rly);
                break;
            case RELAY_OFF_STATUS:
                Relay_turn_on(rly);
                break;
            default : /* nothing */ break;    
        }
    }
    
    return ret;
}