#include <iostream>
/**
 * Рекурсивная функция для инкрементации натурального числа
 * 
 * @param y - натуральное число для инкрементации
 * @return увеличенное значение числа по специальным правилам
 */
int Increment(int y) {
    // Базовый случай: если y равно 0, возвращаем 1
    if (y == 0) {
        return 1;
    }
    // Рекурсивный случай: если y нечетное (остаток от деления на 2 равен 1)
    else if (y % 2 == 1) {
        // Рекурсивно вызываем Increment для y/2 и умножаем результат на 2
        return 2 * Increment(y / 2);
    }
    // Простой случай: для четных чисел просто добавляем 1
    else {
        return y + 1;
    }
}

int main() {
    // Тестирование функции Increment
    std::cout << "Increment(0) = " << Increment(0) << std::endl;   // Ожидаемый результат: 1
    std::cout << "Increment(1) = " << Increment(1) << std::endl;   // Ожидаемый результат: 2*Increment(0) = 2*1 = 2
    std::cout << "Increment(2) = " << Increment(2) << std::endl;   // Ожидаемый результат: 2 + 1 = 3
    std::cout << "Increment(3) = " << Increment(3) << std::endl;   // Ожидаемый результат: 2*Increment(1) = 2*2 = 4
    std::cout << "Increment(4) = " << Increment(4) << std::endl;   // Ожидаемый результат: 4 + 1 = 5
    std::cout << "Increment(5) = " << Increment(5) << std::endl;   // Ожидаемый результат: 2*Increment(2) = 2*3 = 6
    
    return 0;
}