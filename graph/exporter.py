# exporter.py
from networkx.readwrite import json_graph
import json

class GraphExporter:
    @staticmethod
    def to_gephi(graph, filename):
        nx.write_gexf(graph, filename)
    
    @staticmethod
    def to_d3(graph, filename):
        d3_json = json_graph.node_link_data(graph)
        with open(filename, 'w') as f:
            json.dump(d3_json, f)
    
    @staticmethod
    def to_graphml(graph, filename):
        nx.write_graphml(graph, filename)