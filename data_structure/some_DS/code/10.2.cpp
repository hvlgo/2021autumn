// ! there is binary index tree

#include <iostream>
#define Max 500005
#define lowbit(x) ((x) & (-x))
using namespace std;


long long tree[Max];
long long A[Max];
void update(int x, int val)
{
    for (int pos = x; pos < Max; pos += lowbit(pos))
        tree[pos] += val;
}
long long query(int n)
{
    long long ans = 0;
    for (int pos = n; pos > 0; pos -= lowbit(pos))
    {
        ans += tree[pos];
    }
    return ans;
}
long long query(int u, int v)
{
    return query(v) - query(u - 1);
}
int main()
{
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }
    for (int i = 1; i <= N; i++)
    {
        if (i == 1)
            update(i, A[i]);
        else
            update(i, A[i] - A[i - 1]);
    }
    for (int i = 0; i < M; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            update(x, k);
            update(y+1, -k);
        }
        else
        {
            int x;
            cin >> x;
            cout << query(x) << endl;
        }
    }
}