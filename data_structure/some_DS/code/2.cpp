// ! there is map

#include <iostream>
#include <map>
using namespace std;
map<long long, int> val;
int main()
{
    int n, q;
    cin >> n >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int i, j, k;
            cin >> i >> j >> k;
            val[i * 100000 + j] = k;
        }
        else if (type == 2)
        {
            int i, j;
            cin >> i >> j;
            cout << val[i * 100000 + j] << endl;
        }
    }
}