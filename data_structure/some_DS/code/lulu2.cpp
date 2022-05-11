#include <iostream>
#include <iomanip>
using namespace std;

double val[5], t[5];

int main()
{
    for (int i = 0; i < 5; i++)
    {
        cin >> t[i];
    }
    for (int i = 0; i < 5; i++)
    {
        cin >> val[i];
    }
    double sum = 0.0;
    double t_sum = 0.0;
    for (int i = 0; i < 5; i++)
    {
        cout << fixed << setprecision(8) << t[i] * val[i] << endl;
        sum += t[i] * val[i];
        t_sum += t[i];
    }
    cout << fixed << setprecision(8) << sum << endl;
    sum *= 0.002;
    cout << fixed << setprecision(8) << t_sum << endl;
    cout << fixed << setprecision(8) << sum;
}