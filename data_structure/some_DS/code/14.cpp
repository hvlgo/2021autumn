// ! there is BST trealing(reconstuct)

#include <iostream>
#include <string>
using namespace std;

void work(string second, string first)
{
    if (first.empty()) return;
    char root = first[0];
    int k = second.find(root);
    first.erase(first.begin());
    string second_left = second.substr(0, k);
    string second_right = second.substr(k + 1);
    string first_left = first.substr(0, k);
    string first_right = first.substr(k);
    work(second_left, first_left);
    work(second_right, first_right);
    cout << root;
}
int main()
{
    string first, second;
    cin >> second >> first;
    work(second, first);
    return 0;
}