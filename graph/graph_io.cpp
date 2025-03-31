#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <nlohmann/json.hpp>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

// Определение структуры Edge
struct Edge {
    int target;
    double weight;
    Edge(int t, double w) : target(t), weight(w) {}
};

// Определение типа Graph
using Graph = std::unordered_map<int, std::vector<Edge>>;

// Генерация случайного графа
Graph generate_random_graph(int vertices, int edges, bool directed = false) {
    Graph graph;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_node(0, vertices-1);
    std::uniform_real_distribution<> dist_weight(0.1, 5.0);

    for(int i = 0; i < edges; ++i) {
        int from = dist_node(gen);
        int to = dist_node(gen);
        double weight = dist_weight(gen);
        
        if(from != to) {
            graph[from].emplace_back(to, weight);
            if(!directed) {
                graph[to].emplace_back(from, weight);
            }
        }
    }
    return graph;
}

// Сохранение графа в файл
void save_graph(const Graph& graph, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    for (const auto& [node, neighbors] : graph) {
        file << node << ":";
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if(i > 0) file << " ";
            file << neighbors[i].target << "," << neighbors[i].weight;
        }
        file << "\n";
    }
    file.close();
    std::cout << "Graph saved to " << filename << std::endl;
}

int main() {
    // Чтение конфигурации
    std::ifstream config_file("config.json");
    if (!config_file.is_open()) {
        std::cerr << "Error opening config file!" << std::endl;
        return 1;
    }

    json config;
    try {
        config_file >> config;
    } catch (const std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return 1;
    }

    // Параметры графа
    int vertices = config["vertices"].get<int>();
    int edges = config["edges"].get<int>();
    bool directed = config["directed"].get<bool>();

    // Генерация и сохранение графа
    auto graph = generate_random_graph(vertices, edges, directed);
    save_graph(graph, "graph.dat");

    return 0;
}