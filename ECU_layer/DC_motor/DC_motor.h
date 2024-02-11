/* 
 * File:   DC_motor.h
 * Author: Mr_Alsaied
 *
 * Created on 01 January, 2024, 12:07 AM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

#include "../../MCAL_layer/GPIO/hal_gpio.h"

#define DC_MOTOR_ON_STATUS      0x01u
#define DC_MOTOR_OFF_STATUS     0x00u


typedef struct
{
    uint8 motor_port : 4;
    uint8 motor_pin  : 3;
    uint8 motor_status : 1;
}DC_motor_pin_t;

typedef struct 
{
    DC_motor_pin_t DC_motor[2];
}DC_motor_t;


Std_ReturnType dc_motor_intitialize(const DC_motor_t* motor);
Std_ReturnType dc_motor_move_right(const DC_motor_t* motor);
Std_ReturnType dc_motor_move_left(const DC_motor_t* motor);
Std_ReturnType dc_motor_stop(const DC_motor_t* motor);



#endif	/* DC_MOTOR_H */

