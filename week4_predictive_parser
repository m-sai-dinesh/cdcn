#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
map<pair<char, char>, string> table = {
    {{'E', 'i'}, "TR"}, {{'E', '('}, "TR"},
    {{'R', '+'}, "+TR"}, {{'R', ')'}, "#"}, {{'R', '$'}, "#"},
    {{'T', 'i'}, "FY"}, {{'T', '('}, "FY"},
    {{'Y', '*'}, "*FY"}, {{'Y', '+'}, "#"}, {{'Y', ')'}, "#"}, {{'Y', '$'}, "#"},
    {{'F', 'i'}, "i"}, {{'F', '('}, "(E)"}};
int main()
{
    string input, st = "$E";
    int ip = 0;
    cout << "Enter the input string (use i for identifier): ";
    cin >> input;
    input += '$';
    cout << "\nStack\t\tInput\t\tAction\n";
    cout << "---------------------------------------------\n";
    while (!st.empty())
    {
        char X = st.back(), a = input[ip];
        cout << st << "\t\t" << input.substr(ip) << "\t\t";
        if (X == '$' && a == '$')
        {
            cout << "Accept\n";
            return 0;
        }
        if (X == a)
        {
            st.pop_back();
            ip++;
            cout << "Match " << a << "\n";
        }
        else if (isupper(X) && table.count({X, a}))
        {
            string rhs = table[{X, a}];
            st.pop_back();
            cout << X << " -> " << (rhs == "#" ? "epsilon" : rhs) << "\n";
            if (rhs != "#")
                st += string(rhs.rbegin(), rhs.rend());
        }
        else
        {
            cout << "Error\n";
            return 0;
        }
    }
    cout << "Rejected\n";
    return 0;
}

Output

Enter the input string (use i for identifier): i

Stack		Input		Action
---------------------------------------------
$E		i$		E -> TR
$RT		i$		T -> FY
$RYF		i$		F -> i
$RYi		i$		Match i
$RY		$		Y -> epsilon
$R		$		R -> epsilon
$		$		Accept
