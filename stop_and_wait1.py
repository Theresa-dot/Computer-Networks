import random

def sendPacket(packet):
    print(f"Sending packet {packet}")

def receveAck():
    random_value = random.randint(0, 9)
    return random_value < 7

def main():
    totalPackets = int(input("Enter the total number of packets: "))
    packetCount = int(input("Enter the packet count: "))

    while packetCount < totalPackets:
        if packetCount == totalPackets:
            print("All the packets have been transmitted successfully")
            break

        sendPacket(packetCount)
        print("Waiting for acknowledgement")

        if not receveAck():
            print(f"Packet {packetCount} has been lost, retransmitting...")
            continue

        print(f"Packet {packetCount} has been acknowledged")

        if not receveAck():
            print("Acknowledgement lost, retransmitting...")
            continue

        packetCount += 1

if __name__ == "__main__":
    main()
