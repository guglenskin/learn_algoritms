#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Film {
    int start;
    int end;
    int id;
};

bool compareByEnd(const Film &a, const Film &b) {
    return a.end < b.end;
}

vector<Film> optimalScheduling(vector<Film> films) {
    // Сортируем фильмы по времени окончания съемок
    sort(films.begin(), films.end(), compareByEnd);
    
    vector<Film> selectedFilms;
    int lastEnd = -1;
    
    for (const auto &film : films) {
        if (film.start >= lastEnd) {
            selectedFilms.push_back(film);
            lastEnd = film.end;
        }
    }
    
    return selectedFilms;
}

int main() {
    int n;
    cout << "Введите количество фильмов: ";
    cin >> n;
    
    vector<Film> films(n);
    for (int i = 0; i < n; ++i) {
        cout << "Фильм " << i + 1 << ":\n";
        cout << "  Начало съемок: ";
        cin >> films[i].start;
        cout << "  Окончание съемок: ";
        cin >> films[i].end;
        films[i].id = i + 1;
    }
    
    vector<Film> bestSchedule = optimalScheduling(films);
    
    cout << "\nМаксимальное количество фильмов, в которых можно участвовать: " << bestSchedule.size() << endl;
    cout << "Выбранные фильмы:\n";
    for (const auto &film : bestSchedule) {
        cout << "Фильм " << film.id << ": [" << film.start << ", " << film.end << "]\n";
    }
    cout << "Общий заработок: " << bestSchedule.size() << " единиц (по 1 за каждый фильм)\n";
    
    return 0;
}