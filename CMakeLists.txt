cmake_minimum_required(VERSION 3.10)

# Установим имя проекта
project(GraphProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем подкаталоги
add_subdirectory(src)  # Подключаем исходники C++
add_subdirectory(graph)  # Подключаем сборку graph_builder.cpp

# Устанавливаем путь для исполнимых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
