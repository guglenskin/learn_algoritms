# test_analyzer.py
import pytest

def test_analysis():
    G = nx.karate_club_graph()
    analyzer = GraphAnalyzer(G)
    stats = analyzer.basic_analysis()
    
    assert 0 <= stats['clustering'] <= 1
    assert len(stats['degree_centrality']) == 34