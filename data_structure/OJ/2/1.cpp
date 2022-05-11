#include <iostream>
#define Max 10000500
using namespace std;
int t[Max];
int ans[Max];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        t[tmp]++;
    }
    ans[0] = t[0];
    for (int i = 0; i < 1e7; i++)
    {
        ans[i + 1] = ans[i] + t[i + 1];
    }
    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        cout << ans[b] - ans[a] + t[a] << endl;
    }
}