#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

View::View(Model const& model)
        : model_(model),
          dark_piece(grid_size / 3, Color::medium_red()),
          small_dark_piece(grid_size / 4, Color::black()),
          light_piece(grid_size / 3, Color::white()),
          small_light_piece(grid_size / 4, Color::white()),

          gray_sprite({grid_size, grid_size}, {128, 128, 128}),
          red_sprite({grid_size, grid_size}, Color::medium_red()),
          lime_sprite({grid_size-1, grid_size-1}, Color::medium_blue()),
          ship_sprite({grid_size-2, grid_size-2}, {64, 64, 64}),
          potential_attack_sprite({grid_size-1, grid_size-1},
                                  Color::medium_green()),
          PC_wins({grid_size-1, grid_size-1},
                                  Color::medium_cyan()),
          human_wins({grid_size-1, grid_size-1},
                                  Color::medium_yellow())

        // You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set, ge211::Posn<int> physical_pos)
{
    for (auto pos: model_.board()) {
        set.add_sprite(lime_sprite, board_to_screen(pos), 1);
        if(model_[pos] == Player::dark){
            // if(pos.y<10){
            // set.add_sprite(ship_sprite, board_to_screen(pos), 3);
            // }
        }
        if(model_[pos] == Player::light){

            set.add_sprite(light_piece, board_to_screen(pos), 4);
        }
        if(model_[pos] == Player::both){

            set.add_sprite(dark_piece, board_to_screen(pos), 4);
            // set.add_sprite(ship_sprite, board_to_screen(pos), 3);
        }
        if (model_.winner() == Player::dark)
        {
            set.add_sprite(PC_wins, board_to_screen(pos), 2);
            if(model_[pos] == Player::dark || model_[pos]== Player::both){
                // if(pos.y<10){
                set.add_sprite(ship_sprite, board_to_screen(pos), 3);
                // }
            }
        }
        if (model_.winner() == Player::light)
        {
            set.add_sprite(human_wins, board_to_screen(pos), 2);
            if(model_[pos] == Player::dark || model_[pos]== Player::both){
                // if(pos.y<10){
                set.add_sprite(ship_sprite, board_to_screen(pos), 3);
                // }
            }
        }
            // }


    }
    Move const *ppos = model_.find_move(physical_pos);
    if (ppos != nullptr)
    {
        for (auto pos: ppos->second)
        {
            set.add_sprite(potential_attack_sprite, board_to_screen(pos), 3);
        }
    }
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

Model::Position
View::screen_to_board(View::Position physical) const
{
    return {physical.x / grid_size, physical.y / grid_size};
}

