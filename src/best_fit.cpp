#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

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
    int itemCount, binCap;
    
    cin >> itemCount >> binCap;
    int items[itemCount], placements[itemCount];

    for (int i = 0; i < itemCount; i++) {
        cin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());
    int minCount = bfd(items, itemCount, binCap, placements);
    cout << minCount << "\n";
    for (int i = 0; i < minCount; i++) {
        cout << "Bin number " << i << ": ";
        for (int j = 0; j < itemCount; j++)
            if (placements[j] == i)
                cout << items[j] << ", ";
        cout << "\n";
    }
}