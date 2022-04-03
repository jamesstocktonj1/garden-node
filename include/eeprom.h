#ifndef EEPROM_H
#define EEPROM_H

#include <avr/eeprom.h>

#define ID_POSITION 0
#define TYPE_POSITION 1
#define GROUP_POSITION 2


char eeprom_get_node_id(void);
char eeprom_get_node_type(void);
char eeprom_get_node_group(void);

#endif