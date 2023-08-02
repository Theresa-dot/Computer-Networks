def validify_ip(ip):
    segment=ip.split('.');
    if len(segment)!=4:
        return False;
    for s in segment:
        if not s.isdigit() or int(s)<0 or int(s)>255: 
            return False
    return True

def to_binary(segment):
    try:
        num=int(segment)
        if num<0 or num>255:
            return "Invalid format"
        binary=bin(num)[2:].zfill(8)
        return binary
    except ValueError:
        return "Invalid format"

def to_dotted_decimal(segment):
    try:
        num=int(segment,2)
        if num<0 or num>255:
            return "Invalid format"
        return str(num)
    except ValueError:
        return "Invalid format"
        
def classify_ip(ip):
    segment=ip.split(".")
    if not validify_ip(ip):
        print("Not valid")
        return
    first_octet=segment[0];
    if 0<=int(first_octet)<=127:
        print("Class A")
    elif 128<=int(first_octet)<=191:
        print("Class B")
    elif 192<=int(first_octet)<=223:
        print("Class C")
    elif 224<=int(first_octet)<=239:
        print("Class D")
    else:
        print("Class E")

def find_host_id_net_id(ip):
    if not validify_ip(ip):
        print("Not valid")
        return
    segments=ip.split(".")
    buffer=""
    for i in range(0,4):
        segment=segments[i]
        buffer+=to_binary(segment)
        if buffer.find("Error")!=-1:
            print(buffer)
            return
        if i==0:
            first_octet=segment[i]
            if 0<=int(first_octet)<=127:
                net=8
            elif 128<=int(first_octet)<=191:
                net=16
            elif 192<=int(first_octet)<=223:
                net=24
    network=buffer[:net]
    host=buffer[net:]
    print("Binary Format")
    print("Net id: ",network)
    print("Host id: ",host)
    print("Decimal format")
    print("Net id: ",end="")
    for i in range(0,len(network),8):
        segment=network[i:i+8]
        print(to_dotted_decimal(segment),end=".")
    print()
    print("Host id: ",end="")
    for i in range(0,len(host),8):
        segment=host[i:i+8]
        print(to_dotted_decimal(segment),end=".")
    print()

def find_network_broadcast_address(ip):
    if not validify_ip(ip):
        print("Not valid")
        return
    segments=ip.split(".")
    buffer=""
    for i in range(0,4):
        segment=segments[i]
        buffer+=to_binary(segment)
        if buffer.find("Error")!=-1:
            print(buffer)
            return
        if i==0:
            first_octet=segment[i]
            if 0<=int(first_octet)<=127:
                net=8
            elif 128<=int(first_octet)<=191:
                net=16
            elif 192<=int(first_octet)<=223:
                net=24
    network=buffer[:net]
    host=buffer[net:]
    first_address=network+"0"*(32-int(network))
    broadcast_address=network+"1"*(32-int(network))
    print("Binary Format")
    print("First address",first_address)
    print("Broadcast Address",broadcast_address)
    print("Decimal Format")
    print("First Address: ",end="")
    for i in range(0,len(first_address),8):
        segment=broadcast_address[i:i+8]
        print(to_dotted_decimal(segment),end=".")
    print()
    print("Broadcast Address: ",end="")
    for i in range(0,len(broadcast_address),8):
        segment=first_address[i:i+8]
        print(to_dotted_decimal(segment),end=".")
    print()

while True:
    print("Menu")
    print("1. Conversion")
    print("2. Find net id and host id")
    print("3. Find first address and last address")
    print("4. Exit")
    op=int(input("Enter your choice: "))
    if op==1:
        print("1. Convert dotted decimal to binary")
        print("2. Convert binary to dotted decimal")
        op1=int(input("Enter your choice: "))
        if op1==1:
            ip=input("Input ip address in dotted decimal format")
            if not validify_ip(ip):
                print("Not valid format")
            else:
                ip_binary="".join([to_binary(segment) for segment in ip.split(".")])
                if ip_binary.find("Error")!=-1:
                    print(ip_binary)
                else:
                    print("In binary format: ",ip_binary)
        elif op1==2:
            ip=input("Input ip address in binary format")
            flag=0
            if len(ip)!=32:
                print("Invalid format")
                continue
            for i in ip:
                if int(i)!=0 and int(i)!=1:
                    print("Invalid format")
                    flag=1
                    break
            if flag==1:
                continue
            for i in range(0,32,8):
                segment=ip[i:i+8]
                print(to_dotted_decimal(segment),end=".")
            print()
    elif op==2:
        ip=input("Input ip address in dotted decimal format")
        find_host_id_net_id(ip)
    elif op==3:
        ip=input("Input ip address in dotted decimal format")
        find_network_broadcast_address(ip)
    elif op==4:
        break
    else:
        print("Invalid input")
    
        
        
    
            
        



        