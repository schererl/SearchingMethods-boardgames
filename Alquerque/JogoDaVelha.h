#pragma once
#include "auxiliar.h"
#include "Tabuleiro.h"

class JogoDaVelha
{
private:
	map<int,int> pieces_left{ {-1,0}, {1,0} };
public:
	
	stack<Movement> move_pile; //PRECISA SER UMA PILHA!!!
	JogoDaVelha() {} 
	JogoDaVelha(int number_pieces);
	vector<Movement> possibleMoves(Tabuleiro &alquerque, const Player &mark);
	bool makeMove(Tabuleiro &alquerque, Movement &movement);
	void UndoMove(Tabuleiro &alquerque); // pilhaaaaaaaaa
	bool checkGameOver(const Tabuleiro& alquerque);
	int Evaluate(const Tabuleiro& alquerque)const { return 0;  }; //preencher depois
	
};

ostream& operator<<(ostream& os, Movement movement);
ostream& operator<<(ostream& os, vector<Movement> lstMovments);
