#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MSG_BUF_LEN 12
#define RX_START_CHAR 'S'
#define REPLY_START_CHAR 'R'
#define REPLAY_ACK 'A'
#define END_CHAR 'E'
#define BDCAST_CHAR '0'

//Message Buffer - Receive 6 bytes
// S NodeID Item Data1 Data2 E

#define PROT_POS_START 0
#define PROT_POS_NODEID 1
#define PROT_POS_ACK 2
#define PROT_POS_ITEM 2
#define PROT_POS_DATA1 3
#define PROT_POS_DATA2 4
#define PROT_POS_END 5

//NodeID 1..9,A..Y  0=Broadcast

//Item 0..9
#define PROT_ITEM_LED1 '1'
#define PROT_ITEM_LED2 '2'
#define PROT_ITEM_RELAY1 '3'
#define PROT_ITEM_RELAY2 '4'
#define PROT_ITEM_READ_TEMP '5'
#define PROT_ITEM_READ_SOIL '6'
#define PROT_ITEM_READ_STATUS '7'

//Node Zone Definition
#define NODE_ZONE_UNDEFINED '0'
#define NODE_ZONE_GREENHOUSE '1'
#define NODE_ZONE_VEG_PLOT_1 '2'
#define NODE_ZONE_VEG_PLOT_2 '3'
#define NODE_ZONE_PLANTER_1 '4'
#define NODE_ZONE_PLANTER_2 '5'

//Node Definitions
#define NODE_DEF_UNDEFINED '0'
#define NODE_DEF_WATER '1'
#define NODE_DEF_LIGHTS '2'

typedef struct MyInfo_t
{
    char My_Node_Num;
    char My_Zone;
    char My_Node_Def;
} MyInfo;


#endif //__PROTOCOL_H