// ! 这是括号匹配

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int a[105]; 
int main()
{
    int i,j;
    string s;
    cin >> s;
    for (i=0; i<s.length(); i++) {
        if (s[i] == ')') {
            for (j=i-1; j>=0; j--) {
                if (s[j] == '(' && a[j] == 0) { 
                    a[i] = a[j] = 1;
                    break;
                }
                //else if (s[j] == '[' && a[j] == 0) break;
            }
        }
        else if (s[i] == ']') {
            for (j=i-1; j>=0; j--) {
                if (s[j] == '[' && a[j] == 0) {
                    a[i] = a[j] = 1;
                    break;
                }
                //else if (s[j] == '(' && a[j] == 0) break;
            }
        }
    }
    for (i=0; i<s.length(); i++) {
        if (a[i] == 0) { 
            if (s[i] == '(' || s[i] == ')') cout << "()";
            else cout << "[]";
        }
        else cout << s[i];
    }
    return 0;
}