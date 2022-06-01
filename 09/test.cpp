#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cstdio>
#include <fstream>
#include "sort.hpp"

using namespace std;

void mega_test(const string &str, const string &teststr, size_t cnt) {
    ofstream fout(str, ios::binary | ios::out);
    ofstream testfout(teststr, ios::binary | ios::out);
    for (size_t i = 0; i < cnt; ++i) {
        uint64_t tmp = rand() + (1llu << 31) * rand();
        fout.write((char *) &tmp, sizeof(tmp));
        testfout.write((char *) &tmp, sizeof(tmp));
    }
}

int main() {
    srand(time(NULL));
    mega_test("f1.bin", "f2.bin", 12345678);
    ultra_sort("f1.bin", "out.bin");
    ifstream fin("f2.bin", ios::binary | ios::in);
    ifstream fout("out.bin", ios::binary | ios::in);
    vector<uint64_t> v;
    uint64_t tmp;
    while (fin.read((char *) &tmp, sizeof(tmp))) {
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    for (uint64_t i : v) {
        if (fout.read((char *) &tmp, sizeof(tmp))) {
            if (tmp != i) {
                cout << "Error: sort order failure\n";
                return 0;
            }
        } else {
            cout << "Error: Something missed!\n";
            return 0;
        }
    }
    fin.close();
    fout.close();
    remove("f1.bin");
    remove("f2.bin");
    remove("out.bin");
    cout << "OK\n";
    return 0;
}