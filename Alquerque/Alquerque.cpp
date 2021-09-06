// Alquerque.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "auxiliar.h"
#include "Tabuleiro.h"
#include "JogoDaVelha.h"
#include "Minimax.h"

void Instructions()
{
	cout << "RULES" << endl;
	cout << "coordinates are beetwen 0 and 5\n\n" << endl;
	cout << "INSERT " << " <X> <Y>" << endl;
	cout << "example: INSERT 0 0\n\n" << endl;
	cout << "MOVE " << "<fromX> <fromY> <toX> <toY>" << endl;
	cout << "example: MOVE 0 0 0 1" << endl;
}

void ParseMove(Movement &m, const int &mark)
{
	Action action = NONE;
	Position p1; 
	Position p2;
	
	cout << "describe your move: " << endl;
	string move;
	cin >> move;
	getline(cin, move);
	cout << move << endl;

	string auxAc = "";
	int size = move.length();
	for (int i = 0; i < size; i++) 
	{
		if (move[0] == ' ') 
		{
			cout << auxAc << endl;
			if (auxAc == "MOVE")
			{
				action = MOVE_PIECE;
			}
			else if (auxAc == "INSERT") 
			{
				action = INSERTION_PIECE;
			}
			else
			{
				action = NONE;
			}
			move.erase(0, 1);
			break;
		}
		else
		{
			auxAc +=  move[0];
			move.erase(0, 1);
		}
	}

	if (action == INSERTION_PIECE)
	{
		p1 = make_tuple(-1, -1);
		int x = atoi(&move[0]);
		int y = atoi(&move[2]);
		p2 = make_tuple(x, y);
		
	}
	else if(action == MOVE_PIECE)
	{
		int x1 = atoi(&move[0]);
		int y1 = atoi(&move[2]);
		p1 = make_tuple(x1, y1);

		int x2 = atoi(&move[4]);
		int y2 = atoi(&move[6]);
		p2 = make_tuple(x2, y2);
	}

	m = make_tuple(mark, p1, p2, action);
}

void PlayGame() 
{
	Tabuleiro alquerque(new int[5][5]{ {1,0,-1,0,1},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{-1,0,1,0,-1} });
	JogoDaVelha jogo;
	int player = 0;
	
	/*
	Movement insertion(1, make_tuple(-1,-1), make_tuple(0, 0), INSERTION_PIECE);
	jogo.makeMove(alquerque, insertion);
	cout << alquerque << endl;
	jogo.UndoMove(alquerque);
	cout << alquerque << endl;

	Movement move(1, make_tuple(0, 0), make_tuple(1, 1), MOVE_PIECE);
	jogo.makeMove(alquerque, insertion);
	cout << alquerque << endl;
	jogo.makeMove(alquerque, move);
	cout << alquerque << endl;
	jogo.UndoMove(alquerque);
	cout << alquerque << endl;
	*/

	Minimax mx;     
	mx.deepness = 6;
	mx.Max(alquerque, jogo, 1);

}



int main()
{
	PlayGame();
}

/*
	Tabuleiro alquerque( new int[5][5]{ {0,0,0,0,0},{1,2,1,2,1},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0} });

	cout << "testing updates on current state" << endl;
	std::cout << alquerque;
	alquerque.insertPiece(make_tuple(0, 0), 1);
	std::cout << alquerque;
	alquerque.movePiece(make_tuple(0, 0), make_tuple(1, 1), 1);
	std::cout << alquerque;
	alquerque.removePiece(make_tuple(1, 1), 1);
	std::cout << alquerque;

	cout << "testing neighbours" << endl;
	cout << alquerque.getNeighbours(make_tuple(0,0)) << endl;
	cout << alquerque.getNeighbours(make_tuple(1, 1)) << endl;

	cout << "testing available positions" << endl;
	cout << alquerque.availablePositions() << endl;



	// TESTES Jogo da Velha OBSERVAÇÃO: PESQUISAR SOBRE 'CLASSE ENUMERADA'
	JogoDaVelha jv;
	Movement a = make_tuple(1, make_tuple(-1, -1), make_tuple(0, 0), INSERTION_PIECE) ;
	Movement b = make_tuple(1, make_tuple(0, 0), make_tuple(1, 1), MOVE_PIECE) ;

	auto moves1 = jv.possibleMoves(alquerque, 1);
	cout << moves1 << endl;

	jv.makeMove(alquerque, a);
	cout << a << endl;
	cout << alquerque << endl;


	auto moves2 = jv.possibleMoves(alquerque, 1);
	cout << moves2 << endl;


	if (jv.makeMove(alquerque, b))
	{
		cout << b << endl;
		cout << alquerque << endl;
	}
	*/