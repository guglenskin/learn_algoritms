# analyzer.py
import networkx as nx
import matplotlib.pyplot as plt
from pyvis.network import Network

class GraphAnalyzer:
    def __init__(self, graph):
        self.graph = graph
        self.pos = nx.spring_layout(graph, seed=42)
        
    def basic_analysis(self):
        return {
            "degree_centrality": nx.degree_centrality(self.graph),
            "betweenness": nx.betweenness_centrality(self.graph),
            "clustering": nx.average_clustering(self.graph),
            "diameter": nx.diameter(self.graph) if nx.is_connected(self.graph) else -1
        }
    
    def visualize_3d(self):
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        
        xs, ys, zs = [], [], []
        for node in self.graph.nodes():
            x, y = self.pos[node]
            z = self.basic_analysis()['degree_centrality'][node]
            xs.append(x)
            ys.append(y)
            zs.append(z)
            
        ax.scatter(xs, ys, zs, s=200, c=zs, cmap='viridis')
        plt.title("3D Degree Centrality Visualization")
        plt.show()
    
    def interactive_plot(self, output="graph.html"):
        net = Network(notebook=False, height="750px", width="100%")
        net.from_nx(self.graph)
        
        for node in net.nodes:
            node["size"] = node["degree"] * 10
            node["title"] = f"Degree: {node['degree']}"
            
        net.show(output)
        return output