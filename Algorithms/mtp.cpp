#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

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

int bfd(int items[], int itemCount, int binCap, int currItem, std::vector<int>& bins) {
    std::multiset<int> binSpaces;

    for (auto item: bins) {
        auto bin = binSpaces.lower_bound(item);

        if (bin == binSpaces.end()) {
            binSpaces.insert(binCap - item);
        } else {
            int remainingSpace = *bin - item;
            binSpaces.erase(bin);
            binSpaces.insert(remainingSpace);
        }
    }
    for (int i = currItem; i < itemCount; i++) {
        auto bin = binSpaces.lower_bound(items[i]);

        if (bin == binSpaces.end()) {
            binSpaces.insert(binCap - items[i]);
        } else {
            int remainingSpace = *bin - items[i];
            binSpaces.erase(bin);
            binSpaces.insert(remainingSpace);
        }
    }
    return binSpaces.size();
}

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
    return binSpaces.size();
}

void mtpRecursive(int items[], int itemCount, int currItem, int binCap, std::vector<int>& bins, int& minBins) {
    if (currItem >= itemCount) {
        if (bins.size() < minBins) {
            minBins = bins.size();
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

    for (auto& bin: bins) {
        if (bin + items[currItem] == binCap) {
            bin += items[currItem];
            mtpRecursive(items, itemCount, currItem + 1, binCap, bins, minBins);
            return;
        }
        if (bin + items[currItem] < binCap) {
            bin += items[currItem];
            mtpRecursive(items, itemCount, currItem + 1, binCap, bins, minBins);
            bin -= items[currItem];
        }
    }
    bins.push_back(items[currItem]);
    mtpRecursive(items, itemCount, currItem + 1, binCap, bins, minBins);
    bins.pop_back();
}

int mtp(int items[], int itemCount, int binCap, std::vector<int>& bins) {
    int minBins = bfd(items, itemCount, binCap);
    mtpRecursive(items, itemCount, 0, binCap, bins, minBins);
    return minBins;
}

int main() {
    std::ifstream fin("Input");
    std::ofstream fout("outputs/mtp.out");

    int itemCount, binCap;
    std::vector<int> bins;
    
    fin >> itemCount >> binCap;
    int items[itemCount];

    for (int i = 0; i < itemCount; i++) {
        fin >> items[i];
    }
    std::sort(items, items + itemCount, std::greater<int>());
    fout << mtp(items, itemCount, binCap, bins);

    fin.close();
    fout.close();
}