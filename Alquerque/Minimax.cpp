#include "Minimax.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono> 
Movement Minimax::SelectMove(Tabuleiro& alquerque, JogoDaVelha& jv, int mark) //tentar adicionar const
{
    int maxUT = numeric_limits<int>::min();
    Movement mov;
    for (auto movement : jv.possibleMoves(alquerque, mark))
    {
        jv.makeMove(alquerque, movement);
        int ut = Min(alquerque, jv, mark * -1);
        if (maxUT < ut) { 
            maxUT = ut; 
            mov = movement;
        }
        jv.UndoMove(alquerque);

    }

    return mov;
}

int Minimax::Max(Tabuleiro& alquerque, JogoDaVelha& jv, int mark)
{
    
    deepness -= 1;
    cout << alquerque << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (deepness < 0 || jv.checkGameOver(alquerque))
    {

        return Utility(alquerque, jv);
    }
    int maxUT = numeric_limits<int>::min();
    for (auto movement : jv.possibleMoves(alquerque, mark))
    {
        jv.makeMove(alquerque, movement);

        int ut = Min(alquerque, jv, mark * -1);
        if (maxUT < ut) {
            maxUT = ut;
        }

        deepness += 1;
        jv.UndoMove(alquerque);

    }

    return maxUT;
}

int Minimax::Min(Tabuleiro& alquerque, JogoDaVelha& jv, int mark)
{
    deepness -= 1;
    //cout << alquerque << endl;
    //std::this_thread::sleep_for(std::chrono::seconds(1));

    if (deepness < 0 || jv.checkGameOver(alquerque))
    {
        return Utility(alquerque, jv);
    }

    int minUT = numeric_limits<int>::max();
   
    for (auto movement : jv.possibleMoves(alquerque, mark))
    {
        jv.makeMove(alquerque, movement);
        int ut = Max(alquerque, jv, mark * -1);
        if (minUT > ut) {
            minUT = ut;
        }

        deepness += 1;
        jv.UndoMove(alquerque);
        
    }

    return minUT;
}

int Minimax::Utility(const Tabuleiro& alquerque, const JogoDaVelha& jv)
{
    return jv.Evaluate(alquerque);
}
