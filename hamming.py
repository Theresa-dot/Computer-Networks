def hamming_code(data):
    m=len(data)
    r=0
    while 2**r<m+r+1:
        r+=1
    print("The length of the data is: ",m)
    print("The length of the encoded data is: ",m+r)
    print("No. of redundancy bits: ",r)
    encoded=['r']*(m+r)
    j=m-1
    for i in range (len(encoded)):
        if i+1 not in [2**k for k in range(r)]:
            encoded[i]=data[j]
            j-=1
    info=encoded.copy()
    info.reverse()
    print("Encoded data with redundancy bits: ",info)
    for i in range(r):
        pos=2**i-1
        count=0
        for j in range(pos,len(encoded),2*pos+2):
            count+=sum(int(bit) for bit in encoded[j:j+pos+1] if bit!='r')
        if count%2!=0:
            encoded[pos]='1'
        else: 
            encoded[pos]='0'
    encoded.reverse()
    print("Encoded data is: ",''.join(encoded))
    
def hamming_check(data):
    n=len(data)
    encoded="".join(reversed(data))
    r=0
    while 2**r<n:
        r+=1
    sender=[]
    a=''
    error_bit=0
    for i in range(r):
        pos=2**i-1
        count=0
        for j in range(pos,len(encoded),2*pos+2):
            count+=sum(int(bit) for bit in encoded[j:j+pos+1] if bit!='r')
        if count%2!=0: 
            sender.append('1') 
        else:
            sender.append('0');
    sender.reverse()
    error_bit=int(a.join(sender),2)
    if error_bit>0:
        print("Error is detected at",error_bit)
        encoded=encoded[:error_bit-1]+('0' if encoded[error_bit-1]=='1' else '1')+encoded[error_bit:]
        print("Corrected data is: ","".join(reversed(encoded)))
    else:
        print("No error is detected")
    
            
def valid(data):
    for i in data:
        if i!='1' and i!='0':
            return False
    return True

data=input("Enter data: ")
if valid(data):
    encoded_data=hamming_code(data);
else:
    print("Invalid\n")
    exit()
check_data=input("Enter the received data: ")
comp=hamming_check(check_data)