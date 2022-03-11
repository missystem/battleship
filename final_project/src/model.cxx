
#include "model.hxx"

using namespace ge211;
Model::Model(int size)
        : Model(10, size)
{ }

Model::Model(int width, int height)
        : board_({10, 20})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves
    // p1_pregame();
    // p2_pregame();
}

Model::Rectangle
Model::board() const
{
    return board_.all_positions();
}

void
Model::p1_pregame()
{

}

void
Model::p2_pregame()
{

}
