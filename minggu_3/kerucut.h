#ifndef KERUCUT_H_INCLUDED
#define KERUCUT_H_INCLUDED
#include <iostream>

using namespace std;

struct kerucut
{
    float radius;
    float tinggi;
};

void input_kerucut(kerucut &K);
float volume_kerucut(kerucut K);
#endif // KERUCUT_H_INCLUDED