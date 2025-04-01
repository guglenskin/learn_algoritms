#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>


using namespace std;

// Структура для хранения информации о фильме
struct Film {
    int id;          // Номер фильма
    int start;       // Месяц начала съемок
    int end;         // Месяц окончания съемок
    int payment;     // Общая оплата за фильм
    
    // Оператор сравнения для работы с std::find
    bool operator==(const Film& other) const {
        return id == other.id && start == other.start && 
               end == other.end && payment == other.payment;
    }
};

// Функция для сравнения фильмов по дате окончания
bool compareByEnd(const Film &a, const Film &b) {
    return a.end < b.end;
}

// Функция выбора оптимального набора фильмов
vector<Film> selectFilms(vector<Film> films) {
    // Сортируем фильмы по дате окончания
    sort(films.begin(), films.end(), compareByEnd);
    
    vector<Film> selected; // Выбранные фильмы
    int lastEnd = -1;      // Окончание последнего выбранного фильма
    
    for (const auto &film : films) {
        // Если фильм начинается после окончания предыдущего
        if (film.start >= lastEnd) {
            selected.push_back(film);
            lastEnd = film.end;
        }
    }
    
    return selected;
}
#if 0
// Генерация графика расписания в формате PNG
void generateScheduleGraph(const vector<Film>& films, const vector<Film>& selected) {
    // Создаем скрипт для GNUPlot
    ofstream script("schedule.gnu");
    
    script << "set terminal pngcairo size 1200,600 enhanced font 'Arial,12'\n";
    script << "set output 'schedule.png'\n";
    script << "set title 'График съемок фильмов'\n";
    script << "set xlabel 'Месяцы'\n";
    script << "set ylabel 'Фильмы'\n";
    script << "set style fill solid 0.7\n";
    script << "set key outside\n";
    script << "set grid\n";
    script << "set ytics (";
    
    // Добавляем подписи для каждого фильма
    for (size_t i = 0; i < films.size(); ++i) {
        script << "'" << films[i].id << "' " << i+1;
        if (i != films.size()-1) script << ", ";
    }
    script << ")\n";
    
    // Настройки отображения
    script << "plot '-' using 1:2:3:4:5:6:ytic(6) with boxxyerrorbars title 'Все фильмы' lc rgb 'red',\\\n";
    script << "'-' using 1:2:3:4:5:6:ytic(6) with boxxyerrorbars title 'Выбранные' lc rgb 'green'\n";
    
    // Данные для всех фильмов
    for (const auto &f : films) {
        int ypos = &f - &films[0] + 1;
        script << f.start << " " << ypos-0.4 << " " << f.end << " " << ypos+0.4 << " " << ypos << " " << f.id << "\n";
    }
    script << "e\n";


    // Данные для выбранных фильмов
    for (const auto &f : selected) {
        auto it = find(films.begin(), films.end(), f);
        int ypos = distance(films.begin(), it) + 1;
        script << f.start << " " << ypos-0.4 << " " << f.end << " " << ypos+0.4 << " " << ypos << " " << f.id << "\n";
    }
    script << "e\n";
    
    script.close();
    
    // Вызываем GNUPlot для создания графика
    system("gnuplot schedule.gnu");
}

// Генерация графика выплат в формате PNG
void generatePaymentGraph(const map<int, int>& monthly_income) {
    // Сохраняем данные о выплатах
    ofstream data("payment.dat");
    for (const auto &[month, income] : monthly_income) {
        data << month << " " << income << "\n";
    }
    data.close();
    
    // Создаем скрипт для GNUPlot
    ofstream script("payment.gnu");
    script << "set terminal pngcairo size 800,400 enhanced font 'Arial,12'\n";
    script << "set output 'payment.png'\n";
    script << "set title 'График выплат по месяцам'\n";
    script << "set xlabel 'Месяц'\n";
    script << "set ylabel 'Заработок'\n";
    script << "set style data histogram\n";
    script << "set style histogram cluster gap 1\n";
    script << "set style fill solid 0.7\n";
    script << "set grid\n";
    script << "plot 'payment.dat' using 2:xtic(1) title 'Доход' lc rgb 'blue'\n";
    script.close();
    
    // Вызываем GNUPlot для создания графика
    system("gnuplot payment.gnu");
}
#endif

int main() {
    // Ввод данных
    int n;
    cout << "Введите количество фильмов: ";
    cin >> n;
    
    vector<Film> films(n);
    for (int i = 0; i < n; ++i) {
        films[i].id = i + 1;
        cout << "\nФильм " << films[i].id << ":\n";
        cout << "  Месяц начала съемок: ";
        cin >> films[i].start;
        cout << "  Месяц окончания съемок: ";
        cin >> films[i].end;
        cout << "  Оплата за фильм: ";
        cin >> films[i].payment;
    }
    
    // Выбор оптимальных фильмов
    vector<Film> selected = selectFilms(films);
    
    // Вывод результатов
    cout << "\nОптимальный выбор фильмов:\n";
    int total = 0;
    for (const auto &f : selected) {
        cout << "Фильм " << f.id << ": [" << f.start << "-" << f.end 
             << "], оплата: " << f.payment << "\n";
        total += f.payment;
    }
    cout << "\nОбщий заработок: " << total << "\n";
    
    // Расчет выплат по месяцам
    map<int, int> monthly_income;
    for (const auto &f : selected) {
        int duration = f.end - f.start;
        if (duration == 0) duration = 1;
        int monthly_payment = f.payment / duration;
        
        for (int month = f.start; month < f.end; month++) {
            monthly_income[month] += monthly_payment;
        }
    }
    #if 0
    // Генерация графиков
    generateScheduleGraph(films, selected);
    generatePaymentGraph(monthly_income);
    
    cout << "\nГрафики сохранены в файлы:\n";
    cout << "- schedule.png (график съемок)\n";
    cout << "- payment.png (график выплат)\n";
    
    // Для WSL: открываем проводник Windows с текущей директорией
    system("explorer.exe .");
    
    #endif
    return 0;
}