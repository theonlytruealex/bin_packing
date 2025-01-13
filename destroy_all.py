import os
import shutil
import subprocess

# Define paths
input_dir = 'input'
out_dir = 'out'
ref_dir = 'ref'
png_file = 'algorithm_performance_comparison.png'

# Function to delete the contents of a directory (including subdirectories)
def delete_contents(directory):
    for item in os.listdir(directory):
        item_path = os.path.join(directory, item)
        if os.path.isdir(item_path):
            shutil.rmtree(item_path)  # Delete subdirectories
        else:
            os.remove(item_path)  # Delete files

# 1. Delete contents from 'input/', 'out/', and 'ref/'
delete_contents(input_dir)
delete_contents(out_dir)
delete_contents(ref_dir)

# 3. Delete the image 'algorithm_performance_comparison.png'
if os.path.exists(png_file):
    os.remove(png_file)

print("Operations completed successfully!")
