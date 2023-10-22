//  Side.h

#ifndef SIDE_H
#define SIDE_H

// If used where an int is required, NORTH will automatically convert to 0, and SOUTH to 1
enum Side { NORTH, SOUTH };

const int NSIDES = 2;

// A pot is considered hole #0
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

// It may contain additional types, constants, and non-member function declarations that you find useful to add.

#endif /* SIDE_H */
