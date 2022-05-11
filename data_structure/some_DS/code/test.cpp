#include <iostream>
#include <stdlib.h>
#include <algorithm>

using  namespace std;

#define INF INT_MAX

const int N=1e5+10;

int n,a,x,tot[N],siz[N],rd[N],v[N],son[N][2],d,r,sum;

void pushup(int x)
{
	siz[x]=siz[son[x][0]]+siz[son[x][1]]+tot[x];
	return;
}

void xun(int &p,int d)
{
	int k=son[p][d^1];
	son[p][d^1]=son[k][d];
	son[k][d]=p;
	pushup(p);
	pushup(k);
	p=k;
	return;
}

void cha(int &p,int x)
{
	if(p==0)
	{
		p=++sum;
		siz[p]=tot[p]=1;
		v[p]=x;
		rd[p]=rand();
		return;
	}
	if(v[p]==x)
	{
		siz[p]++;
		tot[p]++;
		return ;
	 } 
	int d=(x>v[p]);
	cha(son[p][d],x);
	if(rd[p]<rd[son[p][d]])
       xun(p,d^1);
	pushup(p);	
}

void shan(int &p,int x)
{
	if(!p) return;
	if(x<v[p]) shan(son[p][0],x);
	else if(x>v[p]) shan(son[p][1],x);
	else
	{
		if(son[p][0]==0&&son[p][1]==0)
		{
			tot[p]--;
			siz[p]--;
			if(tot[p]==0) p=0;
		}
		else
		{
			if(son[p][1]==0)
			{
				xun(p,1);
				shan(son[p][1],x);
			}
			else
			{
				if(son[p][0]==0)
				{
					xun(p,0);
					shan(son[p][0],x);
				}
				else
				{
				   int d=(rd[son[p][0]]>rd[son[p][1]]);
				   xun(p,d);
				   shan(son[p][d],x);
				}
			}
		}
	}
	pushup(p);
}

int pai(int p,int x)
{
	if(!p)return 0;
	if(v[p]==x) return siz[son[p][0]]+1;
	if(v[p]<x) return siz[son[p][0]]+tot[p]+pai(son[p][1],x);
	if(v[p]>x) return pai(son[p][0],x);
}

int ming(int p,int x)
{
	if(!p)return 0;
	if(x<=siz[son[p][0]]) return ming(son[p][0],x);
	else if(x>siz[son[p][0]]+tot[p])
	  return ming(son[p][1],x-siz[son[p][0]]-tot[p]);
	else return v[p];
}

int qian(int p,int x)
{
	if(!p)return -2147483647;
	if(x<=v[p]) return qian(son[p][0],x);
	else return max(v[p],qian(son[p][1],x));
  }  

int hou(int p,int x)
{
	if(!p)return 2147483647;
	if(x>=v[p]) return hou(son[p][1],x);
	else return min(v[p],hou(son[p][0],x));
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>x;
		if(a==5)
		{
			cha(r,x);
		}
		if(a==1)
		{
			cout<<pai(r,x)<<endl;
		}
		if(a==2)
		{
			cout<<ming(r,x)<<endl;
		}
		if(a==3)
		{
			cout<<qian(r,x)<<endl;
		}
		if(a==4)
		{
			cout<<hou(r,x)<<endl;
		}
	}
	return 0;
}