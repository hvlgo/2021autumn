#include <iostream>
#include<set>
using namespace std;
multiset<int>q;
int main()
{
    q.insert(-2147483647);
    q.insert(2147483647);
    int a,b,n;
    cin>>n;
    while(n--)
    {
        cin>>a>>b;
        if(a==1){
            multiset<int>::iterator it,k;
            it=q.lower_bound(b);
            k=q.begin();
            int i=0;
            for(;k!=it;k++,i++);
                cout<<i<<endl;
        }
        if(a==2){
            multiset<int>::iterator it,k;
            int cnt=0;
            for(it=q.begin();it!=q.end();it++,cnt++)
                if(cnt==b)cout<<*it<<endl;
        }
        if(a==3){
            cout<<*--q.lower_bound(b)<<endl;
        }
        if(a==4){
            cout<<*q.upper_bound(b)<<endl;
        }
        if(a==5){
            q.insert(b);
        }
    }
    return 0;
}