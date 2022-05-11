#include <iostream>
#include <iomanip>
using namespace std;

double val[21], t[21];

int main()
{
    for (int i = 0; i < 21; i++)
    {
        cin >> t[i];
    }
    for (int i = 0; i < 21; i++)
    {
        cin >> val[i];
    }
    double sum = 0.0;
    double t_sum = 0.0;
    for (int i = 0; i < 21; i++)
    {
        cout << fixed << setprecision(8) << t[i] * val[i] << endl;
        sum += t[i] * val[i];
        t_sum += t[i];
    }
    cout << fixed << setprecision(8) << sum << endl;
    sum /= t_sum;
    cout << fixed << setprecision(8) << t_sum << endl;
    cout << fixed << setprecision(8) << sum;
}