#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

int bfd(int items[], int itemCount, int binCap, int placements[]) {
    std::multiset<std::pair<int, int>> binSpaces;

    for (int i = 0; i < itemCount; i++) {
        auto bin = binSpaces.lower_bound({items[i], 0});

        if (bin == binSpaces.end()) {
            binSpaces.insert({binCap - items[i], binSpaces.size()});
            placements[i] = binSpaces.size() - 1;
        } else {
            int remainingSpace = bin->first - items[i];
            int index = bin->second;
            binSpaces.erase(bin);
            binSpaces.insert({remainingSpace, index});
            placements[i] = index;
        }
    }
    return binSpaces.size();
}

int main() {
    std::ifstream fin("Input");
    std::ofstream fout("outputs/bfd.out");

    int itemCount, binCap;
    
    fin >> itemCount >> binCap;
    int items[itemCount], placements[itemCount];

    for (int i = 0; i < itemCount; i++) {
        fin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());
    int minCount = bfd(items, itemCount, binCap, placements);
    fout << minCount << "\n";
    for (int i = 0; i < minCount; i++) {
        fout << "Bin number " << i << ": ";
        for (int j = 0; j < itemCount; j++)
            if (placements[j] == i)
                fout << items[j] << ", ";
        fout << "\n";
    }

    fin.close();
    fout.close();
}