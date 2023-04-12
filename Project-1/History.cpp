// History.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

#include "globals.h"
#include "Rabbit.h"
//#include "Player.h"
#include "Arena.h"
#include "History.h"

using namespace std;

History::History(int nRows, int nCols) {
    
    // Initialize relevant members
    m_rows = nRows;
    m_cols = nCols;
    
    // Initialize EMPTY grid
    for (int r {1}; r <= m_rows; r++) {
        for (int c {1}; c <= m_cols; c++) {
            m_grid[r-1][c-1] = 0;
            //cout << m_grid[r-1][c-1];
        }
        //cout << endl;
    }
    //cout << endl;
}

bool History::record(int r, int c) {

    // The function returns false if row r, column c is not within the bounds specified by the History constructor
    if (r > m_rows || c > m_cols || r <= 0 || c <= 0) {
        cout << "False";
        return false;
    }
    
    // If rabbit's health = 1 at a particular spot, increment number of turns at that point on grid
    m_grid[r-1][c-1] += 1;
    return true;
}

void History::display() const {
    // When we pass history by reference in Arena, will that update nRows, nCols, r, c with the necessary values?
    // NOOOOOOOO
    // Reference to Arena::display() function
    
//    for (int r {1}; r <= m_rows; r++) {
//        for (int c {1}; c <= m_cols; c++) {
//            if (m_grid[r-1][c-1] == 0) cout << '.';
//            else cout << 'R';
//        }
//        cout << endl;
//    }
    
    //char displayGrid[][]
    
//    for (int r {1}; r <= m_rows; r++) {
//        for (int c {1}; c <= m_cols; c++) {
//
//            //            char gridChar = m_grid[r][c];
//            //            switch (gridChar)
//            //            {
//            //                case 0: gridChar = '.'; break;
//            //                case 1: gridChar = 'A';
//            //                case 26: break;
//            //                default: gridChar = m_grid[r][c] + 64; break; // Letters B through Z
//            //            }
//            //        }
//            //        cout << endl;
//
//            if (m_grid[r-1][c-1] == 0)
//                m_grid[r-1][c-1] = '.';
//            else if (m_grid[r-1][c-1] >= 26)
//                m_grid[r-1][c-1] = 'Z';
//            else
//                m_grid[r-1][c-1] = ; // Letter value + 64?
//        }
//    }
    
    for (int r {1}; r <= m_rows; r++) {
        for (int c {1}; c <= m_cols; c++) {
            if (m_grid[r-1][c-1] == 0)
                cout << '.';
            else if (m_grid[r-1][c-1] < 26)
                cout << static_cast<char>(m_grid[r-1][c-1] + 64);
//            else if (m_grid[r-1][c-1] >= 26)
//                     cout << 'Z';
            else cout << 'Z';
        }
        cout << endl;
    }
    cout << endl;
}
