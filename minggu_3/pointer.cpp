#include <iostream>
using namespace std;

int main() {
    int a = 20;
    int *almt;
    almt = &a;
    cout << almt << endl;
    cout << *almt << endl;
    return 0;
}