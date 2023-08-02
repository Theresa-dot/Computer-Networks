import random

WINDOW_SIZE = 4

def sendFrame(packet):
    print(f"Sending packet {packet}")

def receiveAck(packet):
    random_value = random.randint(0, 9)
    return random_value < 8

def main():
    totalFrames = int(input("Enter the total number of frames: "))
    ackReceived = [False] * totalFrames
    base = 0
    nextseqnum = 0

    while base < totalFrames:
        if base == totalFrames:
            print("All the frames have been transmitted successfully")
            break

        if nextseqnum < totalFrames and nextseqnum < base + WINDOW_SIZE:
            for i in range(nextseqnum, min(totalFrames, base + WINDOW_SIZE)):
                sendFrame(i)

            print("Waiting for acknowledgement")

            for i in range(nextseqnum, min(totalFrames, base + WINDOW_SIZE)):
                if receiveAck(i):
                    print(f"Packet {i} has been acknowledged")
                    ackReceived[i] = True
                    nextseqnum += 1
                else:
                    print(f"Packet {i} has been lost")

        if ackReceived[base]:
            print(f"Acknowledgement received for packet {base}")
            base += 1
        else:
            print(f"Acknowledgement not received for packet {base}, retransmitting")
            nextseqnum = base

if __name__ == "__main__":
    main()
