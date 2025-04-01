#!/bin/bash

# Выход при ошибке
set -e

# Путь к корневой директории проекта
PROJECT_DIR=$(pwd)

# Создание папки для сборки
mkdir -p $PROJECT_DIR/build
mkdir -p $PROJECT_DIR/output
cd $PROJECT_DIR/build

# Запуск CMake из корневой папки
cmake ..

# Сборка проекта
make -j$(nproc)

echo "Сборка завершена. Исполнимые файлы находятся в $PROJECT_DIR/build/bin/"
