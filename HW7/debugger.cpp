#include <iostream>
#include <climits>
#include <queue>
using namespace std;
#include <vector>
#include <utility>
#include <cstddef>

enum Heading{ North, South, East, West };
enum Action{ go_straight, go_left };

typedef std::pair <std::size_t,std::size_t >coordinate;			// (0,0) is top left. (1,0) is south of (0,0)
typedef std::vector <std::vector <bool >> grid;				// m-length vector of n-length vectors.
typedef std::vector <Action > motion_plan;
typedef std::vector <std::vector <int>> visit;

motion_plan escape_route (grid const &, coordinate, Heading);
bool canExit (int x, int y, Heading facing, int m, int n);
bool canMove (grid const &M, visit visited, Heading facing, int x, int y);
motion_plan finish (int m, int n, int x, int y, Heading facing, motion_plan path);
motion_plan Move (grid const &M, coordinate position, Heading facing, motion_plan plan);

struct Node {
  int x, y, d;
  Heading facing;
  motion_plan path;
};

//Checks the current position to see if roomba can exit. If it can, return true, otherwise return false.
bool canExit (int x, int y, Heading facing, int m, int n)
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

  if (facing == South)
    {
      if (x == m - 1)
	    return true;
      else
	    return false;
    }
  if (facing == East)
    {
      if (y == n - 1)
	    return true;
      else
	    return false;
    }
}


//Checks the current position against the maze grid and visited grid to see if target coordinate is a valid move, returns true if so. 
//Returns false otherwise.
bool
canMove (grid const &M,  vector<vector<int>> visited, Heading facing, int x, int y)
{
  //cout << "canMove X is: " << x << endl;
  //cout << "canMove Y is: " << y << endl;
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
      bool 	valid = ((!cell) && !(visited_cell == facing));
    //cout << "canMove cell is: " << cell << endl;
    //cout << "canMove visited is: " << visited_cell << endl;
    //cout << "valid is: " << valid << endl;

      return valid;
    }
}



motion_plan
escape_route (grid const &M, coordinate init_coordinate, Heading init_heading)
{

  int m = M.size ();
  int n = M[0].size ();
  int max = m*n;
  motion_plan route = { };

  //create a grid to track visited nodes and fill it with "false"
  vector<vector<int>> visited;
  vector <int> row;
  for (int i = 0; i < n; i++)
    {
      row.push_back (-1);

    }
  for (int i = 0; i < m; i++)
    {
      visited.push_back (row);
    }

  //create a queue to hold nodes.
  queue < Node > Q;

  Node first;
  first.x = init_coordinate.first;
  first.y = init_coordinate.second;
  first.facing = init_heading;
  first.path = {};
  first.d = 0;

  visited[first.x][first.y] = first.facing;
  cout << "The first visited node facing: " << visited[first.x][first.y] << endl;
  Q.push (first);

  while (!Q.empty ())
    {
      Node v = Q.front();
      Q.pop();

      int curr_x = v.x;
      int curr_y = v.y;
      int curr_d = v.d;
      motion_plan curr_plan = v.path;
      Heading curr_facing = v.facing;

      cout << "X is: " << curr_x << endl;
      cout << "Y is: " << curr_y << endl;
      cout << "Heading is: " << curr_facing << endl;

	 bool done = canExit(v.x, v.y, v.facing, m, n);

    if(done)
    {
        route = v.path;
        return route;
    }

    if (curr_d >= max)
        break;

    if (curr_facing == North)
	{
	  if (canMove(M, visited, curr_facing, curr_x -1, curr_y))
	    {
	      Node * north = new Node;
	      north->x = curr_x - 1;
	      north->y = curr_y;
	      north->facing = curr_facing;
	      north->path = curr_plan;
	      north->path.push_back (go_straight);
	      visited[curr_x - 1][curr_y] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x - 1][curr_y] << endl;
	      Q.push (*north);
	    }

	  if (canMove (M, visited, curr_facing, curr_x, curr_y - 1))
	    {
	      Node *west = new Node;
	      west->x = curr_x;
	      west->y = curr_y - 1;
	      west->facing = West;
	      west->path = curr_plan;
	      west->path.push_back (go_left);
	      visited[curr_x][curr_y - 1] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x][curr_y - 1] << endl;
	      Q.push (*west);
	    }
	}
      if (curr_facing == West)
	{
	  if (canMove (M, visited, curr_facing, curr_x + 1, curr_y))
	    {
	      Node *south = new Node;
	      south->x = curr_x + 1;
	      south->y = curr_y;
	      south->facing = South;
	      south->path = curr_plan;
	      south->path.push_back (go_left);
	      visited[curr_x + 1][curr_y] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x + 1][curr_y] << endl;
	      Q.push (*south);
	    }

	  if (canMove (M, visited, curr_facing, curr_x, curr_y - 1))
	    {
	      Node *west = new Node;
	      west->x = curr_x;
	      west->y = curr_y - 1;
	      west->facing = curr_facing;
	      west->path = curr_plan;
	      west->path.push_back (go_straight);
	      visited[curr_x][curr_y - 1] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x][curr_y - 1] << endl;
	      Q.push (*west);
	    }
	}
      if (curr_facing == South)
	{
	  if (canMove (M, visited, curr_facing, curr_x + 1, curr_y))
	    {
	      Node *south = new Node;
	      south->x = curr_x + 1;
	      south->y = curr_y;
	      south->facing = curr_facing;
	      south->path = curr_plan;
	      south->path.push_back (go_straight);
	      visited[curr_x + 1][curr_y] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x + 1][curr_y] << endl;
	      Q.push (*south);
	    }

	  if (canMove (M, visited, curr_facing, curr_x, curr_y + 1))
	    {
	      Node *east = new Node;
	      east->x = curr_x;
	      east->y = curr_y + 1;
	      east->facing = East;
	      east->path = curr_plan;
	      east->path.push_back (go_left);
	      visited[curr_x][curr_y + 1] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x][curr_y + 1] << endl;
	      Q.push (*east);
	    }
	}
      if (curr_facing == East)
	{
	  if (canMove (M, visited, curr_facing, curr_x - 1, curr_y))
	    {
	      Node *north = new Node;
	      north->x = curr_x - 1;
	      north->y = curr_y;
	      north->facing = North;
	      north->path = curr_plan;
	      north->path.push_back (go_left);
	      visited[curr_x - 1][curr_y] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x - 1][curr_y] << endl;
	      Q.push (*north);
	    }

	  if (canMove (M, visited, curr_facing, curr_x, curr_y + 1))
	    {
	      Node *
		east = new Node;
	      east->x = curr_x;
	      east->y = curr_y + 1;
	      east->facing = curr_facing;
	      east->path = curr_plan;
	      east->path.push_back (go_straight);
	      visited[curr_x][curr_y + 1] = curr_facing;
          cout << "Visited array gets: " << visited[curr_x][curr_y + 1] << endl;
	      Q.push (*east);
	    }
	}
    }

  return{};
}



int
main ()
{
  grid
    maze = {
   {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,},
   {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,},
   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}
  };

  motion_plan plan = escape_route (maze, { 4, 4 }, South);


  if (plan.empty ())
    std::cout << "No escape!" << std::endl;
  else
  for (Action a:plan)
      switch (a)
	{
	case go_straight:
	  std::cout << "go_straight" << std::endl;
	  break;
	case go_left:
	  std::cout << "go_left" << std::endl;
	}

  return 0;

}
