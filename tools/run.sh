#!/bin/bash

# Путь к корневой директории проекта
PROJECT_DIR=$(pwd)

# Папка для выходных данных
OUTPUT_DIR="$PROJECT_DIR/output"

# Создание папки для выходных данных, если она не существует
mkdir -p $OUTPUT_DIR

# Запуск C++ программы с указанием пути для сохранения файлов
echo "Запуск C++ программы:"
./build/bin/graph_builder "$OUTPUT_DIR"

# Запуск Python визуализаторов с указанием пути
echo "Запуск Python визуализаторов:"
python3 graph/graph_visualizer.py "$OUTPUT_DIR"
python3 graph/graph_visualizer_3d.py "$OUTPUT_DIR"

# Перечень файлов для копирования и удаления
FILES_TO_MOVE=("graph.png" "graph.obj" "graph.dat")

# Копирование файлов в папку output
for file in "${FILES_TO_MOVE[@]}"; do
    if [ -f "$PROJECT_DIR/$file" ]; then
        cp "$PROJECT_DIR/$file" "$OUTPUT_DIR"
        echo "Файл $file скопирован в $OUTPUT_DIR"
    else
        echo "Файл $file не найден, пропускаем..."
    fi
done

# Удаление файлов из основной директории
for file in "${FILES_TO_MOVE[@]}"; do
    if [ -f "$PROJECT_DIR/$file" ]; then
        rm "$PROJECT_DIR/$file"
        echo "Файл $file удалён из основной папки"
    else
        echo "Файл $file не найден, пропускаем удаление..."
    fi
done

echo "Все файлы были перемещены и удалены из основной папки."
