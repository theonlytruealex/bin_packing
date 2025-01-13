#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int lowerBound(std::vector<int>& bins, int items[], int currItem, int itemCount, int binCap) {
    int alpha = items[itemCount - 1];
    int sJ3 = 0, sJ2 = 0, j1 = 0, j2 = 0;

    for (auto bin: bins) {
        if (bin + alpha > binCap) {
            j1++;
        } else if (bin > binCap / 2) {
            j2++;
            sJ2 += bin;
        } else {
            sJ3 += bin;
        }
    }

    for (int i = currItem; i < itemCount; i++) {
        if (items[i] + alpha > binCap) {
            j1++;
        } else if (items[i] > binCap / 2) {
            j2++;
            sJ2 += items[i];
        } else {
            sJ3 += items[i];
        }
    }
    int fraction = sJ3 - j2 * binCap + sJ2;

    fraction = fraction % binCap == 0 ? fraction / binCap : fraction / binCap + 1;
    return j1 + j2 + std::max(0, fraction);
}

int bfd(int items[], int itemCount, int binCap, int currItem, std::vector<int>& bins, int placements[][2]) {
    std::multiset<std::pair<int, int>> binSpaces;

    for (size_t i = 0; i < bins.size(); i++) {
        auto bin = binSpaces.lower_bound({bins[i], 0});

        if (bin == binSpaces.end()) {
            binSpaces.insert({binCap - bins[i], binSpaces.size()});
        } else {
            int remainingSpace = bin->first - bins[i];
            int index = bin->second;
            binSpaces.erase(bin);
            binSpaces.insert({remainingSpace, index});
        }
    }
    for (int i = currItem; i < itemCount; i++) {
        auto bin = binSpaces.lower_bound({items[i], 0});

        if (bin == binSpaces.end()) {
            binSpaces.insert({binCap - items[i], binSpaces.size()});
            placements[i][1] = binSpaces.size() - 1;
        } else {
            int remainingSpace = bin->first - items[i];
            int index = bin->second;
            binSpaces.erase(bin);
            binSpaces.insert({remainingSpace, index});
            placements[i][1] = index;
        }
    }
    return binSpaces.size();
}

int bfd(int items[], int itemCount, int binCap, int placements[][2]) {
    std::multiset<std::pair<int, int>> binSpaces;

    for (int i = 0; i < itemCount; i++) {
        auto bin = binSpaces.lower_bound({items[i], 0});

        if (bin == binSpaces.end()) {
            binSpaces.insert({binCap - items[i], binSpaces.size()});
            placements[i][0] = binSpaces.size() - 1;
        } else {
            int remainingSpace = bin->first - items[i];
            int index = bin->second;
            binSpaces.erase(bin);
            binSpaces.insert({remainingSpace, index});
            placements[i][0] = index;
        }
    }
    return binSpaces.size();
}


void mtpRecursive(int items[], int placements[][2], int itemCount, int currItem, int binCap, std::vector<int>& bins, int& minBins) {
    if (currItem >= itemCount) {
        if (bins.size() < minBins) {
            minBins = bins.size();
            for (int i = 0; i < itemCount; i++)
                placements[i][0] = placements[i][1];
        }
        return;
    }
    if (bins.size() >= minBins) {
        return;
    }
    int lowerB = lowerBound(bins, items, currItem, itemCount, binCap);
    if (lowerB >= minBins) {
        return;
    }

    int bfdSize = bfd(items, itemCount, binCap, currItem, bins, placements);
    if (bfdSize < minBins) {
        minBins = bfdSize;
        for (int i = 0; i < itemCount; i++)
                placements[i][0] = placements[i][1];
    }

    for (int i = 0; i < bins.size(); i++) {
        if (bins[i] + items[currItem] == binCap) {
            bins[i] += items[currItem];
            placements[currItem][1] = i;
            mtpRecursive(items, placements, itemCount, currItem + 1, binCap, bins, minBins);
            return;
        }
        if (bins[i] + items[currItem] < binCap) {
            bins[i] += items[currItem];
            placements[currItem][1] = i;
            mtpRecursive(items, placements, itemCount, currItem + 1, binCap, bins, minBins);
            bins[i] -= items[currItem];
        }
    }
    bins.push_back(items[currItem]);
    placements[currItem][1] = bins.size() - 1;
    mtpRecursive(items, placements, itemCount, currItem + 1, binCap, bins, minBins);
    bins.pop_back();
}

int mtp(int items[], int itemCount, int binCap, std::vector<int>& bins, int placements[][2]) {
    int minBins = bfd(items, itemCount, binCap, placements);
    mtpRecursive(items, placements, itemCount, 0, binCap, bins, minBins);
    return minBins;
}

int main() {
    int itemCount, binCap;
    std::vector<int> bins;
    
    cin >> itemCount >> binCap;
    int items[itemCount], placements[itemCount][2];
    bins.reserve(itemCount);

    for (int i = 0; i < itemCount; i++) {
        cin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());

    int minCount = mtp(items, itemCount, binCap, bins, placements);
    cout << minCount << "\n";
    for (int i = 0; i < minCount; i++) {
        cout << "Bin number " << i << ": ";
        for (int j = 0; j < itemCount; j++)
            if (placements[j][0] == i)
                cout << items[j] << ", ";
        cout << "\n";
    }
}