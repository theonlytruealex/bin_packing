#include <iostream>
#include <fstream>
#include <vector>

int mtp(int items[], int binCap, std::vector<int>& bins);

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

    fout << mtp(items, binCap, bins);

    fin.close();
    fout.close();
}