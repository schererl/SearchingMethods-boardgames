#pragma once
#include "auxiliar.h"
#include "tabuleiro.h"
#include "JogoDaVelha.h"
class Minimax
{
public:
	int deepness;
	Movement SelectMove(Tabuleiro& alquerque, JogoDaVelha& jv, int mark);
	int Max(Tabuleiro& alquerque, JogoDaVelha& jv, int mark);
	int Min(Tabuleiro& alquerque, JogoDaVelha& jv, int mark);
	int Utility(const Tabuleiro& alquerque, const JogoDaVelha& jv);

};

