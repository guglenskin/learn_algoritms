#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp> // ?????????? ????????? ????
#include "graph_generator.h"

TEST_CASE("Graph generation test") {
    json config = {
        {"vertices", 10},
        {"edges", 15},
        {"directed", false}
    };
    
    GraphGenerator generator(config);
    auto graph = generator.generate();
    
    REQUIRE(graph.size() <= 10);
}