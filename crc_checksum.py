def crc(data, divisor):
    # Append zeros to the data to match the length of the divisor
    data += "0" * (len(divisor) - 1)

    # Convert data and divisor to lists for easier manipulation
    data = list(data)
    divisor = list(divisor)

    # Perform division
    for i in range(len(data) - len(divisor) + 1):
        if data[i] == "1":
            for j in range(len(divisor)):
                data[i + j] = str(int(data[i + j]) ^ int(divisor[j]))

    # Return the remainder (CRC value)
    return "".join(data[-(len(divisor)-1):])


def crc_check(data, divisor, crc_value):
    data += str(crc_value)
    data = list(data)
    divisor = list(divisor)

    # Perform division
    for i in range(len(data) - len(divisor) + 1):
        if data[i] == "1":
            for j in range(len(divisor)):
                data[i + j] = str(int(data[i + j]) ^ int(divisor[j]))

    # Return the remainder (CRC value)
    return "".join(data[-(len(divisor)-1):])


def calculate_checksum(data):
    checksum = 0

    for value in data:
        checksum += int(value, 2)  # Convert binary string to decimal

    checksum_bits = 8 if len(data[0]) <= 8 else 16

    if checksum_bits == 8:
        complement = ~checksum
        complement %= 256  # Take the modulo 256 to get an 8-bit checksum value
        return bin(complement)[2:].zfill(8)  # Convert checksum to 8-bit binary string
    else:
        complement = ~checksum
        complement %= 65536  # Take the modulo 65536 to get a 16-bit checksum value
        return bin(complement)[2:].zfill(16)  # Convert checksum to 16-bit binary string


def input_check(data):
    for i in data:
        if i != '0' and i != '1':
            return False
    return True


# Menu-driven program
while True:
    print("Menu:")
    print("1. CRC and CRC check")
    print("2. Checksum")
    print("3. Exit")

    choice = input("Enter your choice: ")

    if choice == "1":
        data_input = input("Enter data: ")
        divisor_input = input("Enter divisor: ")

        if not input_check(data_input) or not input_check(divisor_input):
            print("Invalid input! Please enter binary strings.")
            continue

        crc_value = crc(data_input, divisor_input)
        print("CRC value:", crc_value)

        check_input = input("Enter received data for CRC errror detection: ")

        if not input_check(check_input):
            print("Invalid input! Please enter a binary string.")
            continue

        check_result = crc_check(check_input, divisor_input, crc_value)
        print("CRC check result:", check_result)

        if check_result == '0' * len(crc_value):
            print("No error is detected.")
        else:
            print("Error is detected. CRC check result should be all zeroes for zero error.")
        print("-----------------------------------------------------------------------------------------------------------------------------------------------")
    elif choice == "2":
        rows = int(input("Enter number of rows: "))
        sender= []
        receiver=[]

        for i in range(rows):
            ip = input("Enter data: ")
            if not input_check(ip):
                print("Invalid input! Please enter a binary string.")
                break
            sender.append(ip)
        else:
            checksum_bits = 8 if len(sender[0]) <= 8 else 16
            checksum = calculate_checksum(sender)
            print(f"Checksum value ({checksum_bits}-bit):", checksum)
            
            for i in range(rows):
                ip = input("Enter received data for checksum error detection: ")
                if not input_check(ip):
                    print("Invalid input! Please enter a binary string.")
                    break
                receiver.append(ip)
            
            receiver_side_result = calculate_checksum(receiver + [checksum])
            print(f"Checksum value ({checksum_bits}-bit) at the receiver side:", receiver_side_result)

            if receiver_side_result == '0' * checksum_bits:
                print("No error is detected in the code.")
            else:
                print("Error is detected in the code.")
            print("-----------------------------------------------------------------------------------------------------------------------------------------------")

    elif choice == "3":
        print("Exiting...")
        print("-----------------------------------------------------------------------------------------------------------------------------------------------")
        break

    else:
        print("Invalid choice! Please enter a valid option.")