// ! there is basic BST

#include <iostream>
#define Max 1000050
using namespace std;

struct node{
    int left;
    int right;
}tree[Max];
int ans;

void dfs(int id, int deep)
{
    if (id == 0) return;
    ans = max(ans, deep);
    dfs(tree[id].left, deep + 1);
    dfs(tree[id].right, deep + 1);
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> tree[i].left >> tree[i].right;
    }
    dfs(1, 1);
    cout << ans;
}