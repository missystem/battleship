#include "view.hxx"

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static int const grid_size = 36;

View::View(Model const& model)
        : model_(model),
          hit(grid_size / 2,{255,0, 0}),
          miss(grid_size / 4, Color::white()),
          fiveship_p1_v({grid_size-1,5*grid_size},{128, 128, 128}),
          fourship_p1_v({grid_size-1, 4*grid_size},{128, 128, 128}),
          threeship_p1_v({grid_size-1, 3*grid_size},{128, 128, 128}),
          twoship1_p1_v({grid_size-1, 2*grid_size},{128, 128, 128}),
          twoship2_p1_v({grid_size-1, 2*grid_size},{128, 128, 128}),
          fiveship_p2_v({grid_size-1, 5*grid_size},{128, 128, 128}),
          fourship_p2_v({grid_size-1, 4*grid_size},{128, 128, 128}),
          threeship_p2_v({grid_size-1, 3*grid_size},{128, 128, 128}),
          twoship1_p2_v({grid_size-1, 2*grid_size},{128, 128, 128}),
          twoship2_p2_v({grid_size-1, 2*grid_size},{128, 128, 128}),
          fiveship_p1_h({5*grid_size, grid_size-1},{128, 128, 128}),
          fourship_p1_h({4*grid_size, grid_size-1},{128, 128, 128}),
          threeship_p1_h({3*grid_size, grid_size-1},{128, 128, 128}),
          twoship1_p1_h({2*grid_size, grid_size-1},{128, 128, 128}),
          twoship2_p1_h({2*grid_size, grid_size-1},{128, 128, 128}),
          fiveship_p2_h({5*grid_size, grid_size-1},{128, 128, 128}),
          fourship_p2_h({4*grid_size, grid_size-1},{128, 128, 128}),
          threeship_p2_h({3*grid_size, grid_size-1},{128, 128, 128}),
          twoship1_p2_h({2*grid_size, grid_size-1},{128, 128, 128}),
          twoship2_p2_h({2*grid_size, grid_size-1},{128, 128, 128}),

          possiblesprite({grid_size, grid_size}, Color::medium_green()),

          spritewin({grid_size-1, grid_size-1},Color::medium_green()),
          blue_sprite({grid_size-1, grid_size-1},Color::medium_blue()),

          red_sprite({grid_size-1, grid_size-1},Color::medium_red())
{ }

void
View::draw(ge211::Sprite_set& set, ge211::Posn<int> physical_pos)
{
    // Move const *ppos = model_.find_valid_move(physical_pos);
    // if (ppos != nullptr)
    // {
    //     for (auto pos: ppos->second)
    //     {
    //         set.add_sprite(red_sprite,
    //                        board_to_screen(pos), 10);
    //     }
    // }

}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Battleship";
}

View::Position
View::board_to_screen(Model::Position logical) const
{
    return {logical.x * grid_size, logical.y * grid_size};
}