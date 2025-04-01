# Указываем путь к исходному коду
add_executable(graph_builder graph_builder.cpp)

# Линкация с математической библиотекой
target_link_libraries(graph_builder m)

# Устанавливаем папку для исполнимых файлов
set_target_properties(graph_builder PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
