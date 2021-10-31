#include "job.h"
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//Got some help from https://www.geeksforgeeks.org/detect-cycle-in-a-graph/ which helped refresh my memory on how to implement lists, 
//iterators and some of the syntax for classes.

//create a Graph class
class Graph {
  
  protected:
  
  int V;
  list<int> *adjacent;
  
  public:
  //constructor
  Graph(int V);
  //adds a directed edge via adjacency lists. Nodes point toward nodes that they depend on
  void addEdge (int vertex, int target);
  //checks to see if the graph is cyclic
  bool isCyclic();
  //a DFS based helper function that to iterate through all the vertices
  bool isCyclicHelper(int v, bool visited[], bool *recStack);
  //a BFS based helper function to count all the dependencies of a vertex
  int dependencyCount(int v);
};

//constructor
Graph::Graph(int V) {
  this->V = V;
  adjacent = new list<int>[V];
}

//utilizes a BFS strategy based on the lecture example to visit each node starting at the job node you want to complete
//counts all the dependencies for that job and returns that value
int Graph::dependencyCount (int v)
{
  //initialize count variable
  int count = 0;
  
  //initialize boolean array to hold color of nodes false = white, true = black
  bool *visited = new bool[V];
  //initialize all to white
  for (int i = 0; i < V; i++)
  {
    visited[i] = false;
  }

  //create a queue and push the node to the job that we're checking to 
  queue<int> Q;
  //push that node onto queue and color it black, add one to count.
  Q.push(v);
  visited[v] = true;
  count++;
  
  //use BFS algorithm to iterate through all nodes connected to input node
  while (!Q.empty())
  {
    //start with the first node in queue
    int h = Q.front(); 
    //iterate through all of its neighbors in the adjacency list.
    list<int>::iterator i;
    for(i = adjacent[h].begin(); i != adjacent[h].end(); ++i)
    {
      //if the node has not been visited, add it to the que, and increase the count
      if (!visited[*i])
        {
          Q.push(*i);
          visited[*i] = true;
          count++;
        }
    }
    //once we're done, remove it from the que
    Q.pop();
  }
  //return the total count, which will be the number of jobs that must be completed before input job v can start
  return count;
}

//helper function for isCyclic to use DFS to find all connected nodes
//will return true if there is a cycle and false if the graph is not cyclic
bool Graph::isCyclicHelper(int v, bool visited[], bool *recStack) {
  //if the node has not been visited
  if(visited[v] == false)
    {
      //mark color it black and then put it on the recursion stack
      visited[v] = true;
      recStack[v] = true;

      //for each of the neighbors of the node
      list<int>::iterator i;
      for(i = adjacent[v].begin(); i != adjacent[v].end(); ++i)
      {
        //if the neighbor has not been visited, recursively call this funciton on that node
        //if that node or any further recursive calls ends up at a node that is on the recursion stack
        //then the graph is cyclic and the function returns true
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
    //otherwise remove from the recursion stack and return false. this path dead ends.
    recStack[v] = false;
    return false;
}

//function called on a graph to detect if there is a cycle somewhere within the graph
bool Graph::isCyclic() {
  //create arrays to hold values for the color and the recursion stack and intialize all to false
  bool *visited = new bool[V];
  bool *recStack = new bool[V];
  
  for (int i = 0; i < V; i++)
  {
    visited[i] = false;
    recStack[i] = false;
  }

  //for each node in the graph, run isCyclicHelper to determine if there is a cycle in any part of the graph that
  //starts with that node if there is return true
  for (int i = 0; i < V; i++)
    {
      if (isCyclicHelper(i, visited, recStack))
      return true;
    }
  //otherwise return false
  return false;

}

//add a directed edge from vertex to target vertex
void Graph::addEdge(int vertex, int target) {
  adjacent[vertex].push_back(target);
}

bool canFinish(int n, vector<pair<int, int>> &dependencies) { 

  //find the size of the vector  
  int size = dependencies.size();
  //create a graph of size n = number of jobs
  Graph job(n);
  //initialize boolean return variable
  bool finishable = true;

  //fill the graph's adjacency list with all the edges
  //the 2nd job of the pair points to the first job that it depends on
  for (int i = 0; i < size; i++)
    {
      int first = dependencies[i].first - 1;
      int second = dependencies[i].second - 1;
      job.addEdge(second,first);
    }
  
  //if the graph has any cycles, that means that there is a logical fallacy and
  //the jobs cannot be finished based on the dependencies they have.
  if (job.isCyclic())
    finishable = false;
  
  return finishable; 
  }


bool canRun(int n, vector<pair<int, int>> &dependencies, int j, int i) {
  
  //initialize size of dependency vector, job Graph with size n, and return variable
  int size = dependencies.size();
  Graph job(n);
  bool runable = true;

  //fill the graph's adjacency list with all the edges
  //the 2nd job of the pair points to the first job that it depends on
  for (int i = 0; i < size; i++)
    {
      int first = dependencies[i].first - 1;
      int second = dependencies[i].second - 1;
      job.addEdge(second,first);
    }

    /*if the number of jobs that depend on the input job is higher than the job
    slot you want to use to do that job, it can't run.
    otherwise there is some combination of jobs and NOPs that you can do that will
    allow you to run that job in that spot.*/
    if (job.dependencyCount(j-1) > i)
      runable = false;

  return runable;
}
