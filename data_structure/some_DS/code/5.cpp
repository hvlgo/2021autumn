// ! there is link list

#include <iostream>
#include <list>
using namespace std;
using Iter = std::list<int>::iterator;

const int Max = 100005;
list<int> link;
Iter pos[Max];
int n, m;
bool erased[Max];
void build()
{
    link.push_front(1);
    pos[1] = link.begin();
    for (int i = 2; i <= n; i++)
    {
        int k, p;
        cin >> k >> p;
        if (p == 0)
        {
            pos[i] = link.insert(pos[k], i);
        }
        else
        {
            pos[i] = link.insert(next(pos[k]), i);
        }
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        if (!erased[x])
        {
            erased[x] = true;
            link.erase(pos[x]);
        }
    }
}
int main()
{
    cin >> n;
    build();
    for (auto i : link)
    {
        cout << i << ' ';
    }
}