#include "ship.hxx"

Ship
change_Ship(Ship);
{
    switch (Ship) {
    case Ship::fiveship:
        return Ship::fourship:;
    case Ship::fourship::
        return Ship::threeship:;
    case Ship::threeship:
        return Ship::twoship1:;
    case Ship::twoship1::
        return Ship::twoship2:;
    default:
        return Ship;
    }
}
