#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Graph {
  
  protected:
  
  int V;
  list<int> *adjacent;
  
  public:
  Graph(int V);
  void addEdge (int vertex, int target);
};

Graph::Graph(int V) {
  this->V = V;
  adjacent = new list<int>[V];
}

void Graph::addEdge(int vertex, int target) {
  adjacent[vertex].push_back(target);
}

