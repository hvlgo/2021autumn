// ! there is binary index tree

#include <iostream>
#define lowbit(x) ((x) & (-x))
#define Max 500005
using namespace std;

long long tree[Max];
void update(int x, int val)
{
    for (int i = x; i < Max; i += lowbit(i))
        tree[i] += val;
}
long long query(int n)
{
    long long ans = 0;
    for (int i = n; i > 0; i -= lowbit(i))
        ans += tree[i];
    return ans;
}
long long query(int u, int v)
{
    return query(v) - query(u - 1);
}
int main()
{
    int n, m;
    int tmp;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> tmp;
        update(i, tmp);
    }
    for (int i = 0; i < m; i++)
    {
        int op, x, y;
        cin >> op;
        cin >> x >> y;
        if (op == 1)
        {
            update(x, y);
        }
        else
        {
            cout << query(x, y) << endl;
        }
    }
}