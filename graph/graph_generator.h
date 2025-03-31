#pragma once

#include <unordered_map>
#include <vector>
#include <random>
#include <nlohmann/json.hpp> // ?????????? ????????? ????

using json = nlohmann::json;

struct Edge {
    int target;
    double weight;
    Edge(int t, double w) : target(t), weight(w) {}
};

class GraphGenerator {
public:
    GraphGenerator(const json& config);
    std::unordered_map<int, std::vector<Edge>> generate();
    
private:
    int vertices;
    int edges;
    bool directed;
    std::mt19937 engine;
    std::uniform_int_distribution<> dist_node;
    std::uniform_real_distribution<> dist_weight;
};