#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#define Max 10010
using namespace std;


int a[Max], b[Max], c[Max];
int main()
{
    int n;
    scanf("%d", &n);
    char sample[Max];
    scanf("%s", &sample);
    for (int i = 0; i < n; i++)
    {
        if (sample[i] == 'A') a[i] = 1;
        else if (sample[i] == 'B') b[i] = 1;
        else if (sample[i] == 'C') c[i] = 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        a[i + 1] = a[i] + a[i + 1];
        b[i + 1] = b[i] + b[i + 1];
        c[i + 1] = c[i] + c[i + 1];
    }
    for (int i = 0; i < n; i++)
    {
        if (sample[i] == 'A' && (a[n - 1] - a[i - 1] > b[n - 1] - b[i] + c[n - 1] - c[i]))
        {
            printf("False");
            return 0;
        }
        if (sample[i] == 'B' && (b[i] > a[i] + c[i]))
        {
            printf("False");
            return 0;
        }
    }
    printf("True");
    return 0;
}