#include <iostream>
#include <fstream>
#include <vector>

int nf(int items[], int itemCount, int binCap, std::vector<int>& bins) {
    int binCount = 1;

    bins.push_back(items[0]);
    for (int i = 1; i < itemCount; i++) {
        if (bins.back() + items[i] > binCap) {
            bins.push_back(items[i]);
            binCount++;
        } else {
            bins.back() += items[i];
        }
    }
    return binCount;
}

int main() {
    std::ifstream fin("Input");
    std::ofstream fout("outputs/nf.out");

    int itemCount, binCap;
    std::vector<int> bins;
    
    fin >> itemCount >> binCap;
    int items[itemCount];

    for (int i = 0; i < itemCount; i++) {
        fin >> items[i];
    }

    fout << nf(items, itemCount, binCap, bins);

    fin.close();
    fout.close();
}