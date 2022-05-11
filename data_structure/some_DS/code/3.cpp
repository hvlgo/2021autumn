// ! there is stack and calculate

#include <iostream>
#include <stack>
#include <cctype>
#include <string>
using namespace std;

stack<long long> numbers;

int main()
{
    string str;
    cin >> str;
    int pos = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i]))
        {
            continue;
        }
        else if (str[i] == '+')
        {
            long long first = numbers.top();
            numbers.pop();
            long long second = numbers.top();
            numbers.pop();
            long long num = first + second;
            numbers.push(num);
            pos++;
        }
        else if (str[i] == '-')
        {
            long long first = numbers.top();
            numbers.pop();
            long long second = numbers.top();
            numbers.pop();
            long long num = second - first;
            numbers.push(num);
            pos++;
        }
        else if (str[i] == '*')
        {
            long long first = numbers.top();
            numbers.pop();
            long long second = numbers.top();
            numbers.pop();
            long long num = first * second;
            numbers.push(num);
            pos++;
        }
        else if (str[i] == '/')
        {
            long long first = numbers.top();
            numbers.pop();
            long long second = numbers.top();
            numbers.pop();
            long long  num = second / first;
            numbers.push(num);
            pos++;
        }
        else if (str[i] == '.')
        {
            string number = str.substr(pos, i - pos);
            numbers.push(stoi(number));
            pos = i + 1;
        }
        else if (str[i] == '@')
        {
            cout << numbers.top();
        }
    }
}