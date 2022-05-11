// ! there is segment tree

#include <iostream>
using namespace std;

#define Max 100005
struct
{
    int l;
    int r;
    long long sum, lazy;
} node[Max * 4];
int n, m;
int num[Max];

void pushdown(int p)
{
    if(node[p].lazy){
        node[p << 1].sum += node[p].lazy * (node[p << 1].r-node[p << 1].l + 1);
        node[p << 1 | 1].sum += node[p].lazy * (node[p << 1 | 1].r-node[p << 1 | 1].l + 1);
        node[p << 1].lazy += node[p].lazy;
        node[p << 1 | 1].lazy += node[p].lazy;
        node[p].lazy = 0;
    }
}

void build(int p, int l, int r)
{
    node[p].l = l;
    node[p].r = r;
    if (l == r)
    {
        node[p].sum = num[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    node[p].sum = node[p << 1].sum + node[p << 1 | 1].sum;
}

long long query(int p, int l, int r)
{
    if (l <= node[p].l && r >= node[p].r)
        return node[p].sum;
    pushdown(p);
    int mid = (node[p].l + node[p].r) >> 1;
    long long res = 0;
    if (l <= mid)
    {
        res += query(p << 1, l, r);
    }
    if (r > mid)
    {
        res += query(p << 1 | 1, l, r);
    }
    return res;
}

void add(int p, int l, int r, int k)
{
    if (l <= node[p].l && r >= node[p].r)
    {
        node[p].sum += k * (node[p].r - node[p].l + 1);
        node[p].lazy += k;
        return;
    }
    pushdown(p);
    int mid = (node[p].l + node[p].r) >> 1;
    if (l <= mid)
    {
        add(p << 1, l, r, k);
    }
    if (r > mid)
    {
        add(p << 1 | 1, l, r, k);
    }
    node[p].sum = node[p << 1].sum + node[p << 1 | 1].sum;
}


int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            add(1, x, y, k);
        }
        else
        {
            int x, y;
            cin >> x >> y;
            cout << query(1, x, y) << endl;
        }
    }
}