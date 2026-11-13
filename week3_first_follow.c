#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;
vector<string> prod;
map<char, set<char>> First, Follow;
set<char> firstOf(const string &s)
{
    set<char> res;
    for (char c : s)
    {
        if (!isupper(c))
        {
            res.insert(c);
            return res;
        }
        for (char x : First[c])
            if (x != '#')
                res.insert(x);
        if (!First[c].count('#'))
            return res;
    }
    res.insert('#');
    return res;
}
template <class F>
void repeatUntilStable(F step)
{
    bool changed = true;
    while (changed)
        changed = step();
}
void print(const string &name, map<char, set<char>> &m, const vector<char> &nts)
{
    cout << "\n" << name << " sets:\n";
    for (char nt : nts)
    {
        cout << name << "(" << nt << ") = { ";
        for (char c : m[nt])
            cout << c << " ";
        cout << "}\n";
    }
}
int main()
{
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    prod.resize(n);
    cout << "Enter productions (use # for epsilon):\n";
    vector<char> nts;
    for (auto &p : prod)
    {
        cin >> p;
        if (!First.count(p[0]))
        {
            First[p[0]];
            nts.push_back(p[0]);
        }
    }
    repeatUntilStable([&]
    {
        bool changed = false;
        for (auto &p : prod)
        {
            size_t before = First[p[0]].size();
            set<char> f = firstOf(p.substr(2));
            First[p[0]].insert(f.begin(), f.end());
            changed |= First[p[0]].size() != before;
        }
        return changed;
    });
    Follow[prod[0][0]].insert('$');
    repeatUntilStable([&]
    {
        bool changed = false;
        for (auto &p : prod)
            for (size_t i = 2; i < p.size(); i++)
            {
                if (!isupper(p[i]))
                    continue;
                char B = p[i];
                size_t before = Follow[B].size();
                set<char> f = firstOf(p.substr(i + 1));
                for (char x : f)
                    if (x != '#')
                        Follow[B].insert(x);
                if (f.count('#'))
                    Follow[B].insert(Follow[p[0]].begin(), Follow[p[0]].end());
                changed |= Follow[B].size() != before;
            }
        return changed;
    });
    print("FIRST", First, nts);
    print("FOLLOW", Follow, nts);
    return 0;
}

Output
Enter number of productions: 8
Enter productions (use # for epsilon):
E=TR
R=+TR
R=#
T=FS
S=*FS
S=#
F=(E)
F=i

FIRST sets:
FIRST(E) = { ( i }
FIRST(R) = { # + }
FIRST(T) = { ( i }
FIRST(S) = { # * }
FIRST(F) = { ( i }

FOLLOW sets:
FOLLOW(E) = { $ ) }
FOLLOW(R) = { $ ) }
FOLLOW(T) = { $ ) + }
FOLLOW(S) = { $ ) + }
FOLLOW(F) = { $ ) * + }
