#include "../include/eeprom.h"


char eeprom_get_node_id(void) {

    return (char)eeprom_read_byte((uint8_t *)ID_POSITION);
}

char eeprom_get_node_type(void) {

    return (char)eeprom_read_byte((uint8_t *)TYPE_POSITION);
}

char eeprom_get_node_group(void) {

    return (char)eeprom_read_byte((uint8_t *)GROUP_POSITION);
}