// ! there is the second people (may the segment tree also works in O(n))
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int max1 = -1, max2 = -1;
    int maxpos1, maxpos2;
    int tmp;
    for (int i = 0; i < (1 << n); i++)
    {
        if (i < (1 << n) / 2)
        {
            cin >> tmp;
            if (tmp > max1)
            {
                max1 = tmp;
                maxpos1 = i + 1;
            }
        }
        else
        {
            cin >> tmp;
            if (tmp > max2)
            {
                max2 = tmp;
                maxpos2 = i + 1;
            }
        }
    }
    cout << (max1 < max2 ? maxpos1 : maxpos2);
}