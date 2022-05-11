// ! there is priority queue (heap)

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
priority_queue<long long, vector<long long>, greater<int>> que;
long long ans;
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        que.push(tmp);
    }
    while(que.size() != 1)
    {
        long long first = que.top();
        que.pop();
        long long second = que.top();
        que.pop();
        long long sum = first + second;
        que.push(sum);
        ans += sum;
    }
    cout << ans;
}