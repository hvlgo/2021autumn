#include <iostream>
#include <stdlib.h>
#include <algorithm>
#define Max 100500
using namespace std;

struct node
{
    int val, pri, tot, size;
    int son[2];
}tree[Max];
int sum, r;
void pushup(int pos)
{
    tree[pos].size = tree[tree[pos].son[0]].size + tree[tree[pos].son[1]].size + tree[pos].tot;
    return;
}

void rotate(int & pos, int type)
{
    int tmp = tree[pos].son[type ^ 1];
    tree[pos].son[type ^ 1] = tree[tmp].son[type];
    tree[tmp].son[type] = pos;
    pushup(pos);
    pushup(tmp);
    pos = tmp;
    return;
}//! type = 0,左旋; type = 1, 右旋；

void insert(int &p, int x)
{
    if (p == 0)
    {
        p = ++sum;
        tree[p].size = tree[p].tot = 1;
        tree[p].val = x;
        tree[p].pri = rand();
        return;
    }
    if (tree[p].val == x)
    {
        tree[p].size++;
        tree[p].tot++;
        return;
    }
    int type = (x > tree[p].val);
    insert(tree[p].son[type], x);
    if (tree[p].pri < tree[tree[p].son[type]].pri)
        rotate(p, type ^ 1);
    pushup(p);
}

int Rank(int p, int x)
{
    if (!p) return 0;
    if (tree[p].val == x) return tree[tree[p].son[0]].size ;
    if (tree[p].val < x) return tree[tree[p].son[0]].size + tree[p].tot + Rank(tree[p].son[1], x);
    if (tree[p].val > x) return Rank(tree[p].son[0], x);
}

bool exist = true;
int Kth(int p, int x)
{
    if (!p) 
    {
        exist = false;
        return 0;
    }
    if (x <= tree[tree[p].son[0]].size) return Kth(tree[p].son[0], x);
    else if (x > tree[tree[p].son[0]].size + tree[p].tot) return Kth(tree[p].son[1], x - tree[tree[p].son[0]].size + tree[p].tot);
    else return tree[p].val;
}

int prev(int p, int x)
{
    if (!p) return -2147483647;
    if (x <= tree[p].val) return prev(tree[p].son[0], x);
    else return max(tree[p].val, prev(tree[p].son[1], x));
}

int succ(int p, int x)
{
    if (!p) return 2147483647;
    if (x >= tree[p].val) return succ(tree[p].son[1], x);
    else return min(tree[p].val, succ(tree[p].son[0], x));
}

int main()
{
    int n, s, x;
    int tmp;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s >> x;
        switch(s){
            case 5:
                insert(r, x);
                break;
            case 1:
                cout << Rank(r, x) + 1 << endl;
                break;
            case 2:
                tmp= Kth(r, x);
                if (exist) cout << tmp << endl;
                exist = true;
                break;
            case 3:
                cout << prev(r, x) << endl;
                break;
            case 4:
                cout << succ(r, x) << endl;
                break;
        }
    }
    return 0;
}