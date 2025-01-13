import subprocess

# Define paths to the scripts and make directory
src_dir = 'src'
generate_tests_script = 'generate_tests.py'
run_tests_script = 'run_tests.sh'
compare_solutions_script = 'compare_solutions.py'

# 1. Run 'make' in the 'src/' directory
print("Running 'make' in the 'src/' directory...")
subprocess.run(['make'], cwd=src_dir)

# 2. Run the 'generate_tests.py' Python script
print("Running 'generate_tests.py'...")
subprocess.run(['python', generate_tests_script])

# 3. Run the 'run_tests.sh' shell script
print("Running 'run_tests.sh'...")
subprocess.run(['bash', run_tests_script])

# 4. Run the 'compare_solutions.py' Python script
print("Running 'compare_solutions.py'...")
subprocess.run(['python', compare_solutions_script])

print("Operations completed successfully!")
