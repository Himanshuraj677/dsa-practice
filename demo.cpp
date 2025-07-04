#include<iostream>
#include<string>
using namespace std;

int main () {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    int i = 0, j = str.length() - 1;
    while (i < j) {
        swap(str[i++], str[j--]);
    }
    cout << "Reversed string: " << str << endl;
    return 0;
}