#include <stdio.h>
#define Max 4000005
int n;
long long ans;
struct node
{
    int x;
    int y;
};
node t[Max];

void qsort(int l, int r)
{
    if (l >= r)
        return;

    int x = l, y = r;

    node k = t[l];
    do
    {
        while (l < r && t[r].x <= k.x) r--;
        if (l < r) t[l++] = t[r];
        while (l < r && t[l].x > k.x) l++;
        if (l < r) t[r--] = t[l];
    } while (l != r);
    t[l] = k;

    qsort(x, l - 1);
    qsort(l + 1, y);
}

void merge (int lo, int mi, int hi)
{
    node * tmp = new node[hi - lo];
    int left_idx = lo, right_idx = mi, i = 0;
    while (left_idx < mi && right_idx < hi)
    {
        if (t[left_idx].y < t[right_idx].y)
            tmp[i++] = t[left_idx++];
        else
        {
            tmp[i++] = t[right_idx++];
            ans += mi - left_idx;
        }
    }
    while (left_idx < mi)  tmp[i++] = t[left_idx++];
    while (right_idx < hi) tmp[i++] = t[right_idx++];
    for (int i = 0, idx = lo; i < hi - lo; i++, idx++)
    {
        t[idx] = tmp[i];
    }
    delete [] tmp; 
}
// void merge2(int lo, int mi, int hi)
// {   
//     int lb = mi - lo;
//     node* B = new node[lb];
//     for (int i = 0; i < lb; i++)
//         B[i] = t[i + lo];
//     int lc = hi - mi; node* C = t + mi;
//     for (int i = lo, j = 0, k = 0; (j < lb)||(k < lc);) {
//         if ( ( j < lb ) && ( ! ( k < lc ) || ( B[j].y <= C[k].y ) ) ) t[i++] = B[j++];
//         if ( ( k < lc ) && ( ! ( j < lb ) || ( C[k].y <  B[j].y ) ) ) t[i++] = C[k++], ans += mi - j - lo;
//     }
//     delete [] B; 
// } 

void mergeSort(int lo, int hi)
{
    if (hi - lo < 2) return;
    int mi = (lo + hi)/2;
    mergeSort(lo, mi), mergeSort(mi, hi);
    merge(lo, mi, hi);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t[i].x);
        scanf("%d", &t[i].y);
    }
    qsort(0, n - 1);
    mergeSort(0, n);
    printf("%lld", ans);
}