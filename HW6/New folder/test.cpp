#include "job.h"
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
  
  bool isCyclic();

  bool isCyclicHelper(int v, bool visited[], bool *recStack);

  int dependencyCount(int v);
};

Graph::Graph(int V) {
  this->V = V;
  adjacent = new list<int>[V];
}

int Graph::dependencyCount (int v)
{
  int count = 0;
  
  bool *visited = new bool[V];

  for (int i = 0; i < V; i++)
  {
    visited[i] = false;
  }

  queue<int> Q;
  
  Q.push(v);
  visited[v] = true;
  count++;
  
  
  while (!Q.empty())
  {
    
    int h = Q.front(); 
    
    list<int>::iterator i;
    for(i = adjacent[h].begin(); i != adjacent[h].end(); ++i)
    {
      
      if (!visited[*i])
        {
          Q.push(*i);
          visited[*i] = true;
          count++;
        }
    }
    
    Q.pop();
  }
  
  return count;
}


bool Graph::isCyclicHelper(int v, bool visited[], bool *recStack) {

  if(visited[v] == false)
    {
    
      visited[v] = true;
      recStack[v] = true;

      
      list<int>::iterator i;
      for(i = adjacent[v].begin(); i != adjacent[v].end(); ++i)
      {

        if (!visited[*i] && isCyclicHelper(*i, visited, recStack))
         {
           return true;
         }
        else if (recStack[*i])
          {
            return true;
          }
      }
    }
    recStack[v] = false;
    return false;
}

bool Graph::isCyclic() {
  bool *visited = new bool[V];
  bool *recStack = new bool[V];
  
  for (int i = 0; i < V; i++)
  {
    visited[i] = false;
    recStack[i] = false;
  }

  for (int i = 0; i < V; i++)
    {
      if (isCyclicHelper(i, visited, recStack))
      return true;
    }

  return false;

}

void Graph::addEdge(int vertex, int target) {
  adjacent[vertex].push_back(target);
}

bool canFinish(int n, vector<pair<int, int>> &dependencies) { 

  
  int size = dependencies.size();
  
  Graph job(n);
  
  bool finishable = true;
  for (int i = 0; i < size; i++)
    {
      int first = dependencies[i].first - 1;
      int second = dependencies[i].second - 1;
      job.addEdge(second,first);
    }
  
  if (job.isCyclic())
    finishable = false;
  
  return finishable; 
  }


bool canRun(int n, vector<pair<int, int>> &dependencies, int j, int i) {
  
  int size = dependencies.size();
  Graph job(n);
  bool runable = true;


  for (int i = 0; i < size; i++)
    {
      int first = dependencies[i].first - 1;
      int second = dependencies[i].second - 1;
      job.addEdge(second,first);
    }

    
    if (job.dependencyCount(j-1) > i)
      runable = false;

  return runable;
}
