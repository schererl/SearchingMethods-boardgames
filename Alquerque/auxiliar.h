#pragma once



#ifndef IMPORTINGLIBS

#include <string>
#include <vector>
#include <array>
#include <stack>
#include <map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <limits>

using namespace std;
#endif // IMPORTINGLIBS

#ifndef DATASTRUCTURE
enum Action {
	INSERTION_PIECE,
	MOVE_PIECE,
	REMOVE_PIECE,
	JUMP_OVER_PIECE,
	NONE
};
using Position = tuple<int, int>;
using Player = int;
//                      0         1        2          3
using Movement = tuple<Player, Position, Position, Action>; //start_position, final_position, action *talvez seja melhor usar uma struct

#endif // !DATASTRUCTURE

