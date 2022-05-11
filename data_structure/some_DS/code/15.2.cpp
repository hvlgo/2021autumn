#include <iostream>
#define maxn 100000
using namespace std;

struct node
{
    int val,pri,size,lson,rson;//val键值，pri优先级，size子树大小。
}tree[maxn];
int tot;
void L_rotate(int &pos)
{
    node x=tree[tree[pos].rson];//x表示要转到上面的节点
    tree[pos].rson=x.lson;
    x.lson=pos;
    x.size=tree[pos].size;
    maintain(pos);
    tree[pos]=x;
}
void R_rotate(int &pos)
{
    node x=tree[tree[pos].lson];
    tree[pos].lson=x.rson;
    x.size=tree[pos].size;
    maintain(pos);
    tree[pos]=x;
}
void maintain(int pos)
{
    tree[pos].size=tree[tree[pos].lson].size+tree[tree[pos].rson].size+1;
}
void insert(int &pos,int x)
{
    if(!pos)
    {
        pos=++tot;
        tree[pos].val=x;
        tree[pos].pri=rand();
    }
    if(x<tree[pos].val)
    {
        insert(tree[pos].lson,x);
        if(tree[pos].pri<tree[lson].pri)//如果优先级不匹配，就旋转(这里维护的是大根堆)
            R_rotate(pos);
    }
    else
    {
        insert(tree[pos].rson,x);
        if(tree[pos].pri<tree[rson].pri)
            L_rotate(pos);
    }
    maintain(pos);
}
void remove(int &pos,int x)
{
    if(!pos)
        return;
    if(x==tree[pos].val)
    {
        if(tree[pos].lson|tree[pos].rson)//如果非叶子节点
        {
            if(tree[tree[pos].lson].pri>tree[tree[pos].rson].pri)
                R_rotate(pos),remove(tree[pos].lson,x);
            else
                L_rotate(pos),remove(tree[pos].rson,x);
            maintain(pos);
        }
        else
            pos=0;
    }
    else
    {
        if(x<tree[pos].val)
            remove(tree[pos].lson,x);
        else
            remove(tree[pos].rson,x);
    }
    if(pos)
        maintain(pos);
}

int rank(int pos,int x)
{
    if(!pos)
        return 1;
    if(x<tree[pos].val)
        return rank(tree[pos].lson,x);
    else
        return rank(tree[pos].rson,x)+tree[tree[pos].lson].size+1;
}
int rank(int pos,int x,int &cnt)
{
    if(!pos)
        return -1;
    if(x==tree[pos].val)
        return cnt+=tree[tree[pos].lson].size;
    else
    {
        if(x<tree[pos].val)
            rank(tree[pos].lson,x,cnt);
        else
            cnt+=(tree[tree[pos].lson].size+1),rank(tree[pos].rson,x,cnt);
    }
}

int kth(int pos,int k)
{
    if(!pos || k<=0 || k>tree[pos].size)
        return -1;
    if(k==tree[tree[pos].lson].size+1)
        return tree[pos].val;
    else if(k<=tree[tree[pos].lson].size)
        return kth(tree[pos].lson,k);
    else
        return kth(tree[pos].rson,k-tree[tree[pos].lson].size-1);
}

int prev(int pos,int x)
{
    if(!pos)
        return -INF;
    if(x<tree[pos].val)
        return prev(tree[pos].lson,x);
    else
        return max(tree[pos].val,prev(tree[pos].rson,x));
}
int nxt(int pos,int x)
{
    if(!pos)
        return INF;
    if(x>=tree[pos].val)
        return nxt(tree[pos].rson,x);
    else
        return min(tree[pos].val,nxt(tree[pos].lson,x));
}