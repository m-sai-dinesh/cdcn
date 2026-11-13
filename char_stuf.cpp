#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
const unsigned char FLAG = 0x7E, ESC = 0x7D;
typedef vector<unsigned char> Bytes;
Bytes stuff(const Bytes &data)
{
    Bytes out;
    for (unsigned char b : data)
    {
        if (b == FLAG || b == ESC)
        {
            out.push_back(ESC);
            out.push_back(b ^ 0x20);
        }
        else
            out.push_back(b);
    }
    return out;
}
Bytes unstuff(const Bytes &s)
{
    Bytes out;
    bool escaped = false;
    for (unsigned char b : s)
    {
        if (escaped)
        {
            out.push_back(b ^ 0x20);
            escaped = false;
        }
        else if (b == ESC)
            escaped = true;
        else
            out.push_back(b);
    }
    return out;
}
void printBytes(const Bytes &bytes)
{
    cout << " : ";
    for (unsigned char b : bytes)
        cout << hex << uppercase << setw(2) << setfill('0') << (int)b << " ";
    cout << dec << "\n";
}
int main()
{
    cout << "\n============================================================\n";
    cout << "       CHARACTER STUFFING - C++ Implementation\n";
    cout << "============================================================\n";
    Bytes original = {0x01, 0x7E, 0x02, 0x7D, 0x03, 0x7E, 0x04};
    cout << "\n[1] ORIGINAL DATA:\n";
    printBytes(original);
    Bytes stuffed = stuff(original);
    cout << "\n[2] AFTER STUFFING (Sender):\n";
    printBytes(stuffed);
    Bytes recovered = unstuff(stuffed);
    cout << "\n[3] AFTER UNSTUFFING (Receiver):\n";
    printBytes(recovered);
    if (original == recovered)
        cout << "\nSUCCESS: Original data recovered!\n";
    else
        cout << "\nERROR: Data mismatch!\n";
    cout << "\n============================================================\n";
    return 0;
}

Output

============================================================
       CHARACTER STUFFING - C++ Implementation
============================================================

[1] ORIGINAL DATA:
 : 01 7E 02 7D 03 7E 04 

[2] AFTER STUFFING (Sender):
 : 01 7D 5E 02 7D 5D 03 7D 5E 04 

[3] AFTER UNSTUFFING (Receiver):
 : 01 7E 02 7D 03 7E 04 

SUCCESS: Original data recovered!

============================================================
