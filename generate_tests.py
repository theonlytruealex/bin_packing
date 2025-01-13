import os
import random
import subprocess

# Define folder paths and bin capacity
INPUT_FOLDER = "input/"
REF_FOLDER = "ref/"

BIN_CAPACITY = 500
MTP_EXECUTABLE = "src/mtp"

# Ensure folders exist
os.makedirs(INPUT_FOLDER, exist_ok=True)
os.makedirs(REF_FOLDER, exist_ok=True)

def generate_tests_and_refs(num_tests=1000, num_items_range=(50, 55), weight_range=(1, BIN_CAPACITY)):
    for i in range(num_tests):
        print(i)
        # Generate input: number of items and their weights
        num_items = random.randint(*num_items_range)
        weights = [random.randint(*weight_range) for _ in range(num_items)]

        # Write input to file
        input_file_path = f"{INPUT_FOLDER}/test_{i}.txt"  # Define input file path
        with open(input_file_path, "w") as input_file:
            input_file.write(f"{len(weights)} {BIN_CAPACITY}\n")
            input_file.write(" ".join(map(str, weights)))


# Generate 2000 test cases
generate_tests_and_refs()
