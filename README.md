# 📋 README: Инструкция по использованию алгоритмов

<div align="center">
  <img src="https://img.shields.io/badge/Алгоритмы-2%20проекта-blue" alt="Количество алгоритмов">
  <img src="https://img.shields.io/badge/Языки-C%2FC%2B%2B-green" alt="Используемые языки">
  <img src="https://img.shields.io/badge/Сборка-GCC%20%7C%20Clang%20%7C%20CMake-orange" alt="Варианты сборки">
</div>

## 📌 Содержание
1. [Алгоритм TSP](#-1-алгоритм-ближайшего-соседа-для-задачи-коммивояжера-tsp)
2. [Планирование фильмов](#-2-алгоритм-оптимального-планирования-съемок-фильмов)
3. [Примечания](#-примечания)

---

## 🗺️ 1. Алгоритм ближайшего соседа для задачи коммивояжера (TSP)

### Описание
Алгоритм находит приближенное решение задачи коммивояжера, строя маршрут, который посещает все точки, начиная с заданной и каждый раз переходя к ближайшей непосещенной точке.

### 🛠️ Способы сборки

#### Вариант 1: Прямая компиляция (GCC/Clang)
```bash
# Сборка с GCC
gcc algoritms_1.c -o tsp -lm

# Или с Clang
clang algoritms_1.c -o tsp -lm

# Запуск
./tsp
```

#### Вариант 2: Сборка через CMake
1. Создайте файл `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.10)
project(TSP_Solver)

# Настройка компилятора
set(CMAKE_C_STANDARD 20)

# Сборка основной программы
add_executable(tsp algoritms_1.c)
target_link_libraries(tsp m)  # Для подключения математической библиотеки
```

2. Соберите проект:
```bash
mkdir build && cd build
cmake ..
make
./tsp
```

### 📋 Шаги выполнения
1. Введите количество точек
2. Для каждой точки введите координаты (x y)
3. Программа выведет:
   - Оптимальный маршрут (последовательность точек)
   - Длину полученного маршрута

### 💻 Пример работы
**Ввод:**
```
Введите количество точек: 4
Введите координаты точки A (x y): 0 0
Введите координаты точки B (x y): 1 2
Введите координаты точки C (x y): 3 1
Введите координаты точки D (x y): 2 0
```

**Вывод:**
```
Оптимальный маршрут: A → D → C → B
Длина маршрута: 6.48
```

---

## 🎬 2. Алгоритм оптимального планирования съемок фильмов

### Описание
Алгоритм выбирает максимальное количество непересекающихся по времени фильмов, что позволяет максимизировать заработок (по условию - за каждый фильм платят одинаково).

### 🛠️ Способы сборки

#### Вариант 1: Прямая компиляция (G++/Clang++)
```bash
# Сборка с G++
g++ algoritms_2.cpp -o films

# Или с Clang++
clang++ algoritms_2.cpp -o films

# Запуск
./films
```

#### Вариант 2: Сборка через CMake
1. Добавьте в `CMakeLists.txt`:
```cmake
# Сборка программы планирования фильмов
add_executable(films algoritms_2.cpp)
```

2. Пересоберите проект:
```bash
cd build
cmake ..
make
./films
```

### 📋 Шаги выполнения
1. Введите количество фильмов
2. Для каждого фильма введите:
   - Время начала съемок
   - Время окончания съемок
3. Программа выведет:
   - Максимальное количество фильмов для участия
   - Список выбранных фильмов
   - Общий заработок

### 💻 Пример работы
**Ввод:**
```
Введите количество фильмов: 3
Фильм 1:
  Начало съемок: 1
  Окончание съемок: 3
Фильм 2:
  Начало съемок: 2
  Окончание съемок: 5
Фильм 3:
  Начало съемок: 4
  Окончание съемок: 6
```

**Вывод:**
```
Максимальное количество фильмов: 2
Выбранные фильмы:
Фильм 1: [1, 3]
Фильм 3: [4, 6]
Общий заработок: 2 единиц
```

---

## 📝 Примечания

### Для TSP
- Координаты точек - действительные числа
- Решение приближенное, не обязательно оптимальное
- Для CMake требуется версия 3.10 или выше

### Для планирования фильмов
- Времена съемок - целые числа
- Окончание должно быть > начала
- Решение точное для поставленной задачи

### Общие рекомендации
1. Для CMake можно собрать оба проекта одновременно, добавив оба `add_executable` в один файл
2. Для Windows используйте MinGW или WSL для сборки
3. Для проверки версии CMake: `cmake --version`

<div align="center">
  <br>
  <img src="https://img.shields.io/badge/Удачи%20в%20использовании!-brightgreen" alt="Удачи">
</div>