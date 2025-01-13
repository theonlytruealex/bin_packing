#!/bin/bash

# Definirea căilor
INPUT_DIR="input"
OUTPUT_DIR="out"
EXECUTABLES=("src/first_fit" "src/best_fit" "src/next_fit" "src/mtp")

# Creare directoare de output pentru fiecare executabil
mkdir -p "$OUTPUT_DIR"
for exe in "${EXECUTABLES[@]}"; do
    exe_name=$(basename "$exe")
    mkdir -p "$OUTPUT_DIR/$exe_name"
done

# Procesarea fiecărui fișier de input
for input_file in "$INPUT_DIR"/*; do
    input_base=$(basename "$input_file")
    
    for exe in "${EXECUTABLES[@]}"; do
        exe_name=$(basename "$exe")
        output_file="$OUTPUT_DIR/$exe_name/$input_base.out"
        
        # Rulează executabilul cu fișierul de intrare
        if [[ -x "$exe" ]]; then
            ./"$exe" < "$input_file" > "$output_file"
            echo "Procesat $input_file cu $exe_name, rezultat în $output_file"
        else
            echo "Eroare: $exe nu este executabil. Verifică compilarea!"
        fi
    done
done

echo "Toate testele au fost procesate!"
