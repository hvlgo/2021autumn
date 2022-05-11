// ! there is segment tree

#include <iostream>
using namespace std;

const int N = 100;
int n, m;
struct Stree
{
    int l, r;
    int data;
}t[N << 2];

void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r;
    if (l == r)
    {
        t[p].data = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    t[p].data = t[p << 1].data + t[p << 1 | 1].data;
}

void change(int p, int x) // * x is pos number of the section
{
    if (t[p].l == t[p].r)
    {
        t[p].data = 0;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if (x <= mid)
    {
        change(p << 1, x);
    }
    else
    {
        change(p << 1 | 1, x);
    }
    t[p].data = t[p<<1].data + t[p<<1|1].data;
}

int query(int p, int x) // * return the pos number of the section of the x nd
{
    if (t[p].l == t[p].r)
    {
        return t[p].l;
    }
    if (x > t[p << 1].data) return query(p << 1 | 1, x - t[p << 1].data);
    else return query(p << 1, x);
}
int main()
{
    cin >> n >> m;
	if(n==0) return 0;
	build(1,1,n);
	int pos=1;
	while(n)
	{
		pos=(pos+m-2)%t[1].data+1;//t[1].dat即剩余总人数 
		int qwq=query(1,pos);
		cout<<qwq<<" ";
		change(1,qwq);
		n--;
	}
	
	return 0;
}