/* 
 * File:   Relay.h
 * Author: Mr_Alsaied
 *
 * Created on 29 January, 2024, 08:14 PM
 */

#ifndef RELAY_H
#define	RELAY_H

#include "Relay_cnfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

#define RELAY_ON_STATUS 0X01U
#define RELAY_OFF_STATUS 0X00U

typedef struct
{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}Relay_t;


Std_ReturnType Relay_initialize(const Relay_t* rly);
Std_ReturnType Relay_turn_on(const Relay_t* rly);
Std_ReturnType Relay_turn_off(const Relay_t* rly);
Std_ReturnType Relay_toggle(const Relay_t* rly);

#endif	/* RELAY_H */

