#include "roomba.h"
#include <cstring>
#include <queue>
#include <iostream>
typedef std::vector <std::vector <bool>> visit;
using namespace std;

struct Node
{
    int x, y, d;
    Heading facing;
    motion_plan path;
};

//Checks the current position to see if roomba can exit. If it can, return true, otherwise return false.
bool canExit(int x, int y, Heading facing, int m, int n)
{
    if (facing == North)
    {
        if (x == 0)
            return true;
        else
            return false;
    }
    if (facing == West)
    {
        if (y == 0)
            return true;
        else
            return false;
    }
    
    if (facing == South){ 
        if (x == m - 1) 
            return true;
        else
           return false;
    }
    if (facing == East){
        if (y == n - 1)
            return true;
        else
            return false;
    }
}

//Checks the current position against the maze grid and visited grid to see if target coordinate is a valid move, returns true if so. 
//Returns false otherwise.
bool canMove (grid const &M, visit visited, Heading facing, int x, int y)
{
  int m = M.size ();
  int n = M[0].size ();
  if ((x < 0) || (y < 0) || (x >= m) || (y >= n))
    {
      return false;
    }
  else
    {
      bool cell = M[x][y];
      int 	visited_cell = visited[x][y];
      bool 	valid = ((!cell) && !(visited_cell));

      return valid;
    }
}


motion_plan escape_route(grid const &M, coordinate init_coordinate, Heading init_heading) {
    
    int m = M.size();
    int n = M[0].size();
    int Dmax = m*n;
    motion_plan route = {};
    
    //create a grid to track visited nodes and fill it with "false"
    visit visited;
    vector<bool> row;
    for (int i = 0; i < n; i++)
    {
        row.push_back(0);
        
    }
    for (int i = 0; i < m; i++)
    {
            visited.push_back(row);
    }

    //create a queue to hold nodes.
    queue<Node> Q;

    Node first;
    first.x = init_coordinate.first;
    first.y = init_coordinate.second;
    first.facing = init_heading;
    first.path = {};
    first.d = 0;
    
    visited[first.x][first.y] = true;
    Q.push(first);

    while (!Q.empty())
    {
        Node v = Q.front();
        Q.pop();

        int curr_x = v.x;
        int curr_y = v.y;
        int curr_d = v.d;
        motion_plan curr_plan = v.path;
        Heading curr_facing = v.facing;
        cout << "D = " << curr_d << endl;


        bool done = canExit(v.x, v.y, v.facing, m, n);

        if(done)
        {
            route = v.path;
            return route;
        }

        if (curr_d >= Dmax)
            return {};

        
            if (curr_facing == North)
            {           
                if(canMove(M, visited, curr_facing, curr_x -1, curr_y))
                    {
                        Node *north= new Node;
                        north->x = curr_x-1;
                        north->y = curr_y;
                        north->facing = curr_facing;
                        north->path = curr_plan;
                        north->path.push_back(go_straight);
                        north->d = curr_d +1;
	                    visited[curr_x - 1][curr_y] = true;
                        Q.push(*north);
                    }

                if(canMove (M, visited, curr_facing, curr_x, curr_y - 1))
                    {
                        Node *west= new Node;
                        west->x = curr_x;
                        west->y = curr_y-1;
                        west->facing = West;
                        west->path = curr_plan;
                        west->path.push_back(go_left);
                        west->d = curr_d +1;
	                    visited[curr_x][curr_y - 1] = true;
                        Q.push(*west);
                    }    
            }
            if (curr_facing == West)
            {        
                if (canMove (M, visited, curr_facing, curr_x + 1, curr_y))
                    {
                        Node *south= new Node;
                        south->x = curr_x+1;
                        south->y = curr_y;
                        south->facing = South;
                        south->path = curr_plan;
                        south->path.push_back(go_left);
                        south->d = curr_d +1;
	                    visited[curr_x + 1][curr_y] = true;
                        Q.push(*south);
                    }

                if(canMove(M, visited, curr_facing, curr_x, curr_y-1))
                    {
                        Node *west= new Node;
                        west->x = curr_x;
                        west->y = curr_y-1;
                        west->facing = curr_facing;
                        west->path = curr_plan;
                        west->path.push_back(go_straight);
                        west->d = curr_d +1;
                        visited[curr_x][curr_y-1] = true;
                        Q.push(*west);
                    }
            }       
            if (curr_facing == South)
            {
                if(canMove(M, visited, curr_facing, curr_x +1 , curr_y))
                    {
                        Node *south= new Node;
                        south->x = curr_x+1;
                        south->y = curr_y;
                        south->facing = curr_facing;
                        south->path = curr_plan;
                        south->path.push_back(go_straight);
                        south->d = curr_d +1;
                        visited[curr_x+1][curr_y] = true;
                        Q.push(*south);
                    }

                if(canMove(M, visited, curr_facing, curr_x, curr_y+1))
                    {
                        Node *east= new Node;
                        east->x = curr_x;
                        east->y = curr_y+1;
                        east->facing = East;
                        east->path = curr_plan;
                        east->path.push_back(go_left);
                        east->d = curr_d +1;
                        visited[curr_x][curr_y+1] = true;
                        Q.push(*east);
                    }
            }
            if (curr_facing == East)
            {
                if(canMove(M, visited, curr_facing, curr_x-1, curr_y))
                    {
                        Node *north= new Node;
                        north->x = curr_x-1;
                        north->y = curr_y;
                        north->facing = North;
                        north->path = curr_plan;
                        north->path.push_back(go_left);
                        north->d = curr_d +1;
                        visited[curr_x-1][curr_y] = true;
                        Q.push(*north);
                    }

                if(canMove(M, visited, curr_facing, curr_x, curr_y+1))
                    {
                        Node *east= new Node;
                        east->x = curr_x;
                        east->y = curr_y+1;
                        east->facing = curr_facing;
                        east->path = curr_plan;
                        east->path.push_back(go_straight);
                        east->d = curr_d +1;
                        visited[curr_x][curr_y+1] = true;
                        Q.push(*east);
                    }
            }
        }


    return {};
}
