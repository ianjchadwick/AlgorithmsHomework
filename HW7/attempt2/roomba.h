#ifndef _ROOMBA
#define _ROOMBA

#include <vector>
#include <utility>
#include <cstddef>

enum Heading { North, South, East, West };
enum Action { go_straight, go_left };

typedef std::pair<std::size_t, std::size_t> coordinate; // (0,0) is top left. (1,0) is south of (0,0)
typedef std::vector<std::vector<bool>> grid; // m-length vector of n-length vectors.
typedef std::vector<Action> motion_plan;
typedef std::vector <std::vector <int>> visit;


motion_plan escape_route(grid const&, coordinate, Heading);
bool canExit(int x, int y, Heading facing, int m, int n);
bool canMove (grid const &M, visit visited, Heading facing, int x, int y);
motion_plan finish(int m, int n, int x, int y, Heading facing, motion_plan path);
motion_plan Move(grid const &M, coordinate position, Heading facing, motion_plan plan);



#endif
