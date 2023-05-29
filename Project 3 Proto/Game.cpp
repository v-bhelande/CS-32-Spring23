//  Game.cpp

# include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
: m_board(b), m_south(south), m_north(north), m_start(SOUTH)
{

}

void Game::display() const
{
    cout << m_north->name() << "\n ";
    
    for (int i {1}; i <= m_board.holes(); i++) cout << m_board.beans(NORTH, i) << " ";
    cout << endl;
    
    cout << m_board.beans(NORTH, 0);
    for (int i {0}; i < 2*m_board.holes()-1; i++) cout << " ";
    cout << m_board.beans(SOUTH, 0) << "\n ";
    
    for (int i {1}; i <= m_board.holes(); i++) cout << m_board.beans(SOUTH, i) << " ";
    cout << endl;
    
    cout << m_south->name() << "\n";
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    // If there are no beans in play on each side, game is over
    if (m_board.beansInPlay(SOUTH) != 0 || m_board.beansInPlay(NORTH) != 0)
    {
        cerr << "Game continues!\n";
        over = false;
        return;
    }
    else
    {
        over = true;
        
        // Compare beans in each POT
        if (m_board.beans(NORTH, POT) > m_board.beans(SOUTH, POT))
        {
            cerr << m_north->name() << " is the winner!\n";
            hasWinner = true;
            winner = NORTH;
        }
        else if (m_board.beans(NORTH, POT) < m_board.beans(SOUTH, POT))
        {
            cerr << m_south->name() << " is the winner!\n";
            hasWinner = true;
            winner = SOUTH;
        }
        else  // Case for draw
        {
            cerr << "It was a draw...\n";
            hasWinner = false;
        }
    }
}

bool Game::move(Side s)
{
    // Cannot make move if no beans in play for player
    if (m_board.beansInPlay(s) == 0)
    {
        cerr << "Cannot make a move as no beans in play, returning false...\n";
        return false;
    }
    
    // Choose side and have corresponding player choose a move
    switch (s) {
        case SOUTH:
            Side endSide;
            int endHole;
            cerr << m_south->name() << " is making a move, calling sow function!\n";
            m_board.sow(SOUTH, m_south->chooseMove(m_board, SOUTH), endSide, endHole);
            break;
        case NORTH:
        default:
            break;
    }
    
    // Display move after each turn
    // Infinte loop until a move cannot be completed
    return false;  // TODO:  implement this function
}

void Game::play()
{
    // TODO:  implement this function
}

// TESTING PURPOSES ONLY
int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
