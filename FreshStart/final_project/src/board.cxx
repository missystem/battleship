#include "board.hxx"
#include <algorithm>

using namespace ge211;

Board::Board(Dimensions dims)
        : dims_(dims)
{
    if (dims_.width < 10 || dims_.height < 20) {
        throw Client_logic_error("Board::Board: dims too small");
    }

    if (dims_.width > 10 ||
        dims_.height > 20) {
        throw Client_logic_error("Board::Board: dims too large");
    }
}

Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_position(Position pos, Player player) const
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

size_t
Board::count_player(Player player) const
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

std::vector<Board::Dimensions> const&
Board::all_directions()
{
    static std::vector<Dimensions> result = build_directions();
    return result;
}

Board::Rectangle
Board::all_positions() const
{
    return Rectangle::from_top_left(the_origin, dims_);
}
