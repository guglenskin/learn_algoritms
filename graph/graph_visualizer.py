import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph(edges, graph_type, output_file):
    G = nx.DiGraph() if graph_type in [2, 3] else nx.Graph()
    
    if graph_type == 1:  # Полный граф
        nodes = list(set(sum(([u, v] for u, v, _ in edges), [])))
        G.add_nodes_from(nodes)
        for i in range(len(nodes)):
            for j in range(i + 1, len(nodes)):
                weight = next((w for u, v, w in edges if (u == nodes[i] and v == nodes[j]) or (u == nodes[j] and v == nodes[i])), None)
                if weight is not None:
                    G.add_edge(nodes[i], nodes[j], weight=weight)
        pos = nx.drawing.nx_agraph.graphviz_layout(G, prog="dot", args="-Grankdir=LR")  # Полный граф слева направо
    elif graph_type == 2:  # Дерево
        for edge in edges:
            G.add_edge(edge[0], edge[1], weight=edge[2])
        pos = nx.drawing.nx_agraph.graphviz_layout(G, prog="dot", args="-Grankdir=TB")  # Дерево сверху вниз
    else:  # Ориентированный граф
        for edge in edges:
            G.add_edge(edge[0], edge[1], weight=edge[2])
        pos = nx.spring_layout(G)
    
    plt.figure(figsize=(8, 8))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=3000, font_size=12, arrows=True)
    
    edge_labels = {(u, v): w for u, v, w in edges}
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=10)
    
    plt.savefig(output_file)
    plt.close()

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
    output_file = "graph.png"
    edges = read_graph_from_file(filename)
    
    print("Выберите тип графа:")
    print("1 - Полный граф")
    print("2 - Дерево")
    print("3 - Ориентированный граф")
    
    while True:
        try:
            graph_type = int(input("Введите номер: "))
            if graph_type in [1, 2, 3]:
                break
            else:
                print("Ошибка: Введите 1, 2 или 3.")
        except ValueError:
            print("Ошибка: Введите целое число.")
    
    visualize_graph(edges, graph_type, output_file)
    print(f"Граф сохранен в {output_file}")

if __name__ == "__main__":
    main()
