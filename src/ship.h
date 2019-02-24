// ship.h
// Simeon Ng
// Jason Herning
// Updated: 2/23/19
// Ship Class Header File

#ifndef CS372_BATTLESHIP_SHIP_H
#define CS372_BATTLESHIP_SHIP_H

#include <iostream>
#include <cstddef>
#include <vector>
#include <cmath>
#include "board.h"

using std::cout;
using std::endl;
using std::vector;

//To Do:
// -find way to hold locations of shots
//

//Ship
//size will always be from size 1-5
//position will always be from 1-100
class Ship {

public:
    Ship(Coords c1, Coords c2);

    size_t getLength();
    Coords getBegin() const;
    Coords getEnd() const;

    void attack(const Coords& c);
    bool isSunk() const;

private:
    const Coords _begin;    // Coords of Beginning of ship
    const Coords _end;      // Coords of End of ship
    bool _orientation;      // Orientation of ship;
                            // True == Horizontal, False == Vertical
    vector<bool> _hits;

};


#endif //CS372_BATTLESHIP_SHIP_H
