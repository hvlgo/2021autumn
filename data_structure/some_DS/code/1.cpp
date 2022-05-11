// ! there is vector

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> numbers;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
    for (int i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        cout << numbers[tmp - 1] << endl;
    }
}