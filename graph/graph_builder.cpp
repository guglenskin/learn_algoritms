#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    char from;
    char to;
    int weight;
};

int main(int argc, char* argv[]) {
    // Проверяем, был ли передан путь к директории
    if (argc < 2) {
        cout << "Ошибка: Не указан путь для сохранения файлов." << endl;
        return 1;
    }

    string output_dir = argv[1];  // Путь к директории, переданный через аргумент командной строки
    int numVertices, numEdges;

    cout << "Введите количество вершин: ";
    cin >> numVertices;

    cout << "Введите количество рёбер: ";
    cin >> numEdges;

    vector<Edge> edges;

    cout << "Введите рёбра в формате: FROM TO WEIGHT (например: A B 2)\n";
    for (int i = 0; i < numEdges; i++) {
        char from, to;
        int weight;
        cin >> from >> to >> weight;
        edges.push_back({from, to, weight});
    }

    // Сохранение в файл в output
    string filename = output_dir + "/graph.dat";  // Путь к файлу с графом
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка при открытии файла для записи." << endl;
        return 1;
    }

    for (const auto& edge : edges) {
        file << edge.from << " " << edge.to << " " << edge.weight << "\n";
    }
    file.close();

    cout << "Граф сохранён в " << filename << "!" << endl;
    return 0;
}
