//  Main.cpp

#include "Side.h"
#include "Player.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <cassert>

using namespace std;

void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
                    b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
                b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
        b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
                b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
        b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    
//    b.setBeans(NORTH, 2, 0);
//    b.setBeans(NORTH, 3, 0);
//    cout << "=========" << endl;
//    int n2 = hp.chooseMove(b, NORTH);
//    cout << "=========" << endl;
//    assert(n2 == 1);
    
    int n3 = bp.chooseMove(b, SOUTH);
    b.setBeans(SOUTH, 1, 0);
    b.setBeans(SOUTH, 4, 0);
    assert(n3 == 1 || n3 == 3);
    
    int n4 = sp.chooseMove(b, SOUTH);
    assert(n4 == 1  ||  n == 3);
}

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    //    Homer
    //   0  1  2
    // 0         0
    //   2  0  0
    //    Bart
    g.status(over, hasWinner, winner);
    assert(!over);
    assert(g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    
    g.display();
}

void GameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3);
    assert(g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0);
    assert(g.beans(NORTH, 3) == 0);
    assert(g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
    cerr << "======== FINAL TURN OF GAME ========\n";
    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

void playGame()
{
    HumanPlayer bp1("Him");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
}

int main()
{
//    doBoardTests();
//    cout << "Passed all tests" << endl;
    
//    doPlayerTests();
//    cout << "Passed all tests" << endl;
    
//    doGameTests();
//    cout << "Passed all tests" << endl;
    
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 0);
//    b.setBeans(SOUTH, 0, 2);
//    b.setBeans(NORTH, 0, 6);
//    b.setBeans(NORTH, POT, 0);
//    b.setBeans(SOUTH, 1, 2);
//    b.setBeans(NORTH, 2, 1);
//    b.setBeans(NORTH, 3, 2);
//    Game g(b, &bp1, &bp2);
//    bool over;
//    bool hasWinner;
//    Side winner;
//
//    g.status(over, hasWinner, winner);
//
//    b.setBeans(NORTH, POT, 2);
//    g.status(over, hasWinner, winner);
//
//    b.setBeans(NORTH, POT, 4);
//    g.status(over, hasWinner, winner);
    
//    GameTests();
//    cout << "Passed all tests" << endl;
    
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 2);
//    Game g(b, &bp1, &bp2);
//    g.play();
    
    HumanPlayer hp("Marge");
    BadPlayer bp("Homer");
    Board b(3, 2);
    b.setBeans(SOUTH, 1, 3);
    
    Game g(b, &hp, &bp);
    g.display();
    g.play();
}

