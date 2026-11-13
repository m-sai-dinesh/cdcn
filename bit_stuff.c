#include <iostream>
#include <string>
using namespace std;
const string FLAG = "01111110";
string stuff(const string &data)
{
    string out;
    int ones = 0;
    for (char c : data)
    {
        out += c;
        if (c == '1' && ++ones == 5)
        {
            out += '0';
            ones = 0;
        }
        else if (c == '0')
            ones = 0;
    }
    return out;
}
string unstuff(const string &s)
{
    string out;
    int ones = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        out += s[i];
        if (s[i] == '1' && ++ones == 5)
        {
            i++;
            ones = 0;
        }
        else if (s[i] == '0')
            ones = 0;
    }
    return out;
}
string addFrame(const string &data)
{
    return FLAG + stuff(data) + FLAG;
}
string removeFrame(const string &frame)
{
    int f = FLAG.size();
    if (frame.size() < 2 * f || frame.substr(0, f) != FLAG || frame.substr(frame.size() - f) != FLAG)
    {
        cout << "Error: Invalid frame!\n";
        return "";
    }
    return unstuff(frame.substr(f, frame.size() - 2 * f));
}
int main()
{
    string data;
    cout << "Enter data: ";
    cin >> data;
    string frame = addFrame(data);
    cout << "Transmitted Frame: " << frame << "\n";
    cout << "Received Data: " << removeFrame(frame) << "\n";
    return 0;
}

Output

Enter data: 0111111011111
Transmitted Frame: 0111111001111101011111001111110
Received Data: 0111111011111
