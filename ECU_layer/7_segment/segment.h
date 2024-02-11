/* 
 * File:   segment.h
 * Author: Mr_Alsaied
 *
 * Created on 02 February, 2024, 08:45 PM
 */

#ifndef SEGMENT_H
#define	SEGMENT_H

#include "segment_cnfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct
{
    pin_config_t segment_pin[4];
    segment_type_t segment_type;
}segment_t;

Std_ReturnType segment_inititalize(const segment_t* seg);
Std_ReturnType segment_write_number(const segment_t* seg, uint8 number);



#endif	/* SEGMENT_H */

