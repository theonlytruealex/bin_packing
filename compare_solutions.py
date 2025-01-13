import os
import matplotlib.pyplot as plt
import numpy as np

# Directory paths
REF_DIR = "out/mtp"
OUT_DIR = "out"
EXECUTABLES = ["first_fit", "best_fit", "next_fit", "mtp"]

# Function to read the number of bins from a file (first line)
def get_bin_count(file_path):
    try:
        with open(file_path, "r") as file:
            return int(file.readline().strip())  # Read and return the first line (number of bins)
    except Exception as e:
        return None

# Dictionary to store results for each algorithm
results = {exe: [] for exe in EXECUTABLES}
ref_values = []  # List to store reference values (from ref/test_X.txt)

# Iterate over all the test files in the 'ref' directory
for test_file in os.listdir(REF_DIR):
    if test_file.endswith(".txt"):  # Only process .txt files
        # Get the path of the reference file
        ref_file_path = os.path.join(REF_DIR, test_file)
        ref_value = get_bin_count(ref_file_path)  # Get the number of bins from the reference
        if ref_value is not None:
            ref_values.append(ref_value)

            # Iterate over the output files for each algorithm
            for exe in EXECUTABLES:
                output_file = os.path.join(OUT_DIR, exe, test_file + ".out")  # Append .out to match the filenames
                if os.path.exists(output_file):  # Check if the output file exists
                    output_value = get_bin_count(output_file)  # Get the number of bins used by the algorithm
                    if output_value is not None:
                        results[exe].append(output_value)

# Analyze the performance percentage for each algorithm
performance = {exe: [] for exe in EXECUTABLES}
for exe, values in results.items():
    for i, value in enumerate(values):
        ref_value = ref_values[i]
        if ref_value > 0:  # Avoid division by zero
            percentage_diff = (value - ref_value) / ref_value * 100
            performance[exe].append(percentage_diff)

# Calculate the best, worst, and middle solutions (percentages)
best = {}
worst = {}
middle = {}

for exe, percents in performance.items():
    if percents:  # Only calculate if the list is non-empty
        best[exe] = min(percents)  # Best performance (minimum percentage)
        worst[exe] = max(percents)  # Worst performance (maximum percentage)
        middle[exe] = np.median(percents)  # Middle performance (median percentage)

# Print the results
print("\nAlgorithm Performance (percentage difference from reference):")
for exe in EXECUTABLES:
    if exe in best:
        print(f"\nAlgorithm {exe}:")
        print(f"  - Best performance: {best[exe]:.2f}%")
        print(f"  - Worst performance: {worst[exe]:.2f}%")
        print(f"  - Middle performance: {middle[exe]:.2f}%")
    else:
        print(f"\nAlgorithm {exe}: No data available.")

# Create a plot to visualize the performance of each algorithm
fig, ax = plt.subplots(figsize=(10, 6))  # Create a figure and axis for the plot

# Plot the performance of each algorithm
for exe in EXECUTABLES:
    if exe in performance:
        ax.plot(performance[exe], label=f"{exe}", marker='o')  # Plot each algorithm's performance

# Labeling the axes and the plot
ax.set_xlabel("Test cases")  # X-axis label
ax.set_ylabel("Percentage difference from reference (%)")  # Y-axis label
ax.set_title("Algorithm Performance Comparison")  # Plot title
ax.legend()  # Display legend
plt.grid(True)  # Enable grid for better readability
# Save the plot to a file
plt.savefig("algorithm_performance_comparison.png", dpi=300)
print("Plot saved as 'algorithm_performance_comparison.png'.")
