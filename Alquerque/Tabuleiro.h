#pragma once
#include "auxiliar.h"


class Tabuleiro
{

public:
    int _initialState[5][5];
    array<array <int, 5>, 5> state_;

    Tabuleiro(int initialState[5][5]) { 
        for (int i = 0; i < 5; i++) 
        {
            for (int j = 0; j < 5; j++) 
            {
                _initialState[i][j] = initialState[i][j];
                state_[i][j] = initialState[i][j];
            }
        }
    }

    //verificar se isto funciona
    Tabuleiro(const Tabuleiro& t) { 
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                _initialState[i][j] = t._initialState[i][j];
                state_[i][j] = t.state_[i][j];
            }
        }
    }
    
    vector<Position> availablePositions();
    vector<Position> getNeighbours(const Position &position);
    vector<Position> getPlayerPieces(const Player &mark);
    
    bool movePiece(const Position &initialPosition, const Position &finalPosition, const Player &mark);
    bool insertPiece(const Position &position, const Player &mark);
    bool removePiece(const Position &position, const Player &mark);
    
    //caso precise assegurar que state é readonly a
    //const array<array <int, 5>, 5> state() const { return state_; }
    
    // usei dois parâmetros para não dar criar muitas tuplas desnecessárias na hora de verificar fim de jogo
    //inline informa o compilador para substituir a função direto nas suas chamadas --minimiza sobrecarga
    //definição precisa estar no header
    inline bool existPlayerAt(int X, int Y, const Player& mark) const
    {
        return Tabuleiro::state_[X][Y] == mark;
    }
    
    bool isEmpty(int X, int Y) const
    {
        return Tabuleiro::state_[X][Y] == 0;
    }

    array<array <int, 5>, 5> getStateCopy();
    
    
private:

    

    map<tuple<int, int>, vector<string>> boardMap = {
        //linha x coluna
            {make_tuple(0,0), {"S", "SE", "E" }},
            {make_tuple(0,1), {"W", "S", "E"}},
            {make_tuple(0,2), {"W", "SW", "S", "SE" ,"E"}},
            {make_tuple(0,3), {"W", "S", "E"}},
            {make_tuple(0,4), {"W", "SW", "S"}},

            {make_tuple(1,0), {"N", "E", "S"}},
            {make_tuple(1,1), {"N", "NW", "W", "SW", "S", "SE", "E", "NE"}},
            {make_tuple(1,2), {"N", "W", "S", "E"}},
            {make_tuple(1,3), {"N", "NW", "W", "SW", "S", "SE", "E", "NE"}},
            {make_tuple(1,4), {"N", "W", "S"}},

            {make_tuple(2,0), {"N", "S", "SE", "E", "NE"}},
            {make_tuple(2,1), {"N", "W", "S", "E"}},
            {make_tuple(2,2), {"N", "NW", "W", "SW", "S", "SE", "E", "NE"}},
            {make_tuple(2,3), {"N", "W", "S", "E"}},
            {make_tuple(2,4), {"N", "NW", "W", "SW", "S"}},

            {make_tuple(3,0), {"N", "E", "S"}},
            {make_tuple(3,1), {"N", "NW", "W", "SW", "S", "SE", "E", "NE"}},
            {make_tuple(3,2), {"N", "W", "S", "E"}},
            {make_tuple(3,3), {"N", "NW", "W", "SW", "S", "SE", "E", "NE"}},
            {make_tuple(3,4), {"N", "W", "S"}},

            {make_tuple(4,0), {"N", "E", "NE"}},
            {make_tuple(4,1), {"N", "W", "E"}},
            {make_tuple(4,2), {"N", "NW", "W", "E", "NE"}},
            {make_tuple(4,3), {"N", "W", "E"}},
            {make_tuple(4,4), {"N", "NW", "W"}}
    };

    map<string, tuple<int, int>> orientation = {
        {"N",make_tuple(-1, 0)},
        //south
        {"S",make_tuple(1, 0)},
        //west E
        {"W",make_tuple(0, -1)},
        //east D
        {"E",make_tuple(0, 1)},
        //northeast
        {"NE",make_tuple(-1, 1)},
        //northwest
        {"NW",make_tuple(-1, -1)},
        //southeast
        {"SE", make_tuple(1, 1)},
        //southwest
        {"SW", make_tuple(1, -1)}
    };


};

ostream& operator<<(ostream& os, Tabuleiro& tb);
ostream& operator<<(ostream& os, vector<tuple<int, int>> vec);



