//  Game.cpp

#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
: m_board(b), m_south(south), m_north(north), m_turn(SOUTH)
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
//    for (;;)
//    {
//        // Cannot make move if no beans in play for player
//        if (m_board.beansInPlay(SOUTH) == 0)
//        {
//            cerr << m_south->name() << " cannot make a move as no beans in play, sweeping beans into " << m_north->name() << " pot...\n";
//            return false;
//        }
//
//        Side endSide;
//        int endHole;
//
//        // Choose side and have corresponding player choose a move
//        cerr << m_south->name() << " can make a move, calling sow function!\n";
//        m_board.sow(SOUTH, m_south->chooseMove(m_board, SOUTH), endSide, endHole);
//
//        // Last bean lands in Side s POT
//        if (endSide == SOUTH && endHole == 0)
//        {
//            cerr << "Last bean landed in " << m_south->name() << " pot, taking another turn!\n";
//            continue;
//        }
//
//        // Capture case
//
//        // If bean in last hole is on Side s and has only 1 bean, it must have been empty before
//        if (beans(SOUTH, endHole) == 1 && beans(NORTH, endHole) > 0)
//        {
//            m_board.moveToPot(SOUTH, endHole, SOUTH);
//            m_board.moveToPot(NORTH, endHole, SOUTH);
//            display();
//
//            // End turn
//            cerr << "Capture successful, turn is over!\n";
//            return true;
//        }
//        display();
//        cerr << "Turn is over!\n";
//        return true;
//    }
    
    // Choose side and have corresponding player choose a move
    switch (s) {
        case SOUTH:
            for (;;)
            {
                // Cannot make move if no beans in play for player
                if (m_board.beansInPlay(SOUTH) == 0)
                {
                    // Sweep remaining beans into opposing player's side
                    cerr << m_south->name() << " cannot make a move as no beans in play, sweeping beans into " << m_north->name() << " pot...\n";
                    
                    for (int i {1}; i <= m_board.holes(); i++)
                    {
                        m_board.moveToPot(NORTH, i, NORTH);
                    }
                    display();
                    return false;
                }
                
                Side endSide;
                int endHole;
                
                // Choose side and have corresponding player choose a move
                cerr << m_south->name() << " can make a move, calling sow function!\n";
                m_board.sow(SOUTH, m_south->chooseMove(m_board, SOUTH), endSide, endHole);
                
                // Last bean lands in Side s POT
                if (endSide == SOUTH && endHole == 0)
                {
                    cerr << "Last bean landed in " << m_south->name() << " pot, taking another turn!\n";
                    display();
                    continue;
                }
                
                // Capture case
                
                // If bean in last hole is on Side s and has only 1 bean, it must have been empty before
                if (beans(SOUTH, endHole) == 1 && beans(NORTH, endHole) > 0 && endSide == SOUTH)
                {
                    m_board.moveToPot(SOUTH, endHole, SOUTH);
                    m_board.moveToPot(NORTH, endHole, SOUTH);
                    display();
                    
                    // End turn
                    cerr << "Capture successful, turn is over!\n";
                    return true;
                }
                display();
                cerr << "Turn is over!\n";
                return true;
            }
            break;
        case NORTH:
            for (;;)
            {
                // Cannot make move if no beans in play for player
                if (m_board.beansInPlay(NORTH) == 0)
                {
                    cerr << m_north->name() << " cannot make a move as no beans in play, sweeping beans into " << m_south->name() << " pot...\n";
                    
                    for (int i {1}; i <= m_board.holes(); i++)
                    {
                        m_board.moveToPot(SOUTH, i, SOUTH);
                    }
                    display();
                    return false;
                }
                
                Side endSide;
                int endHole;
                
                // Choose side and have corresponding player choose a move
                cerr << m_north->name() << " can make a move, calling sow function!\n";
                m_board.sow(NORTH, m_north->chooseMove(m_board, NORTH), endSide, endHole);
                
                // Last bean lands in Side s POT
                if (endSide == NORTH && endHole == 0)
                {
                    cerr << "Last bean landed in " << m_north->name() << " pot, taking another turn!\n";
                    display();
                    continue;
                }
                
                // Capture case
                
                // If bean in last hole is on Side s and has only 1 bean, it must have been empty before
                if (beans(NORTH, endHole) == 1 && beans(SOUTH, endHole) > 0 && endSide == NORTH)
                {
                    m_board.moveToPot(SOUTH, endHole, NORTH);
                    m_board.moveToPot(NORTH, endHole, NORTH);
                    display();
                    
                    // End turn
                    cerr << "Capture successful, turn is over!\n";
                    return true;
                }
                display();
                cerr << "Turn is over!\n";
                return true;
            }
        default:
            break;
    }
}

void Game::play()
{
    // Check game status
    bool over = false;
    bool hasWinner = false;
    Side winner;
    
    for (;;)
    {
        // Check status
        status(over, hasWinner, winner);
        if (over) return;
        
        // Make a move
        move(m_turn);
        
        // Change player's turn
        switch (m_turn) {
            case SOUTH:
                m_turn = NORTH;
                break;
            case NORTH:
                m_turn = SOUTH;
            default:
                break;
        }
    }
    // TODO:  implement this function
}

// TESTING PURPOSES ONLY
int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
