//  Board.cpp

#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
: m_nHoles(nHoles), m_nInitialBeansPerHole(nInitialBeansPerHole)
{
    if (nHoles <= 0) m_nHoles = 1;
    if (nInitialBeansPerHole < 0) m_nInitialBeansPerHole = 0;
    
    for (int i {0}; i < NSIDES + 2*m_nHoles; i++)
    {
        if(i == 0 || i == m_nHoles+1)
        {
            num_beans.push_back(0);
//            cerr << "Pushed back 0\n";
        }
        else num_beans.push_back(m_nInitialBeansPerHole);
    }
    
    for (int i {0}; i < num_beans.size(); i++)
    {
        cerr << num_beans.at(i) << " ";
    }
    cerr << endl;
}

int Board::holes() const
{
    return m_nHoles;
}

int Board::beans(Side s, int hole) const
{
    if (hole < 0 || hole > m_nHoles)
    {
        cerr << "Chose an invalid hole, returning -1\n";
        return -1;
    }
    
    if (hole == POT)
    {
        switch (s) {
            case NORTH:
                return num_beans.at(0);
                break;
            case SOUTH:
                return num_beans.at(m_nHoles+1);
                break;
            default:
                break;
        }
    }

    // Conversion of North according to mapping scheme
    if (s == NORTH) hole = num_beans.size() - hole;
    return num_beans.at(hole);
}

int Board::beansInPlay(Side s) const
{
    int beanCounter {0};
    
    switch (s) {
        case SOUTH:
            for (unsigned long i {1}; i <= m_nHoles; i++) beanCounter += num_beans.at(i);
            cerr << "Returning " << beanCounter << " beans in play, side is: " << s << endl;
            return beanCounter;
            break;
        case NORTH:
            for (unsigned long i {num_beans.size()-1}; i >= num_beans.size()-m_nHoles; i--) beanCounter += num_beans.at(i);
            cerr << "Returning " << beanCounter << " beans in play, side is: " << s << endl;
            return beanCounter;
        default:
            break;
    }
}

int Board::totalBeans() const
{
    int beanCounter {0};
    for (int i {0}; i <= num_beans.size()-1; i++) beanCounter += num_beans[i];

    cerr << "Returning " << beanCounter << " total beans" << endl;
    return beanCounter;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if ((s != NORTH && s != SOUTH) || (hole <= 0 || hole > m_nHoles))
    {
        cerr << "Chose an invalid hole/pot, (" << s << ", " << hole << "), returning false\n";
        return false;
    }
    
    // Side s switches
    bool isSouth = false;
    bool isNorth = false;
    
    // Store number of beans to disperse
    int numBeans {0};
    
    // Iterator
    int i {0};
    
    switch (s) {
        case SOUTH:
            isSouth = true;
//            cerr << "bruhhhhh " << num_beans.at(hole) << endl;
            numBeans = num_beans.at(hole);
            i = hole;
            // Set beans at (s, hole) = 0
            num_beans.at(hole) = 0;
            break;
        case NORTH:
            isNorth = true;
            numBeans = num_beans.at(num_beans.size()-hole);
            i = num_beans.size()-hole;
            // Set beans at (s, hole) = 0
            num_beans.at(num_beans.size()-hole) = 0;
            break;
        default:
            break;
    }
    
    // Start filling from next hole
    if (i == num_beans.size()-1) i = 0;
    else i +=1;
    
    // Iterate through vector and store a bean
    while (i < num_beans.size())
    {
        // If we reach end of vector, start again at beginning
        if (i == num_beans.size()-1)
        {
            cerr << "Reached end of loop, starting again from the beginning\n";
            i = 0;
            break;
        }
        
        // Case for North Pot
        if (i == 0) if (isSouth) continue;
        
        // Case for South Pot
        if (i == m_nHoles+1) if (isNorth) continue;
        
        num_beans.at(i) += 1;
        cerr << "Deposited a bean in hole " << i << endl;
        
        numBeans--;
        cerr << "Beans remaining = " << numBeans << endl;
        
        if (numBeans == 0)
        {
//            cerr << "i = " << i << endl;
            
            // Statements to determine endSide and endHole
            if (i == m_nHoles+1)
            {
                endSide = SOUTH;
                endHole = 0;
            }
            else if (i == 0)
            {
                endSide = NORTH;
                endHole = 0;
            }
            else if (i > m_nHoles+1 && i <= num_beans.size()-1)
            {
                endSide = NORTH;
                endHole = i+1-m_nHoles;
            }
            else
            {
                endSide = SOUTH;
                endHole = i;
            }
            cerr << "Stored all beans, returning true, end side is " << endSide << " and end hole is " << endHole << "\n";
            return true;
        }
        // Move to next pot/hole
        i++;
    }
    
    cerr << "Something went wrong with your sow function bro, returning false...\n";
    return false;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if ((s != NORTH && s != SOUTH) || (hole <= 0 || hole > m_nHoles))
    {
        cerr << "Chose an invalid hole, (" << s << ", " << hole << "), returning false\n";
        return false;
    }

    // Add beans to potOwner's hole
    switch (potOwner) {
        case SOUTH:
            switch (s) {
                case SOUTH:
                    num_beans.at(m_nHoles+1) += num_beans.at(hole);
                    cerr << "Number of beans in pot of " << potOwner << " = " << num_beans.at(0) << endl;
                    // Remove beans from (s, hole)
                    num_beans.at(hole) = 0;
                    return true;
                    break;
                case NORTH:
                    num_beans.at(0) += num_beans.at(num_beans.size()-hole);
                    cerr << "Number of beans in pot of " << potOwner << " = " << num_beans.at(num_beans.size()-hole) << endl;
                    // Remove beans from (s, hole)
                    num_beans.at(hole) = 0;
                    return true;
                default:
                    break;
            }
            break;
        case NORTH:
            switch (s) {
                case SOUTH:
                    num_beans.at(m_nHoles+1) += num_beans.at(hole);
                    cerr << "Number of beans in pot of " << potOwner << " = " << num_beans[POT] << endl;
                    // Remove beans from (s, hole)
                    num_beans.at(hole) = 0;
                    return true;
                    break;
                case NORTH:
                    num_beans.at(0) += num_beans.at(num_beans.size()-hole);
                    cerr << "Number of beans in pot of " << potOwner << " = " << num_beans[POT] << endl;
                    // Remove beans from (s, hole)
                    num_beans.at(num_beans.size()-hole) = 0;
                    return true;
                default:
                    break;
            }
        default:
            break;
    }
}

// ONLY HERE FOR TESTING PURPOSES
bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole < 0 || hole > m_nHoles || beans < 0)
    {
        cerr << "Invalid hole " << hole << " chosen or -ve number of beans " << beans << " chosen\n";
        return false;
    }
    
    if(hole == POT)
    {
        switch (s) {
            case SOUTH:
                num_beans.at(m_nHoles+1) = beans;
                cerr << "Set beans at SOUTH POT (" << s << ", " << hole << ") to: "  << beans << endl;
                return true;
                break;
            case NORTH:
                num_beans.at(0) = beans;
                cerr << "Set beans at NORTH POT (" << s << ", " << hole << ") to: "  << beans << endl;
                return true;
                break;
            default:
                break;
        }
    }

    cerr << "POT was not chosen for setBeans function...\n";
    switch (s) {
        case SOUTH:
            num_beans.at(hole) = beans;
            cerr << "Set beans at (" << s << ", " << hole << ") to: "  << beans << endl;
            return true;
            break;
        case NORTH:
            num_beans.at(num_beans.size()-hole) = beans;
            cerr << "Set beans at (" << s << ", " << hole << ") to: "  << beans << endl;
            return true;
        default:
            break;
    }
}
