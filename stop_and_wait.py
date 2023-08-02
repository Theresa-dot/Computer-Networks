import time
import random

def sender(message):
    print("Sender : Sending Message : ",message)
    time.sleep(1)
    return random.choice([True,False])

def receiver():
    print("Receiver : Waiting for meassage")
    time.sleep(2)
    print("Receiver: Message Received")

def stop_and_wait_protocol(message):
    while True:
        sent_packet = sender(message)
        if sent_packet:
            receiver_ip = input("Receiver acknowledgement received ?[Y/N]")
            if receiver_ip == 'Y':
                break
            else:
                print("Packet lost. Resending")

message = "Hello"
stop_and_wait_protocol(message)
