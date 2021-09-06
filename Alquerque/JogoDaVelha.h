#pragma once
#include "auxiliar.h"
#include "Tabuleiro.h"

class JogoDaVelha
{
private:
	enum INTERNAL_STATE{
		INSERT,
		MOVE
	};
	int pieces_left_p1 = 0;
	int pieces_left_p2 = 0;
	INTERNAL_STATE current_state_p1 = INSERT;
	INTERNAL_STATE current_state_p2 = INSERT;
public:
	
	stack<Movement> move_pile; //PRECISA SER UMA PILHA!!!
	JogoDaVelha() {} //pedir número de peças e número de peças não colocadas como parâmetro
	vector<Movement> possibleMoves(Tabuleiro &alquerque, const Player &mark);
	bool makeMove(Tabuleiro &alquerque, Movement &movement);
	void UndoMove(Tabuleiro &alquerque); // pilhaaaaaaaaa
	bool checkGameOver(const Tabuleiro& alquerque);
	int Evaluate(const Tabuleiro& alquerque)const { return 0;  }; //preencher depois
	
};

ostream& operator<<(ostream& os, Movement movement);
ostream& operator<<(ostream& os, vector<Movement> lstMovments);
