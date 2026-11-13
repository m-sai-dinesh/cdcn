#include <bits/stdc++.h>
using namespace std;
vector<pair<char,string>> productions;
map<char,set<char>> FIRST;
vector<set<pair<pair<int,int>,char>>> C, M;
map<pair<int,char>,int> trans, T;
map<pair<int,char>,string> ACTION;
map<pair<int,char>,int> GOTO;
set<char> findFirst(char symbol);
set<char> firstOfString(string str) {
    set<char> result;
    bool allNullable = true;
    for(char ch : str) {
        if(ch == '#') {
            result.insert('#');
            break;
        }
        if(!isupper(ch)) {
            result.insert(ch);
            allNullable = false;
            break;
        }
        set<char> temp = findFirst(ch);
        for(char x : temp)
            if(x != '#')
                result.insert(x);
        if(temp.find('#') == temp.end()) {
            allNullable = false;
            break;
        }
    }
    if(allNullable)
        result.insert('#');
    return result;
}
set<char> findFirst(char symbol) {
    if(FIRST.count(symbol))
        return FIRST[symbol];
    for(auto p : productions) {
        if(p.first != symbol)
            continue;
        if(p.second == "#") {
            FIRST[symbol].insert('#');
            continue;
        }
        set<char> temp = firstOfString(p.second);
        FIRST[symbol].insert(temp.begin(),temp.end());
    }
    return FIRST[symbol];
}
set<pair<pair<int,int>,char>> closure(
    set<pair<pair<int,int>,char>> I) {
    while(true) {
        auto nw = I;
        for(auto it : I) {
            int p = it.first.first;
            int d = it.first.second;
            char la = it.second;
            string rhs = productions[p].second;
            if(d >= rhs.size())
                continue;
            char B = rhs[d];
            if(!isupper(B))
                continue;
            string beta = rhs.substr(d+1) + la;
            set<char> f = firstOfString(beta);
            for(int i=0; i<productions.size(); i++) {
                if(productions[i].first == B) {
                    for(char x : f) {
                        if(x != '#')
                            nw.insert({{i,0},x});
                    }
                }
            }
        }
        if(nw == I)
            return I;
        I = nw;
    }
}
set<pair<pair<int,int>,char>> goTo(
    set<pair<pair<int,int>,char>> I, char X) {
    set<pair<pair<int,int>,char>> J;
    for(auto it : I) {
        int p = it.first.first;
        int d = it.first.second;
        char la = it.second;
        string rhs = productions[p].second;
        if(d < rhs.size() && rhs[d] == X)
            J.insert({{p,d+1},la});
    }
    if(!J.empty())
        J = closure(J);
    return J;
}
void generateStates() {
    C.push_back(closure({{{0,0},'$'}}));
    for(int i=0; i<C.size(); i++) {
        set<char> symbols;
        for(auto it : C[i]) {
            int p = it.first.first;
            int d = it.first.second;
            string rhs = productions[p].second;
            if(d < rhs.size())
                symbols.insert(rhs[d]);
        }
        for(char X : symbols) {
            auto J = goTo(C[i],X);
            int j = -1;
            for(int k=0; k<C.size(); k++) {
                if(C[k] == J) {
                    j = k;
                    break;
                }
            }
            if(j == -1) {
                j = C.size();
                C.push_back(J);
            }
            trans[{i,X}] = j;
        }
    }
}
void mergeStates() {
    map<set<pair<int,int>>,int> cores;
    vector<int> mapping(C.size());
    for(int i=0; i<C.size(); i++) {
        set<pair<int,int>> core;
        for(auto it : C[i])
            core.insert(it.first);
        if(!cores.count(core)) {
            cores[core] = M.size();
            M.push_back({});
        }
        mapping[i] = cores[core];
        M[mapping[i]].insert(
            C[i].begin(),C[i].end()
        );
    }
    for(auto x : trans) {
        int i = x.first.first;
        char X = x.first.second;
        T[{mapping[i],X}] = mapping[x.second];
    }
}
bool put(int s, char a, string v) {
    if(ACTION.count({s,a}) &&
       ACTION[{s,a}] != v) {
        cout << "LALR Conflict detected!\n";
        return false;
    }
    ACTION[{s,a}] = v;
    return true;
}
bool buildTable() {
    for(int s=0; s<M.size(); s++) {
        for(auto it : M[s]) {
            int p = it.first.first;
            int d = it.first.second;
            char la = it.second;
            string rhs = productions[p].second;
            char A = productions[p].first;
            if(d < rhs.size()) {
                char X = rhs[d];
                int j = T[{s,X}];
                if(isupper(X))
                    GOTO[{s,X}] = j;
                else {
                    if(!put(s,X,"s"+to_string(j)))
                        return false;
                }
            }
            else {
                if(p == 0 && la == '$') {
                    if(!put(s,'$',"acc"))
                        return false;
                }
                else {
                    if(!put(s,la,"r"+to_string(p)))
                        return false;
                }
            }
        }
    }
    return true;
}
void printTable() {
    cout << "\nACTION TABLE\n";
    for(auto x : ACTION) {
        cout << "State " << x.first.first
             << " " << x.first.second
             << " = " << x.second << "\n";
    }
    cout << "\nGOTO TABLE\n";

    for(auto x : GOTO) {
        cout << "State " << x.first.first
             << " " << x.first.second
             << " = " << x.second << "\n";
    }
}
void parse(string w) {
    if(w.empty() || w.back() != '$')
        w += '$';
    vector<int> st = {0};
    int i = 0;
    while(i < w.size()) {
        int s = st.back();
        char a = w[i];
        auto it = ACTION.find({s,a});
        cout << "State: " << s
             << " Input: " << w.substr(i);
        if(it == ACTION.end()) {
            cout << " ERROR\nString Rejected\n";
            return;
        }
        string act = it->second;
        cout << " Action: " << act << "\n";
        if(act == "acc") {
            cout << "\nString Accepted!\n";
            return;
        }
        if(act[0] == 's') {
            st.push_back(stoi(act.substr(1)));
            i++;
        }
        else {
            int p = stoi(act.substr(1));
            char A = productions[p].first;
            int len = productions[p].second == "#" ?
                      0 : productions[p].second.size();
            while(len--)
                st.pop_back();
           int ns = st.back();
            if(!GOTO.count({ns,A})) {
                cout << "String Rejected\n";
                return;
            }
            st.push_back(GOTO[{ns,A}]);
        }
    }
}
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    char start;
    cout << "Enter start symbol: ";
    cin >> start;
    productions.push_back({'Z',string(1,start)});
    cout << "Enter productions (Example: S=CC):\n";
    for(int i=0; i<n; i++) {
        char lhs, equal;
        string rhs;
        cin >> lhs >> equal >> rhs;
        productions.push_back({lhs,rhs});
    }
    findFirst(start);
    findFirst('Z');
    generateStates();
    mergeStates();
    if(!buildTable())
        return 0;
    cout << "\nLR(1) States: " << C.size();
    cout << "\nLALR States: " << M.size() << "\n";
    printTable();
    string input;
    cout << "\nEnter input string: ";
    cin >> input;
    parse(input);
    return 0;
}


output 

Enter number of productions: 3
S
S = CC
C = cC
C = d
Enter start symbol: Enter productions (Example: S=CC):

LR(1) States: 10
LALR States: 7

ACTION TABLE
State 0 c = s3
State 0 d = s4
State 1 c = s3
State 1 d = s4
State 2 $ = acc
State 3 c = s3
State 3 d = s4
State 4 $ = r3
State 4 c = r3
State 4 d = r3
State 5 $ = r1
State 6 $ = r2
State 6 c = r2
State 6 d = r2

GOTO TABLE
State 0 C = 1
State 0 S = 2
State 1 C = 5
State 3 C = 6

Enter input string: dd
State: 0 Input: dd$ Action: s4
State: 4 Input: d$ Action: r3
State: 1 Input: d$ Action: s4
State: 4 Input: $ Action: r3
State: 5 Input: $ Action: r1
State: 2 Input: $ Action: acc

String Accepted!
