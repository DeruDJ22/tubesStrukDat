#include "kerucut.h"

void input_kerucut(kerucut &K) {
    cout << "Masukkan nilai tinggi kerucut: ";
    cin >> (K).tinggi;
    cout << "Masukkan nilai radius kerucut: ";
    cin >> (K).radius;
}

float volume_kerucut(kerucut K) {
    return ((3.14 * K.radius * K.radius * K.tinggi) / 3);
}