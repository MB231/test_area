#include <iostream>

using namespace std;
int main()
{
    int test = 12;
    int* ptr = &test;
    cout << "test:" << test << endl;
    cout << "&test:" << &test << endl;
    cout << "ptr:" << ptr << endl;
    cout << "*ptr:" << *ptr << endl;
    cout << "&ptr:" << &ptr << endl;

    return 0;
}
