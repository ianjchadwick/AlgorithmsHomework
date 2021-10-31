#include <iostream>
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

typedef vector<pair<int, int>> deplist;

int main() {

Graph g(4);
deplist ex1, ex2, circle, line, star1, star2, tree;
  ex1 = {{1, 2}};
  ex2 = {{1, 2}, {2, 1}};

g.addEdge(0,2);


return 0;
}
