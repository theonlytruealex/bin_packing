#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

int ffd(int items[], int itemCount, int binCap, std::vector<int>& bins) {
    int binCount = 1;
    bool found = false;

    bins.push_back(items[0]);
    for (int i = 1; i < itemCount; i++) {
        found = false;
        for (auto& bin: bins) {
            if (bin + items[i] <= binCap) {
                bin += items[i];
                found = true;
                break; 
            }
        }
        if (!found) {
            bins.push_back(items[i]);
            binCount++;
        }
    }
    
    return binCount;
}

int main() {
    std::ifstream fin("Input");
    std::ofstream fout("outputs/ffd.out");

    int itemCount, binCap;
    std::vector<int> bins;
    
    fin >> itemCount >> binCap;
    int items[itemCount];

    for (int i = 0; i < itemCount; i++) {
        fin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());
    fout << ffd(items, itemCount, binCap, bins);

    fin.close();
    fout.close();
}