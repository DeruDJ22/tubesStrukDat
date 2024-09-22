#include <iostream>
using namespace std;
int main() {
    int bill[10];
    bill[0] = 1;
    bill[1] = 4;
    bill[2] = 5;
    cout << bill[0] << endl;
    cout << bill[1] << endl;
    cout << bill[2] << endl;
    cout << bill[0] + bill[1] + bill[2] << endl;
    return 0;
}