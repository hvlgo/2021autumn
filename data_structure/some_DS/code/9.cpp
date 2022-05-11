// ! there is stack simulation

#include <iostream>
#include <stack>
using namespace std;
int push[100005];
int pop[100005];
stack<int> sck;
int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 0; i < n; i++) cin >> push[i];
        for (int i = 0; i < n; i++) cin >> pop[i];
        for (int i = 0; i < n; i++)
        {
            sck.push(push[i]);
            while (sck.top() == pop[sum])
            {
                sck.pop();
                sum++;
                if (sck.empty()) break;
            }
        }
        if (sck.empty()) cout << "Yes" << endl;
        else cout << "No" << endl;
        while(!sck.empty()) sck.pop();
    }
}