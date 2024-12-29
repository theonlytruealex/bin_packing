#include <iostream>
#include <fstream>
#include <vector>

int nf(int items[], int itemCount, int binCap, std::vector<int>& bins, int placements[]) {
    bins.push_back(items[0]);
    placements[0] = 0;
    for (int i = 1; i < itemCount; i++) {
        if (bins.back() + items[i] > binCap) {
            bins.push_back(items[i]);
        } else {
            bins.back() += items[i];
        }
        placements[i] = bins.size() - 1;
    }
    return bins.size();
}

int main() {
    std::ifstream fin("Input");
    std::ofstream fout("outputs/nf.out");

    int itemCount, binCap;
    std::vector<int> bins;
    
    fin >> itemCount >> binCap;
    int items[itemCount], placements[itemCount];
    bins.reserve(itemCount);

    for (int i = 0; i < itemCount; i++) {
        fin >> items[i];
    }

    int minCount = nf(items, itemCount, binCap, bins, placements);
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