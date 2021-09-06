#include "Tabuleiro.h"

vector<Position> Tabuleiro::availablePositions()
{
	vector<Position> available;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (Tabuleiro::state_[i][j] == 0) { 
				available.push_back(make_tuple(i, j));
			}
		}
	}


	return available;
}

vector<Position> Tabuleiro::getNeighbours(const Position &currentPosition)
{

	auto search = Tabuleiro::boardMap.find(currentPosition);
	vector<Position> neighbours;
	
	if (search == Tabuleiro::boardMap.end()) throw exception();
	
	for(auto it = (search->second).begin(); it != (search->second).end(); ++it) 
	{
		auto search2 = Tabuleiro::orientation.find(*it);
		if (search2 == Tabuleiro::orientation.end()) throw exception();

		tuple<int, int> transform = search2->second;
		neighbours.push_back(make_tuple(get<0>(currentPosition) + get<0>(transform), get<1>(currentPosition) + get<1>(transform)));
	}
	
	
	return neighbours;
}

vector<Position> Tabuleiro::getPlayerPieces(const Player& mark)
{
	vector<tuple<int, int>> playerPositions;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (Tabuleiro::state_[i][j] == mark) playerPositions.push_back(make_tuple(i, j));
		}
	}
	return playerPositions;
}

bool Tabuleiro::movePiece(const Position &initialPosition, const Position &finalPosition, const Player &mark)
{
	int initX = get<0>(initialPosition), initY = get<1>(initialPosition);
	int fnlX = get<0>(finalPosition), fnlY = get<1>(finalPosition);
	if (Tabuleiro::state_[initX][initY] != mark || Tabuleiro::state_[fnlX][fnlY] != 0)
		return false;

	//verificar se essa é uma posição válida
	Tabuleiro::state_[initX][initY] = 0;
	Tabuleiro::state_[fnlX][fnlY] = mark;
	return true;
}

bool Tabuleiro::insertPiece(const Position &position, const Player &mark)
{
	int X = get<0>(position), Y = get<1>(position);
	if (Tabuleiro::state_[X][Y] != 0)
		return false;

	Tabuleiro::state_[X][Y] = mark;
	return true;
	
}

bool Tabuleiro::removePiece(const Position &position, const Player &mark)
{
	//talvez descontar o número de peças do jogador
	int X = get<0>(position), Y = get<1>(position);
	if (Tabuleiro::state_[X][Y] != mark)
		return false;

	Tabuleiro::state_[X][Y] = 0;
	return true;
}

array<array <int, 5>, 5> Tabuleiro::getStateCopy()
{
	array<array <int, 5>, 5> cpy;
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) 
		{
			cpy[i][j] = Tabuleiro::state_[i][j];
		}
	}

	return cpy;
}


ostream& operator<<(ostream& os, Tabuleiro& tb)
{
	string output = "\n";
	array<array <int, 5>, 5> arr = tb.getStateCopy();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			output += to_string(arr[i][j]) + " ";
		}
		output += "\n";
	}
	os << output;
	output += "\n";
	return os;
}

ostream& operator<<(ostream& os, vector<tuple<int, int>> vec)
{
	string output = "";
	for (auto v : vec) {
		output += "(" + to_string(get<0>(v)) + ", " + to_string(get<1>(v)) + ") ";
	}
	output += "\n";
	os << output;
	return os;
}

