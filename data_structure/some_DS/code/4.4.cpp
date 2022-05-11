// ! there is segment tree

#include <iostream>
using namespace std;
#define Max 100100
struct
{
    int l;
    int r;
    long long sum, addLazy, mulLazy;
}node[Max * 4];
int num[Max];
int n, m, q;

void build(int p, int l, int r)
{
    node[p].l = l;
    node[p].r = r;
    node[p].mulLazy = 1;
    if (l == r)
    {
        node[p].sum = num[l];
        node[p].sum %= q;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    node[p].sum = node[p << 1].sum + node[p << 1 | 1].sum;
    node[p].sum %= q;
}


void pushdown(int p)
{
    if (node[p].addLazy || node[p].mulLazy != 1)
    {
        node[p << 1].sum *= node[p].mulLazy;
        node[p << 1].sum += (node[p << 1].r - node[p << 1].l + 1) * node[p].addLazy;
        node[p << 1].sum %= q;
        node[p << 1 | 1].sum *= node[p].mulLazy;
        node[p << 1 | 1].sum += (node[p << 1 | 1].r - node[p << 1 | 1].l + 1) * node[p].addLazy;
        node[p << 1 | 1].sum %= q;
        node[p << 1].mulLazy *= node[p].mulLazy;
        node[p << 1].mulLazy %= q;
        node[p << 1].addLazy = node[p << 1].addLazy * node[p].mulLazy + node[p].addLazy;
        node[p << 1].addLazy %= q;
        node[p << 1 | 1].mulLazy *= node[p].mulLazy;
        node[p << 1 | 1].mulLazy %= q;
        node[p << 1 | 1].addLazy = node[p << 1 | 1].addLazy * node[p].mulLazy + node[p].addLazy;
        node[p << 1 | 1].addLazy %= q;
        node[p].addLazy = 0;
        node[p].mulLazy = 1;
    }
}

long long query(int p, int l, int r)
{
    if (l <= node[p].l && r >= node[p].r)
    {
        return node[p].sum;
    }
    pushdown(p);
    long long res = 0;
    int mid = (node[p].l + node[p].r) >> 1;
    if (l <= mid)
    {
        res += query(p << 1, l, r);
    }
    if (r > mid)
    {
        res += query(p << 1 | 1, l, r);
    }
    return res % q;
}

void add(int p, int l, int r, int k)
{
    if (l <= node[p].l && r >= node[p].r)
    {
        node[p].sum += (node[p].r -  node[p].l + 1) * k;
        node[p].sum %= q;
        node[p].addLazy += k;
        node[p].addLazy %= q;
        return;
    }
    pushdown(p);
    int mid = (node[p].l + node[p].r) >> 1;
    if (l <= mid)
        add(p << 1, l, r, k);
    if (r > mid)
        add(p << 1 | 1, l, r, k);
    node[p].sum = (node[p << 1].sum + node[p << 1 | 1].sum) % q;
}

void mul(int p, int l, int r, int k)
{
    if (l <= node[p].l && r >= node[p].r)
    {
        node[p].sum *= k;
        node[p].sum %= q;
        node[p].mulLazy *= k;
        node[p].mulLazy %= q;
        node[p].addLazy *= k;
        node[p].addLazy %= q;
        return;
    }
    pushdown(p);
    int mid = (node[p].l + node[p].r) >> 1;
    if (l <= mid)
        mul(p << 1, l, r, k);
    if (r > mid)
        mul(p << 1 | 1, l, r, k);
    node[p].sum = (node[p << 1].sum + node[p << 1 | 1].sum) % q;
}

int main()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++)
    {
        int type, x, y;
        long long k;
        cin >> type;
        switch (type)
        {
            case 1:
                    cin >> x >> y >> k;
                    mul(1, x, y, k);
                    break;
            case 2:
                    cin >> x >> y >> k;
                    add(1, x, y, k);
                    break;
            case 3:
                    cin >> x >> y;
                    cout << query(1, x, y)  << endl;
                    break;
        }
    }
    return 0;
}