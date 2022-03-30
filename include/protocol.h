#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MSG_BUF_LEN 12
#define RX_START_CHAR 'S'
#define REPLY_START_CHAR 'R'
#define END_CHAR 'E'
#define BDCAST_CHAR '0'

//Message Buffer - Receive 6 bytes
// S NodeID Item Data1 Data2 E

#define PROT_POS_START 0
#define PROT_POS_NODEID 1
#define PROT_POS_ITEM 2
#define PROT_POS_DATA1 3
#define PROT_POS_DATA2 4
#define PROT_POS_END 5

//NodeID 1..9,A..Y  0=Broadcast

//Item 0..9
#define PROT_ITEM_LED1 '1'
#define PROT_ITEM_LED2 '2'
#define PROT_ITEM_RELAY '3'
#define PROT_ITEM_READ_TEMP '4'
#define PROT_ITEM_READ_SOIL '5'
#define PROT_ITEM_READ_STATUS '6'


#endif //__PROTOCOL_H