import networkx as nx

def save_graph_as_obj(edges, output_file):
    G = nx.Graph()
    for edge in edges:
        G.add_edge(edge[0], edge[1], weight=edge[2])
    
    nodes = list(G.nodes())
    node_index = {node: i for i, node in enumerate(nodes)}
    
    with open(output_file, "w") as f:
        f.write("# OBJ file generated for graph visualization\n")
        
        # Записываем вершины
        for node in nodes:
            x, y, z = node_index[node] * 0.5, node_index[node] * 0.5, 0  # Простая раскладка
            f.write(f"v {x} {y} {z}\n")
        
        # Записываем рёбра
        for u, v in G.edges():
            f.write(f"l {node_index[u] + 1} {node_index[v] + 1}\n")

def read_graph_from_file(filename):
    edges = []
    with open(filename, "r") as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 3:
                edges.append((parts[0], parts[1], int(parts[2])))
    return edges

def main():
    filename = "graph.dat"
    output_file = "graph.obj"
    edges = read_graph_from_file(filename)
    
    save_graph_as_obj(edges, output_file)
    print(f"Граф сохранен в {output_file}, импортируйте его в Blender.")

if __name__ == "__main__":
    main()
