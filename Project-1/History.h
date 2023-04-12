// History.h

#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class Arena;
class Player;
class Rabbit;

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Arena*  m_arena;
};

#endif /* HISTORY_H */
