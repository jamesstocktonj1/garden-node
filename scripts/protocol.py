#protocol definition
#James Stockton
#30/03/2022

#Constants taken from include/protocol.h
MSG_BUF_LEN = 12
RX_START_CHAR = 'S'
REPLY_START_CHAR = 'R'
REPLAY_ACK = 'A'
END_CHAR = 'E'
BDCAST_CHAR = '0'

#Message Buffer - Receive 6 bytes
# S NodeID Item Data1 Data2 E

PROT_POS_START = 0
PROT_POS_NODEID = 1
PROT_POS_ACK = 2
PROT_POS_ITEM = 2
PROT_POS_DATA1 = 3
PROT_POS_DATA2 = 4
PROT_POS_END = 5

#NodeID 1..9,A..Y  0=Broadcast

#Item 0..9
PROT_ITEM_LED1 = '1'
PROT_ITEM_LED2 = '2'
PROT_ITEM_RELAY = '3'
PROT_ITEM_READ_TEMP = '4'
PROT_ITEM_READ_SOIL = '5'
PROT_ITEM_READ_STATUS = '6'



commands = [
    "light",
    "relay",
    "temperature",
    "soil",
    "status"
]

def concatCommand(buffer, nodeID):

    data = "S"
    data += str(nodeID)

    for i in buffer:
        data += str(i)

    data += "E"
    data += "\n"

    return data