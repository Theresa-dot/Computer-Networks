#include <iostream>
#include <string>
#include <bitset>

using namespace std;

bool isValidIPv4Address(const string &ip)
{
    size_t pos = 0;
    size_t found;
    int count = 0;

    while ((found = ip.find('.', pos)) != string::npos)
    {
        string segment = ip.substr(pos, found - pos);
        if (segment.empty() || segment.size() > 3)
            return false;
        if (segment.size() > 1 && segment[0] == '0')
            return false;
        for (char c : segment)
        {
            if (!isdigit(c))
                return false;
        }
        int num = stoi(segment);
        if (num < 0 || num > 255)
            return false;

        pos = found + 1;
        count++;
    }

    if (count != 3)
        return false;

    string segment = ip.substr(pos);
    if (segment.empty() || segment.size() > 3)
        return false;
    if (segment.size() > 1 && segment[0] == '0')
        return false;
    for (char c : segment)
    {
        if (!isdigit(c))
            return false;
    }
    int num = stoi(segment);
    if (num < 0 || num > 255)
        return false;

    return true;
}

string toBinary(const string &segment)
{
    int num = stoi(segment);
    bitset<8> bin(num);
    return bin.to_string();
}

string toDottedDecimal(const string &segment)
{
    int num = stoi(segment);
    return to_string(num);
}

void classifyIPAddress(const string &ip)
{
    string buffer = "";
    int network = 0;

    size_t pos = 0;
    size_t found;
    for (int i = 0; i < 4; i++)
    {
        found = ip.find('.', pos);
        string segment = ip.substr(pos, found - pos);
        pos = found + 1;

        buffer += toBinary(segment);

        if (i == 0)
        {
            int firstOctet = stoi(segment);
            if (firstOctet >= 1 && firstOctet <= 126)
            {
                cout << "Class A" << endl;
                network = 8;
            }
            else if (firstOctet >= 128 && firstOctet <= 191)
            {
                cout << "Class B" << endl;
                network = 16;
            }
            else if (firstOctet >= 192 && firstOctet <= 223)
            {
                cout << "Class C" << endl;
                network = 24;
            }
            else if(firstOctet >= 224 &&)
            else
            {
                cout << "Not a valid Class A, B, or C address" << endl;
                return;
            }
        }
    }

    string networkID = buffer.substr(0, network);
    string hostID = buffer.substr(network);

    cout << "Network ID (Binary): " << networkID << endl;
    cout << "Network ID (Dotted Decimal): ";
    for (int i = 0; i < networkID.length(); i += 8)
    {
        string segment = networkID.substr(i, 8);
        cout << toDottedDecimal(segment);
        if (i < networkID.length() - 8)
            cout << ".";
    }
    cout << endl;

    cout << "Host ID (Binary): " << hostID << endl;
    cout << "Host ID (Dotted Decimal): ";
    for (int i = 0; i < hostID.length(); i += 8)
    {
        string segment = hostID.substr(i, 8);
        cout << toDottedDecimal(segment);
        if (i < hostID.length() - 8)
            cout << ".";
    }
    cout << endl;
}

int main()
{
    string ip;

    cout << "Enter an IPv4 address: ";
    cin >> ip;

    if (!isValidIPv4Address(ip))
    {
        cout << "Invalid IPv4 address" << endl;
        return 0;
    }

    classifyIPAddress(ip);

    return 0;
}