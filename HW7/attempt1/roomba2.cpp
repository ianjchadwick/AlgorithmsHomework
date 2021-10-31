#include "roomba.h"
#include <climits>
using namespace std;

struct Node
{
    int x, y, distance;
    Heading facing;
    motion_plan path;

};

//Checks the current position to see if roomba can exit. If it can, return true, otherwise return false.
bool canExit(coordinate position, Heading facing, int m, int n)
{
    switch (facing)
    {
        case North: if (position.first == 0)
                        return true;
                    else if(position.second == 0)
                        return true;
                    else
                        return false;

        case West:  if (position.first == m - 1)
                            return true;
                    else if (position.second == 0)
                            return true;
                    else
                        return false;    
        case South: if (position.first == m - 1) 
                            return true;
                    else if (position.second == 0)
                            return true;
                    else
                        return false;

        case East:  if (position.first == 0)
                            return true;
                    else if (position.second == n - 1)
                            return true;
                    else
                        return false;
        default:
                    return false;
    }
}

motion_plan finish(int m, int n, coordinate position, Heading facing, motion_plan path)
{
    switch (facing)
    {
        case North: 
            if (position.first == 0)
                path.push_back(go_straight);
            else if(position.second == 0)
                path.push_back(go_left);
        case West:  
            if (position.first == m - 1)
                path.push_back(go_left);
            else if (position.second == 0)
                path.push_back(go_straight);
        case South: 
            if (position.first == m - 1) 
                path.push_back(go_straight);
            else if (position.second == 0)
                path.push_back(go_left);
        case East:  
            if (position.first == 0)
                path.push_back(go_left);
            else if (position.second == n - 1)
                path.push_back(go_straight);
    }

    return path;
}


//Checks the current position against the maze grid and visited grid to see if the roomba has at least one valid move, returns true if so. 
//Returns false otherwise.
bool canMove(grid const &M, grid &visited, coordinate position, Heading facing)
{
    int Xcoord = position.first;
    int Ycoord = position.second;
    vector<bool> row;
    vector<bool> Vrow;

    switch (facing)
    {
        case North:
            row = M[Xcoord - 1];
            Vrow = visited[Xcoord - 1];
            if (!row[Ycoord] && !Vrow[Ycoord])
                return true;
            row = M[Xcoord];
            Vrow = visited[Xcoord];
            if (!row[Ycoord - 1] && !Vrow[Ycoord - 1])
                return true;
            else
                return false;
        
        case West:
            row = M[Xcoord];
            Vrow = visited[Xcoord];
            if (!row[Ycoord - 1] && !Vrow[Ycoord - 1])
                return true;
            row = M[Xcoord + 1];
            Vrow = visited[Xcoord + 1];
            if (!row[Ycoord] && !Vrow[Ycoord])
                return true;
            else
                return false;
        
        case East:
            row = M[Xcoord];
            Vrow = visited[Xcoord];
            if (!row[Ycoord + 1] && !Vrow[Ycoord + 1])
                return true;
            row = M[Xcoord - 1];
            Vrow = visited[Xcoord - 1];
            if (!row[Ycoord] && !Vrow[Ycoord])
                return true;
            else  
                return false;
        
        case South:
            row = M[Xcoord];
            Vrow = visited[Xcoord];
            if (!row[Ycoord + 1] && !Vrow[Ycoord + 1])
                return true;
            row = M[Xcoord + 1];
            Vrow = visited[Xcoord + 1];
            if (!row[Ycoord] && !Vrow[Ycoord])
                return true;
            else
                return false;
        default:
            return false;
    }
    return false;
}

motion_plan Move(grid const &M, coordinate position, Heading facing, motion_plan plan, grid &visited)
{
    int Mdimension = M.size() - 1;
    int Ndimension = M[1].size() - 1;
    bool done = canExit(position, facing, Mdimension, Ndimension);
    bool ableToMove = canMove(M, visited, position, facing);

    while (!done && ableToMove)
    {    
        Heading newFacing;
        coordinate newPosition;
        motion_plan branch1, branch2;
        
        done = canExit(position, facing, Mdimension, Ndimension);
        ableToMove = canMove(M, visited, position, facing);
    }
 

}


motion_plan escape_route(grid const &M, coordinate init_coordinate, Heading init_heading) {
    return {};
}
