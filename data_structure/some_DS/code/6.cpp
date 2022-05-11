// ! there is software translate (queue)

#include <iostream>
#include <queue>
using namespace std;
queue<int> que;
const int Max = 1005;
int m, n;
bool inQue[Max];
int main()
{
    cin >> m >> n;
    int query = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (!inQue[x])
        {
            query++;
            if (que.size() == m)
            {
                int t = que.front();
                que.pop();
                inQue[t] = false;
            }
            que.push(x);
            inQue[x] = true;
        }
    }
    cout << query << endl;
}