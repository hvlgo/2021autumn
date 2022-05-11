// ! there is a simulation

#include <iostream>
#include <queue>
using namespace std;
int nation[100005];
int Time[300005];
int num[300005];
int ans;
int p;
int main()
{
    int pos = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        int k;
        cin >> t >> k;
        for (int j = 0; j < k; j++)
        {
            int tmp;
            cin >> tmp;
            Time[++pos] = t;
            num[pos] = tmp;
            if (nation[tmp] == 0)
                ans++;
            nation[tmp]++;
        }
        while (t - Time[p] >= 86400)
        {
            nation[num[p]]--;
            if (nation[num[p]] == 0)
                ans--;
            p++;
        }
        cout << ans << endl;
    }
}