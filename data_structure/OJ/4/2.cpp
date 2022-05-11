#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class queue{
    int data[40400];
    int head = 0;
    int tail = 0;
public:
    void push(int x)
    {
        data[tail++] = x;
    }
    int pop()
    {
        return data[head++];
    }
    bool empty()
    {
        return (head == tail);
    }
};
int n;
int a[9];
int tree[40320 + 5][4];
int ans[40320 + 5];
bool v[40320 + 5];
int fact[9] = {1};
int p[10];
int b[10];
bool vis[10];
int cantor(int * tmp)
{
    int ans = 0;
    for (int i = 0; i < 8; i++)
        a[i] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = i + 1; j < 8; j++)
            if (tmp[j] < tmp[i])
                a[i]++;
    for (int i = 0; i < 8; i++)
    {
        ans += a[i] * fact[7 - i];
    }
    return ans;
}

int kth(int index)
{
    int pos = 0;
    for (int i = 1; i < 9; i++)
    {
        if (!vis[i]) pos++;
        if (index == pos) return i;
    }
}

void decantor(int x)
{
    for (int i = 1; i < 9; i++)
        vis[i] = false;
    for (int i = 0; i < 8; i++)
    {
        b[i] = x / fact[7 - i];
        x %= fact[7 - i];
    }
    for (int i = 0; i < 8; i++)
    {
        p[i] = kth(b[i] + 1);
        vis[p[i]] = true;
    }
}
void swap(int* x, int* y)
{
    int z = *x;
    *x = *y;
    *y = z;
}
int tran()
{
    int k[10];
    for (int i = 0; i < 10; i++)
    {
        k[i] = p[i];
    }
    for (int i = 0;  i < 4; i++)
        swap(&k[i], &k[7 - i]);
    return cantor(k);
}

int move()
{
    int k[10];
    for (int i = 0; i < 10; i++)
        k[i] = p[i];
    int x = k[0];
    int y = k[7];
    for (int i = 0; i < 3; i++)
        k[i] = k[i + 1];
    for (int i = 7; i > 4; i--)
        k[i] = k[i - 1];
    k[3] = x;
    k[4] = y;
    return cantor(k);
}

int rotate()
{
    int k[10];
    for (int i = 0; i < 10; i++)
        k[i] = p[i];
    int x = k[1];
    k[1] = k[2];
    k[2] = k[5];
    k[5] = k[6];
    k[6] = x;
    return cantor(k);
}

void bfs(int x)
{
    queue que;
    que.push(x);
    ans[x] = 0;
    v[x] = true;
    while (!que.empty())
    {
        int tmp = que.pop();
        for (int i = 0; i < 3; i++)
            {
                if (!v[tree[tmp][i]])
                {
                    que.push(tree[tmp][i]);
                    v[tree[tmp][i]] = true;
                    ans[tree[tmp][i]] = ans[tmp] + 1;
                }
            }
    }
}
int in[9];
int main()
{
    for (int i = 0; i < 7; i++)
    {
        fact[i + 1] = fact[i] * (i + 1);
    }
    for (int i = 0; i < 40320; i++)
    {
        decantor(i);
        tree[i][0] = tran();
        tree[i][1] = move();
        tree[i][2] = rotate();
    }
    // for (int i = 0; i < 40320; i++)
    //     {
    //         for (int j = 0; j < 3; j++)
    //             cout << tree[i][j] << ' ';    
    //         cout << endl;
    //     }
    for (int i = 0; i < 40320; i++)
        ans[i] = -1;
    bfs(0);
    // scanf("%d", &n);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //         scanf("%d", &in[j]);
    //     printf("%d", ans[cantor(in)]);
    //     printf("\n");
    for (int i = 0; i < 40320; i++)
        {
            printf("%d", ans[i]);
            printf(",");
            printf("\n");
        }
}