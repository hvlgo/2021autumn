#include <stdio.h>
using namespace std;
#define Max 1600005
int pop[Max];
int sck[Max];
int bottom, top;
bool op[Max * 2];
int n, m;
int pos = 0;
int ops = 0;
bool out = false;
int main()
{
    
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pop[i]);
    }
    
    for (int i = 0; i < n; i++)
    {
        if (top == m)
        {
            out = true;
            break;
        }
        sck[++top] = i + 1;
        op[ops++] = 1;
        while (sck[top] == pop[pos])
        {
            top--;
            pos++;
            op[ops++] = 0;
            if (bottom == top) break;
        }
    }
    if (out || bottom != top) printf("No");
    else if (bottom == top)
    {
        for (int i = 0; i < ops; i++)
            printf(op[i] == 1 ? "push\n" : "pop\n");
    }
}