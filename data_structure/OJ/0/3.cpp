#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    int r = 1;
    if (a < b)
    {
        swap(a, b);
    }
    while (r)
    {
        r = a % b;
        a = b;
        b = r;
    }
    cout << a;
}