
#include <bits/stdc++.h>
using namespace std;

int action(int state, char ch) {
    switch(state) {
        case 0:
        case 1:
        case 3:
            if(ch == 'c') return 3;
            if(ch == 'd') return 4;
            break;

        case 2:
            if(ch == '$') return 100;
            break;

        case 4:
            if(ch == 'c' || ch == 'd' || ch == '$') return -3;
            break;

        case 5:
            if(ch == '$') return -1;
            break;

        case 6:
            if(ch == 'c' || ch == 'd' || ch == '$') return -2;
            break;
    }
    return 0;
}

int goTo(int state, char ch) {
    if(state == 0 && ch == 'C') return 1;
    if(state == 0 && ch == 'S') return 2;
    if(state == 1 && ch == 'C') return 5;
    if(state == 3 && ch == 'C') return 6;
    return -1;
}

void parse(string input) {
    input += '$';

    vector<int> st = {0};
    int i = 0;

    cout << "\nParsing Steps:\n";

    while(i < input.size()) {
        int s = st.back();
        char ch = input[i];

        int act = action(s, ch);

        cout << "State: " << s
             << " Input: " << input.substr(i);

        if(act == 0) {
            cout << " Action: ERROR\n";
            cout << "\nString Rejected!\n";
            return;
        }

        if(act == 100) {
            cout << " Action: ACCEPT\n";
            cout << "\nString Accepted!\n";
            return;
        }

        if(act > 0) {
            cout << " Action: s" << act << "\n";
            st.push_back(act);
            i++;
        }
        else {
            int p = -act;
            int len;

            if(p == 1) {
                cout << " Action: r1 (S -> CC)\n";
                len = 2;
            }
            else if(p == 2) {
                cout << " Action: r2 (C -> cC)\n";
                len = 2;
            }
            else {
                cout << " Action: r3 (C -> d)\n";
                len = 1;
            }

            while(len--)
                st.pop_back();

            int ns = goTo(st.back(),
                          p == 1 ? 'S' : 'C');

            if(ns == -1) {
                cout << "\nString Rejected!\n";
                return;
            }

            st.push_back(ns);
        }
    }
}

int main() {
    string input;

    cout << "Grammar:\n";
    cout << "S -> CC\n";
    cout << "C -> cC\n";
    cout << "C -> d\n";

    cout << "\nEnter input string: ";
    cin >> input;

    parse(input);

    return 0;
}


output 

Grammar:
S -> CC
C -> cC
C -> d

Enter input string: ccdd

Parsing Steps:
State: 0 Input: ccdd$ Action: s3
State: 3 Input: cdd$ Action: s3
State: 3 Input: dd$ Action: s4
State: 4 Input: d$ Action: r3 (C -> d)
State: 6 Input: d$ Action: r2 (C -> cC)
State: 6 Input: d$ Action: r2 (C -> cC)
State: 1 Input: d$ Action: s4
State: 4 Input: $ Action: r3 (C -> d)
State: 5 Input: $ Action: r1 (S -> CC)
State: 2 Input: $ Action: ACCEPT

String Accepted!
