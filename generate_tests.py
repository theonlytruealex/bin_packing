import os
import random

# Define folder paths and bin capacity
INPUT_FOLDER = "input/"
REF_FOLDER = "ref/"
BIN_CAPACITY = 10

# Ensure folders exist
os.makedirs(INPUT_FOLDER, exist_ok=True)
os.makedirs(REF_FOLDER, exist_ok=True)

def generate_tests_and_refs(num_tests=2000, num_items_range=(5, 100), weight_range=(1, 20)):
    for i in range(num_tests):
        # Generate input: number of items and their weights
        num_items = random.randint(*num_items_range)
        weights = [random.randint(*weight_range) for _ in range(num_items)]

        # Write input to file
        with open(f"{INPUT_FOLDER}/test_{i}.txt", "w") as input_file:
            input_file.write(f"{BIN_CAPACITY}\n")
            input_file.write(" ".join(map(str, weights)))

        # Compute reference solution using a greedy approach
        bins = []
        for weight in weights:
            placed = False
            for bin in bins:
                if sum(bin) + weight <= BIN_CAPACITY:
                    bin.append(weight)
                    placed = True
                    break
            if not placed:
                bins.append([weight])

        # Write reference solution to file
        with open(f"{REF_FOLDER}/test_{i}.txt", "w") as ref_file:
            ref_file.write(f"{len(bins)}\n")
            for bin in bins:
                ref_file.write(f"{bin}\n")

# Generate 2000 test cases
generate_tests_and_refs(num_tests=2000)