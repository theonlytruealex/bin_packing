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

def generate_tests_and_refs(num_tests=1000, num_items_range=(200, 300), weight_range=(1, BIN_CAPACITY)):
    for i in range(num_tests):
        # Generate input: number of items and their weights
        num_items = random.randint(*num_items_range)
        weights = [random.randint(*weight_range) for _ in range(num_items)]

        # Write input to file
        input_file_path = f"{INPUT_FOLDER}/test_{i}.txt"  # Define input file path
        with open(input_file_path, "w") as input_file:
            input_file.write(f"{len(weights)} {BIN_CAPACITY}\n")
            input_file.write(" ".join(map(str, weights)))

        # Generate reference using the mtp executable
        ref_file_path = f"{REF_FOLDER}/test_{i}.txt"
        with open(input_file_path, "r") as input_file, open(ref_file_path, "w") as ref_file:
            try:
                subprocess.run(
                    [MTP_EXECUTABLE],
                    stdin=input_file,
                    stdout=ref_file,
                    stderr=subprocess.PIPE,
                    check=True,
                )
            except subprocess.CalledProcessError as e:
                print(f"Error running {MTP_EXECUTABLE} for {input_file_path}: {e.stderr.decode()}")

# Generate 2000 test cases
generate_tests_and_refs(num_tests=2000)
