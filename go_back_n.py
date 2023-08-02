def sendPacket(packet):
    print(f"Sending packet {packet}")

def receivedAck(packet):
    if packet == 2 or packet == 5:
        return False
    return True

def main():
    totalPackets = int(input("Enter total number of packets: "))
    windowSize = int(input("Enter Window Size: "))

    base = 0
    nextseqNum = 0

    while base < totalPackets:
        if base == totalPackets:
            print("All the packets have been transmitted successfully")
            break

        if nextseqNum < totalPackets and nextseqNum < base + windowSize:
            for i in range(base, base + windowSize):
                if i < totalPackets:
                    sendPacket(i)

            print("Waiting for acknowledgement")

            for i in range(base, base + windowSize):
                if i < totalPackets:
                    if receivedAck(i):
                        print(f"Packet {i} has been acknowledged")
                        nextseqNum += 1
                    else:
                        print(f"Packet {i} lost, retransmitting")

        if nextseqNum >= base + windowSize:
            print("Waiting for acknowledgements")

            for i in range(base, base + windowSize):
                if i < totalPackets:
                    if receivedAck(i):
                        print(f"Packet {i} has been acknowledged")
                        base += 1
                    else:
                        print(f"Acknowledgement for packet {i} lost, retransmitting..")

if __name__ == "__main__":
    main()
