# Bin Packing Problem Algorithms
Analysis of multiple algorithms to solve (or approximate) the NP-hard bin packing problem

## Compilation:
- use the Makefile ```make``` command

## Testing:
### Accuracy:
- use the run_project.py file by tying the command ```python3 run_project.py```
### Efficiency:
- use the time_generate_tests.py file by tying the command ```time_generate_tests.py```
- run each executable separatly: ```./time_next_fit.sh```, ```./time_first_fit.sh```, ```./time_best_fit.sh```

## Algorithms:

### 1. Next-fit:
- tries to fit item into last bin, if it can't it creates a new bin
- worst case 2 * optimal solution

### 2. First-fit:
- Puts new items into the first bin that can carry them
- Worst case 1.7 * optimal solution
- if items are sorted in decreasing order worst case becomes 1.5

### 3. Best fit:
- Puts items into the bin wherethey would leave the smallest remaining space
- Worst case 1.7 * optimal solution
- if items are sorted in decreasing order worst case becomes 1.5

### MTP- exact algorithm
- Sort items non-increasing size
- Explores the decition tree using a depth-first search
- Compute the lower bound of the amount of bins needed given the current arrangement of items in bins
- If the lower bound is not worse than the current solution, try the above algorithms to try to improve the current solution

### Sources

https://www.sciencedirect.com/science/article/abs/pii/S0377221716302491
https://mathopt.be/Slides_LaRoche_Martello.pdf