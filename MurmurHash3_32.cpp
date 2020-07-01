#include <iostream>
#include <string>

using namespace std;

unsigned MurmurHash3(string key)
{
    const unsigned r1 = 15;
    const unsigned r2 = 13;

    const unsigned m = 5;
    const unsigned n = 0xe6546b64;

    const unsigned c1 = 0xcc9e2d51;
    const unsigned c2 = 0x1b873593;

    unsigned hash = 0xee6b27eb;  //这个是初始的seed，可以自己随便给，最好给个大点的质数

    unsigned len = key.size();
    const unsigned nblocks = len / 4;

    for (int i = 0; i < nblocks; ++i)
    {
        unsigned k = ((unsigned)key[4 * i] << 24) + ((unsigned)key[4 * i + 1] << 16) + ((unsigned)key[4 * i + 2] << 8) + (unsigned)key[4 * i + 3];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = (hash << r2) | (hash >> (32 - r2));
        hash = hash * m + n;
    }

    unsigned k1 = 0;

    switch (len & 3)
    {
        case 3:
            k1 ^= (unsigned)key[nblocks * 4 + 2] << 16;
        case 2:
            k1 ^= (unsigned)key[nblocks * 4 + 1] << 8;
        case 1:
            k1 ^= (unsigned)key[nblocks * 4];

            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}


int main(int argc, char* argv[])
{
    string str;
    cout << "please enter a string" << endl;
    while (cin >> str)
    {
        cout << "The hash key is : " << MurmurHash3(str) << endl;
        cout << "please enter a string" << endl;
    }
}
