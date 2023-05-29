//  Player.cpp

#include "Player.h"
#include <iostream>

using namespace std;

// ======================================= Player

Player::Player(string name)
: m_name (name)
{

}

string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
{
    return false;
}

Player::~Player()
{

}

// ======================================= HumanPlayer

HumanPlayer::HumanPlayer(string name)
: Player (name)
{

}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    int holeChoice {0};
    
    // If no beans in side s, return -1
    if(b.beansInPlay(s) == 0)
    {
        cerr << "No beans left in side " << s << ", returning -1\n";
        return -1;
    }
    
    for (;;)
    {
        // Prompt Human player for move
        cerr << "Give me a move " << Player::name() << ": ";
        cin >> holeChoice;
        
        // Testing statement
//        holeChoice = 2;
        
        // If not a valid hole, loop again
        if (holeChoice <= 0 || holeChoice > b.holes())
        {
            cerr << "Chose an invalid hole/pot, try again!\n";
            // exit (1);
            continue;
        }
        
        switch (s) {
            case SOUTH:
            {
                if (b.beans(s, holeChoice) == 0)
                {
                    // If no beans in hole, loop again
                    cerr << "No beans in hole " << holeChoice << ", try a different hole!\n";
                    continue;
                }
                else
                {
                    // If choosing a valid move, return holeChoice
                    cerr << "Returning your hole choice: " << holeChoice << endl;
                    return holeChoice;
                }
                break;
            }
            case NORTH:
            {
                
                // Convert holeChoice for reference
                int mappedHole = (NSIDES + 2*b.holes()) - holeChoice;
                cerr << "Hole choice after mapping = " << mappedHole << endl;
                
                if (b.beans(s, holeChoice) == 0)
                {
                    cerr << "No beans in hole: " << holeChoice << ", try a different hole!\n";
                    continue;
                }
                else
                {
                    cerr << "Returning your hole choice: " << holeChoice << endl;
                    return holeChoice;
                }
                break;
            }
            default:
                break;
        }
    }
}

HumanPlayer::~HumanPlayer()
{
    
}

// ======================================= BadPlayer

BadPlayer::BadPlayer(string name)
: Player (name)
{

}

// BadPlayer will always choose the hole with fewest beans
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    // If no beans in side s, return -1
    if(b.beansInPlay(s) == 0)
    {
        cerr << "No beans left in side " << s << ", returning -1\n";
        return -1;
    }
    
    switch (s) {
        case SOUTH:
        {
            // Iterate through holes and find one with least beans it
            for (int i {1}; i <= b.holes(); i++)
            {
                if (b.beans(s, i) != 0)
                {
                    cerr << "Returning first hole with nonzero beans: " << i << endl;
                    return i;
                }
            }
            break;
        }
        case NORTH:
        {
            // Iterate through holes and find one with least beans it
            for (int i {b.holes()+2}; i <= NSIDES + 2*b.holes() - 1; i++)
            {
                if (b.beans(s, i) != 0)
                {
                    cerr << "Returning first hole with nonzero beans: " << i << endl;
                    return i;
                }
            }
        }
        default:
            break;
    }
    cerr << "Something went wrong with your BadPlayer::chooseMove function, returnin -1...\n";
    return -1;
}

BadPlayer::~BadPlayer()
{
    
}

// ======================================= SmartPlayer

SmartPlayer::SmartPlayer(string name)
: Player (name)
{

}

// BadPlayer will always choose the hole with fewest beans
int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    // If no beans in side s, return -1
    if(b.beansInPlay(s) == 0)
    {
        cerr << "No beans left in side " << s << ", returning -1\n";
        return -1;
    }
    
    switch (s) {
        case SOUTH:
        {
            // Iterate through holes and find one with least beans it
            for (int i {1}; i <= b.holes(); i++)
            {
                if (b.beans(s, i) != 0)
                {
                    cerr << "Returning first hole with nonzero beans: " << i << endl;
                    return i;
                }
            }
            break;
        }
        case NORTH:
        {
            // Iterate through holes and find one with least beans it
            for (int i {b.holes()+2}; i <= NSIDES + 2*b.holes() - 1; i++)
            {
                if (b.beans(s, i) != 0)
                {
                    cerr << "Returning first hole with nonzero beans: " << i << endl;
                    return i;
                }
            }
        }
        default:
            break;
    }
    cerr << "Something went wrong with your BadPlayer::chooseMove function, returnin -1...\n";
    return -1;
}

SmartPlayer::~SmartPlayer()
{
    
}
