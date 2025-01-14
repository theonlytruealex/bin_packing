#include <iostream>

int nf(int items[], int itemCount, int binCap, int placements[]) {
    int currBin = items[0], binCount = 1;
    placements[0] = 0;
    for (int i = 1; i < itemCount; i++) {
        if (currBin+ items[i] > binCap) {
            currBin = items[i];
            binCount++;
        } else {
            currBin += items[i];
        }
        placements[i] = binCount - 1;
    }
    return binCount;
}

int main() {

    int itemCount, binCap;
    
    std::cin >> itemCount >> binCap;
    int items[itemCount], placements[itemCount];

    for (int i = 0; i < itemCount; i++) {
        std::cin >> items[i];
    }

    int minCount = nf(items, itemCount, binCap, placements);
    std::cout << minCount << "\n";
    for (int i = 0; i < minCount; i++) {
        std::cout << "Bin number " << i << ": ";
        for (int j = 0; j < itemCount; j++)
            if (placements[j] == i)
                std::cout << items[j] << ", ";
        std::cout << "\n";
    }
}