#A bus monitoring tool used for debugging
#James Stockton
#01/04/2022


import sys, serial
from protocol import *


#program constants
BAUD = 9600



def decodeCommand(serialString):

    print(serialString)

    messageString = ""

    #print message type
    if(serialString[PROT_POS_START] == RX_START_CHAR):
        messageString = "Transmit:\n"
    elif(serialString[PROT_POS_START] == REPLY_START_CHAR):
        messageString = "Reply:\n"

    #node ID
    messageString += "Node ID: " + serialString[PROT_POS_NODEID] + "\n"

    #decode data for transmit
    if(serialString[PROT_POS_START] == RX_START_CHAR):

        if(serialString[PROT_POS_ITEM] == PROT_ITEM_LED1):
            messageString += "LED 1\n"
        
        elif(serialString[PROT_POS_ITEM] == PROT_ITEM_LED2):
            messageString += "LED 2\n"

        elif(serialString[PROT_POS_ITEM] == PROT_ITEM_RELAY):
            messageString += "Relay\n"

        #print remainding data
        messageString += "Data: "

        for s in serialString[3:]:

            if(s != END_CHAR):
                messageString += s + "\t"

    #decode data for reply
    elif(serialString[PROT_POS_START] == REPLY_START_CHAR):
        
        if(serialString[1] == 'A'):
            messageString += "Acknowledge"
        else:
            messageString += "Did not Acknowledge"

    messageString += "\n\n"

    print(messageString)


def handleSerial(serialDevice):

    serialDevice.baudrate = BAUD
    #serialDevice.open()

    serialDevice.flush()
    
    userExit = False
    midMessage = False
    buffer = ""

    while not userExit:

        buf = serialDevice.read(1).decode()

        if(buf in [RX_START_CHAR, REPLY_START_CHAR]):
            print("Start Message")
            buffer = ""
            buffer += buf

            midMessage = True
        
        elif(buf in [END_CHAR]):
            print("End Message")
            decodeCommand(buffer + buf)

            midMessage = False

        elif(midMessage):
            buffer += buf



        



if __name__ == "__main__":

    serialPort = sys.argv[1]

    with serial.Serial(serialPort, 9600, timeout=1) as ser:
        try:
            handleSerial(ser)
        except:
            print("Error")


    print("Serial Closed")
    ser.close()