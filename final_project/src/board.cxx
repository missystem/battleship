/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "board.hxx"
#include <algorithm>

using namespace ge211;

Board::Board(Dimensions dims)
        : dims_(dims)
{
    if (dims_.width < 10 || dims_.height < 20) {
        throw Client_logic_error("Board::Board: dims too small");
    }

    if (dims_.width > 10 || dims_.height > 20) {
        throw Client_logic_error("Board::Board: dims too large");
    }
}

Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_attack_position(Position pos, Player player) const
{
    if (player == Player::p1){
        return 0 <= pos.x && pos.x < 10 &&
               10 <= pos.y && pos.y < 20;
    }
    else if (player == Player::p2){
        return 0 <= pos.x && pos.x < 10 &&
               0 <= pos.y && pos.y < 10;
    }
    return false;
}

// Player
// Board::operator[](Position pos, Player player) const
// {
//     bounds_check_(pos, player);
//     return get_(pos);
// }

// Board::reference
// Board::operator[](Position pos, Player player)
// {
//     // bounds_check_(pos, player);
//     return reference(*this, pos);
// }

size_t
Board::count_player_hits(Player player) const
{
    switch (player) {
    case Player::p1:
        return p1_hits.size();
    case Player::p2:
        return p2_hits.size();
    default:
        return dims_.width * dims_.height -
               p1_hits.size() - p2_hits.size();
    }
}

// Board::Rectangle
// Board::center_positions() const
// {
//     ;
// }

static std::vector<Board::Dimensions>
build_directions()
{
    std::vector<Board::Dimensions> result;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx || dy) {
                result.push_back({dx, dy});
            }
        }
    }

    return result;
}

// std::vector<Board::Dimensions> const&
// Board::all_directions()
// {
// ;
// }

Board::Rectangle
Board::all_positions() const
{
    return Rectangle::from_top_left(the_origin, dims_);
}

// bool
// operator==(Board const& b1, Board const& b2)
// {
//     return b1.dims_ == b2.dims_ &&
//            b1.light_ == b2.light_ &&
//            b1.dark_ == b2.dark_;
// }

// Player
// Board::get_(Position pos) const
// {
//     if (dark_[pos]) {
//         return Player::dark;
//     } else if (light_[pos]) {
//         return Player::light;
//     } else {
//         return Player::neither;
//     }
// }

// void
// Board::set_(Position pos, Player player)
// {
//     switch (player) {
//     case Player::dark:
//         dark_[pos] = true;
//         light_[pos] = false;
//         break;
//
//     case Player::light:
//         dark_[pos] = false;
//         light_[pos] = true;
//         break;
//
//     default:
//         dark_[pos] = false;
//         light_[pos] = false;
//     }
// }

// void
// Board::set_all(Position_set pos_set, Player player)
// {
//     switch (player) {
//     case Player::light:
//         light_ |= pos_set;
//         dark_ &= ~pos_set;
//         break;
//
//     case Player::dark:
//         dark_ |= pos_set;
//         light_ &= ~pos_set;
//         break;
//
//     default:
//         dark_ &= ~pos_set;
//         light_ &= ~pos_set;
//     }
// }

void
Board::bounds_check_(Position pos, Player player) const
{
    if (!good_attack_position(pos, player)){
        throw Client_logic_error("Board: position out of bounds");
    }
}

bool
operator!=(Board const& b1, Board const& b2)
{
    return !(b1 == b2);
}

// std::ostream&
// operator<<(std::ostream& os, Board const& board)
// {
//     Board::Dimensions dims = board.dimensions();
//
//     for (int y = 0; y < dims.height; ++y) {
//         for (int x = 0; x < dims.width; ++x) {
//             os << board[{x, y}];
//         }
//         os << "\n";
//     }
//
//     return os;
// }

Board::reference::reference(Board& board, Position pos) noexcept
        : board_(board),
          pos_(pos)
{ }

Board::reference&
Board::reference::operator=(reference const& that) noexcept
{
    *this = Player(that);
    return *this;
}

Board::reference&
Board::reference::operator=(Player player) noexcept
{
    board_.set_(pos_, player);
    return *this;
}

Board::reference::operator Player() const noexcept
{
    return board_.get_(pos_);
}

Board::multi_reference
Board::at_set(Position_set pos_set)
{
    return multi_reference(*this, pos_set);
}

Board::multi_reference::multi_reference(
        Board& board,
        Position_set pos_set) noexcept
        : board_(board),
          pos_set_(pos_set)
{ }

Board::multi_reference&
Board::multi_reference::operator=(Player player) noexcept
{
    board_.set_all(pos_set_, player);
    return *this;
}

