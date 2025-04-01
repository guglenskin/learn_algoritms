/**
 * Специализированный инкремент для нечётных чисел
 * @param y - натуральное число (y > 0)
 * @return y + 1, вычисленное особым способом для нечётных
 */
int OddIncrement(int y) {
    // Проверка на чётность
    if (y % 2 == 0) {
        return y + 1;  // Стандартный инкремент
    }
    // Рекурсивный случай для нечётных
    return 2 * OddIncrement(y / 2);
}

// Тесты
#include <cassert>
void test() {
    // Чётные числа
    assert(OddIncrement(2) == 3);
    assert(OddIncrement(4) == 5);
    
    // Нечётные числа
    assert(OddIncrement(1) == 2);
    assert(OddIncrement(3) == 4);
    assert(OddIncrement(5) == 6);
    assert(OddIncrement(7) == 8);
    
    // Граничный случай
    assert(OddIncrement(0) == 1);  // Хотя 0 не натуральное
}

#include <iostream>

int main() {

    return 0;
}