#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int ffd(int items[], int itemCount, int binCap, std::vector<int>& bins, int placements[]) {
    int binCount = 1;
    bool found = false;

    bins.push_back(items[0]);
    placements[0] = 0;
    for (int i = 1; i < itemCount; i++) {
        found = false;
        for (auto& bin: bins) {
            if (bin + items[i] <= binCap) {
                bin += items[i];
                placements[i] = &bin - &bins[0];
                found = true;
                break;
            }
        }
        if (!found) {
            bins.push_back(items[i]);
            placements[i] = binCount;
            binCount++;
        }
    }
    
    return binCount;
}

int main() {

    int itemCount, binCap;
    std::vector<int> bins;
    
    cin >> itemCount >> binCap;
    int items[itemCount], placements[itemCount];
    bins.reserve(itemCount);

    for (int i = 0; i < itemCount; i++) {
        cin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());
    int minCount = ffd(items, itemCount, binCap, bins, placements);
    cout << minCount << "\n";
    for (int i = 0; i < minCount; i++) {
        cout << "Bin number " << i << ": ";
        for (int j = 0; j < itemCount; j++)
            if (placements[j] == i)
                cout << items[j] << ", ";
        cout << "\n";
    }
}