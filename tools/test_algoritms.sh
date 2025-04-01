#!/bin/bash

# Путь к выходной папке
OUTPUT_DIR="$PROJECT_DIR/output"

# Запуск C++ программы с указанием пути для сохранения файлов
echo "Запуск C++ программы:"
./build/bin/algoritms_1 "$OUTPUT_DIR"
./build/bin/algoritms_2 "$OUTPUT_DIR"
./build/bin/algoritms_3 "$OUTPUT_DIR"
./build/bin/algorims_4 "$OUTPUT_DIR"