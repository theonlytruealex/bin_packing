#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

int bfd(int items[], int itemCount, int binCap) {
    std::multiset<int> binSpaces;

    for (int i = 0; i < itemCount; i++) {
        auto bin = binSpaces.lower_bound(items[i]);

        if (bin == binSpaces.end()) {
            binSpaces.insert(binCap - items[i]);
        } else {
            int remainingSpace = *bin - items[i];
            binSpaces.erase(bin);
            binSpaces.insert(remainingSpace);
        }
    }

    for (auto bin: binSpaces) {
        std::cout << 100 - bin << " ";
    }
    std::cout << "\n";

    return binSpaces.size();
}

int main() {
    std::ifstream fin("Input");
    std::ofstream fout("outputs/bfd.out");

    int itemCount, binCap;
    
    fin >> itemCount >> binCap;
    int items[itemCount];

    for (int i = 0; i < itemCount; i++) {
        fin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());
    fout << bfd(items, itemCount, binCap);

    fin.close();
    fout.close();
}