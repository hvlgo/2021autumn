// ! there is queue and Joseph question

#include <iostream>
#include <queue>
using namespace std;
queue<int> que;
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        que.push(i + 1);
    }
    int num = 1;
    while (!que.empty())
    {
        if (num == m)
        {
            cout << que.front() << ' ';
            que.pop();
            num = 1;
        }
        else
        {
            que.push(que.front());
            que.pop();
            num++;
        }
    }
}