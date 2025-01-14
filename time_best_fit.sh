#!/bin/bash

START_TIME=$(date +%s)

# Definirea căilor
INPUT_DIR="input_time"
OUTPUT_DIR="out"
EXECUTABLE="src/best_fit"

# Creare directoare de output pentru fiecare executabil
mkdir -p "$OUTPUT_DIR"

exe_name=$(basename "$EXECUTABLE")
mkdir -p "$OUTPUT_DIR/$exe_name"

# Procesarea fiecărui fișier de input
for input_file in "$INPUT_DIR"/*; do
    input_base=$(basename "$input_file")
    

    exe_name=$(basename "$EXECUTABLE")
    output_file="$OUTPUT_DIR/$exe_name/$input_base.out"
 
    # Rulează executabilul cu fișierul de intrare
    if [[ -x "$EXECUTABLE" ]]; then
        ./"$EXECUTABLE" < "$input_file" > /dev/null
    else
        echo "Eroare: $EXECUTABLE nu este executabil. Verifică compilarea!"
    fi
done

END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))
echo "Timpul total de execuție: $ELAPSED_TIME secunde"
