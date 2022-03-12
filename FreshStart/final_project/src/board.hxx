#include "player.hxx"
#include "move.hxx"

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Board
{
public:
    //
    // HELPFUL TYPE ALIASES
    //

    /// Board dimensions will use `int` coordinates.
    // 8x8 by default
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    // Positions on the board
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    // returns a set of positions (i.e., a contiguous rectangle)
    // used to help iterate over the board
    using Rectangle = ge211::Rect<int>;

    // Defined and documented below.
    class reference;

    static std::vector<Dimensions> const& all_directions();

private:
    //
    // PRIVATE DATA MEMBERS
    //

    Dimensions dims_;
    Position_set p1_ships;
    Position_set p2_ships;
    Position_set p1_hits;
    Position_set p2_hits;
    Position_set p1_misses;
    Position_set p2_misses;

public:

    explicit Board(Dimensions dims);

    Dimensions dimensions() const;

    bool good_position(Position, Player) const;

    void set_all(Position_set, Player);

    size_t count_player(Player) const;

    Rectangle all_positions() const;
}


