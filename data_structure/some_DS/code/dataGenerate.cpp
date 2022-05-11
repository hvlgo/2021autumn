#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int n = rand();
    cout << n << endl;
    for (int i = 0; i < n; i++)
    {
        int t = rand();
        cout << t % 5 + 1 <<  " ";
        int s = rand();
        cout << s << endl;
    }
}