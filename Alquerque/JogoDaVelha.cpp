#include "JogoDaVelha.h"

JogoDaVelha::JogoDaVelha(int number_pieces)
{
    pieces_left[-1] = number_pieces;
    pieces_left[1] = number_pieces;
}

vector<Movement> JogoDaVelha::possibleMoves(Tabuleiro& alquerque, const Player &mark)
{
    vector<Movement> possibleMovements;
    
    int p_left = pieces_left.find(mark)->second;
    if(p_left > 0)
    { 
        //            check insertion
        vector<Position> freeSpaces = alquerque.availablePositions();
        for (auto finalPosition : freeSpaces)
        {
            Position initialPosition = make_tuple(-1, -1);
            possibleMovements.push_back( make_tuple(mark, initialPosition, finalPosition, INSERTION_PIECE) );
        }
    }
    else
    { 
    
        //                  check move
        //get player positions
        vector<Position> playerPositions = alquerque.getPlayerPieces(mark);
        

        //for each piece, get its neighbours
        vector<tuple<Position, Position>> allNeighbours; 
        for (auto initialPosition : playerPositions) 
        {
            vector<Position> neighbours = alquerque.getNeighbours(initialPosition);
            for (auto finalPosition : neighbours) 
            {
                if (!alquerque.isEmpty(get<0>(finalPosition), get<1>(finalPosition)))
                    continue;
                possibleMovements.push_back( make_tuple(mark, initialPosition, finalPosition, MOVE_PIECE) );
            }
        }
    }

    return possibleMovements;
}

bool JogoDaVelha::makeMove(Tabuleiro& alquerque, Movement &movement)
{
    Player mark = get<0>(movement);
    Position start = get<1>(movement);
    Position end = get<2>(movement);
    Action ac = get<3>(movement);
    
    if (ac == INSERTION_PIECE) {
        alquerque.insertPiece(end, mark);
        pieces_left[mark] -= 1;
    }
    else if (ac == MOVE_PIECE) {
        alquerque.movePiece(start, end, mark);
    }

    move_pile.push(movement); 

    return false;
}

void JogoDaVelha::UndoMove(Tabuleiro &alquerque)
{
    Movement _last_movement = move_pile.top();
    move_pile.pop();

    Player mark = get<0>(_last_movement);
    Position start = get<1>(_last_movement);
    Position end = get<2>(_last_movement);
    Action ac = get<3>(_last_movement);

    

    if (ac == INSERTION_PIECE) 
    {
        alquerque.state_[get<0>(end)][get<1>(end)] = 0;
        pieces_left[mark] += 1;
    }
    else if (ac == MOVE_PIECE) 
    {
        alquerque.state_[get<0>(end)][get<1>(end)] = 0;
        alquerque.state_[get<0>(start)][get<1>(start)] = mark;
        
    }
    else
    {
        throw exception(""); // A DEFINIR
    }
}

bool JogoDaVelha::checkGameOver(const Tabuleiro& alquerque)
{
    //* talvez precise verificar qual ação foi executada
    return false;

    Movement _last_movement = move_pile.top();
    // pegar finalPosition do último movimento do jogo para saber a posição da última peça movida 
    int line = get<0>(get<2>(_last_movement));
    int column = get<1>(get<2>(_last_movement));
    int mark = get<0>(_last_movement);

    int lineSequence = 0;
    int columnSequence = 0;
    int dpSequence = 0;
    int dsSequence = 0;

    //testa 4 alinhamentos
    for (int i = 0; i < 4; i++)
    {
        //em linha
        if (alquerque.existPlayerAt(line, i, mark) && alquerque.existPlayerAt(line, i + 1, mark)) { lineSequence++; }
        //em coluna
        if (alquerque.existPlayerAt(i, column, mark) && alquerque.existPlayerAt(i + 1, column, mark)) { columnSequence++; }
        //diagonal princial
        if (alquerque.existPlayerAt(i, i, mark) && alquerque.existPlayerAt(i + 1, i + 1, mark)) { dpSequence++; }
        //diagonal secundária
        if (alquerque.existPlayerAt(i, 4 - i, mark) && alquerque.existPlayerAt(i + 1, 4 - (i + 1), mark)) { dsSequence++; }
    }

    
    //verificar se existe alinhamento de alguma peça em alguma diagonal válida
    //digonais menores
    bool sd0 = alquerque.existPlayerAt(0, 1, mark) &&  alquerque.existPlayerAt(1, 2, mark) &&  alquerque.existPlayerAt(3, 4, mark) && alquerque.existPlayerAt(2, 3, mark);
    bool sd1 = alquerque.existPlayerAt(1, 0, mark) &&  alquerque.existPlayerAt(2, 1, mark) &&  alquerque.existPlayerAt(3, 2, mark) && alquerque.existPlayerAt(4, 3, mark);
    bool sd2 = alquerque.existPlayerAt(3, 0, mark) &&  alquerque.existPlayerAt(1, 2, mark) &&  alquerque.existPlayerAt(2, 1, mark) && alquerque.existPlayerAt(0, 3, mark);
    bool sd3 = alquerque.existPlayerAt(4, 1, mark) &&  alquerque.existPlayerAt(3, 2, mark) &&  alquerque.existPlayerAt(2, 3, mark) && alquerque.existPlayerAt(1, 4, mark);

    return sd0 || sd1 || sd2 || sd3 || (lineSequence > 2) || (columnSequence > 2) || (dpSequence > 2) || (dsSequence > 2);
    
}

ostream& operator<<(ostream& os, Movement movement) {

    if (get<3>(movement) == INSERTION_PIECE)
        os << "Player" << get<0>(movement) << " INSERTED a new piece AT (" << to_string(get<0>(get<2>(movement))) << ", " << to_string(get<0>(get<2>(movement))) << ")";

    else if (get<3>(movement) == MOVE_PIECE)
        os << "Player" << get<0>(movement) << " MOVED a piece FROM (" << to_string(get<0>(get<1>(movement))) << ", " << to_string(get<0>(get<1>(movement))) << ") TO (" << to_string(get<0>(get<2>(movement))) << ", " << to_string(get<0>(get<2>(movement))) << ")";


    else os << "Action not undentified";

    os << "\n";

    return os;
}


ostream& operator<<(ostream& os, vector<Movement> lstMovments) {


    os << "Total possible actions: " << to_string(lstMovments.size()) << "\n\n";
    for (auto movement : lstMovments)
    {

        if (get<3>(movement) == INSERTION_PIECE)
            os << "Player" << get<0>(movement) << " INSERT a new piece AT (" << to_string(get<0>(get<2>(movement))) << ", " << to_string(get<1>(get<2>(movement))) << ")";

        else if (get<3>(movement) == MOVE_PIECE)
            os << "Player" << get<0>(movement) << " MOVE a piece FROM (" << to_string(get<0>(get<1>(movement))) << ", " << to_string(get<1>(get<1>(movement))) << ") TO (" << to_string(get<0>(get<2>(movement))) << ", " << to_string(get<1>(get<2>(movement))) << ")";


        else os << "Action not undentified";

        os << "\n";
    }

    return os;
}
