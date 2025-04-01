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

int main() {
    std::string output_dir = "../output/";
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
    std::ofstream file(output_dir + "graph.dat");
    for (const auto& edge : edges) {
        file << edge.from << " " << edge.to << " " << edge.weight << "\n";
    }
    file.close();

    std::cout << "Граф сохранён в " << output_dir + "graph.dat" << "!\n";
    return 0;
}
