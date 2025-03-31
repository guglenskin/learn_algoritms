import argparse
import networkx as nx
import matplotlib.pyplot as plt
import os
from pyvis.network import Network

def load_graph(file_path):
    """Загрузка графа с автоматическим поиском файла"""
    # Проверяем возможные расположения файла
    possible_paths = [
        file_path,  # Оригинальный путь
        os.path.join(os.path.dirname(__file__), file_path),  # Рядом со скриптом
        os.path.join(os.path.dirname(__file__), '../graph.dat'),  # На уровень выше
        os.path.join(os.getcwd(), 'graph.dat')  # В рабочей директории
    ]
    
    for path in possible_paths:
        abs_path = os.path.abspath(path)
        if os.path.exists(abs_path):
            print(f"Found graph at: {abs_path}")
            return load_graph_file(abs_path)
    
    raise FileNotFoundError(f"Graph file not found in: {possible_paths}")

def load_graph_file(abs_path):
    """Непосредственная загрузка файла"""
    G = nx.Graph()
    with open(abs_path, 'r') as f:
        for line in f:
            if ':' not in line:
                continue
            node, neighbors = line.strip().split(':')
            node = int(node)
            for edge in neighbors.split():
                target, weight = edge.split(',')
                G.add_edge(node, int(target), weight=float(weight))
    return G

def visualize(G, output_file=None):
    """Визуализация с обработкой ошибок"""
    try:
        # Matplotlib визуализация
        plt.figure(figsize=(12, 10))
        pos = nx.spring_layout(G, seed=42)
        
        # Основная отрисовка
        nx.draw_networkx_nodes(G, pos, node_size=800, node_color='lightblue')
        nx.draw_networkx_edges(G, pos, width=2, edge_color='gray')
        nx.draw_networkx_labels(G, pos, font_size=10, font_weight='bold')
        
        # Подписи рёбер (совместимость со старыми версиями NetworkX)
        if hasattr(nx, 'draw_networkx_edge_labels'):
            edge_labels = {(u, v): d['weight'] for u, v, d in G.edges(data=True)}
            nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=8)
        else:
            print("Warning: Edge labels not available in your NetworkX version")
        
        # Сохранение/отображение
        if output_file:
            plt.savefig(output_file, dpi=300, bbox_inches='tight')
            print(f"Graph image saved to: {os.path.abspath(output_file)}")
        else:
            plt.title("Graph Visualization", pad=20)
            plt.show()
        
        # Интерактивная версия
        net = Network(height="800px", width="100%", notebook=False)
        net.from_nx(G)
        html_path = os.path.abspath('graph_interactive.html')
        net.show(html_path)
        print(f"Interactive version saved to: {html_path}")
        
    except Exception as e:
        print(f"Visualization error: {str(e)}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Graph Visualization Tool')
    parser.add_argument('-f', '--file', default='graph.dat', help='Input graph file')
    parser.add_argument('-o', '--output', help='Output image file')
    args = parser.parse_args()
    
    try:
        print("\n=== Graph Visualization ===")
        G = load_graph(args.file)
        
        print("\nGraph info:")
        print(f"- Nodes: {len(G.nodes())}")
        print(f"- Edges: {len(G.edges())}")
        print(f"- Density: {nx.density(G):.4f}")
        
        visualize(G, args.output)
        
    except Exception as e:
        print(f"\nError: {str(e)}")
        print("\nTry specifying full path:")
        print("  python visualize_graph.py -f /full/path/to/graph.dat")