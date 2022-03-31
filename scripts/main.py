#basic communication test script
#James Stockton
#30/03/2022


import sys, serial
from protocol import *


#program constants
BAUD = 9600





def handleSerial(serialDevice):

    serialDevice.baudrate = BAUD
    #serialDevice.open()

    serialDevice.flush()
    
    userExit = False

    while not userExit:
        cmd = input(">> ")
        cmd = cmd.split(" ")

        if cmd[0] in commands:
            buf = []
            
            if(cmd[0] == "light"):
                buf.append(int(cmd[1]))

                if(cmd[2] == "on"):
                    buf.append(1)
                else:
                    buf.append(0)

            elif(cmd[0] == "relay"):
                buf.append(3)
                
                if(cmd[1] == "on"):
                    buf.append(1)
                else:
                    buf.append(0)


            data = concatCommand(buf, 1)
            serialDevice.write(data.encode())

            print(data)

        elif cmd[0] in ["quit", "q"]:
            userExit = True

        else:
            print("Error: Unknown Command")

        #buf = serialDevice.readline().decode()
        #print(buf, end="")



if __name__ == "__main__":

    serialPort = sys.argv[1]

    with serial.Serial(serialPort, 9600, timeout=1) as ser:
        try:
            handleSerial(ser)
        except:
            print("Error")


    print("Serial Closed")
    ser.close()