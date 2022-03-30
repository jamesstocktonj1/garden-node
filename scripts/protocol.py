#protocol definition
#James Stockton
#30/03/2022



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