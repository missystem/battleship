#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

View::View(Model const& model)
        : model_(model),
        // You may want to add sprite initialization here
          dark_piece(grid_size / 2, Color::black()),
          small_dark_piece(grid_size / 4, Color::black()),
          light_piece(grid_size / 2, Color::white()),
          small_light_piece(grid_size / 4, Color::white()),

          gray_sprite({grid_size, grid_size}, {128, 128, 128}),
          red_sprite({grid_size, grid_size}, Color::medium_red()),
          lime_sprite({grid_size-1, grid_size-1}, Color::medium_green())
{ }

// responsible for determining what appears on the screen
// add at least one parameter to it
// so that the controller can communicate control state to the view
// board_to_screen()
//     takes a board pos (e.g., {1, 1}) & converts it into
//     a physical pos in terms of pixels on the screen (e.g., {60, 60})
// screen_to_board()
//     takes a physical pos in terms of pixels (e.g., {120, 120}) &
//     converts it into a pos on the board
// add_player_sprite()
//     based on the curr player (light vs. dark) &
//     state of the game (i.e., is it over),
//     render sprites appropriately
//         Hint: The add_sprite() function can take a 3rd argument (z-layer)
//         that helps place objects above or below others
// when you add sprites to the screen, be careful how you layer things
//     for instance, board pos where players have already made moves should
//         be higher than everything else (i.e., the highest z-coordinate)
//     the actually tiles at the start should be lower than everything else
//     etc.
void View::draw(Sprite_set& set, ge211::Posn<int> physical_pos)
{
    // TODO, PROBABLY
    for (auto pos: model_.board())
    {
        set.add_sprite(lime_sprite, board_to_screen(pos), 1);
        if (model_[pos] == Player::dark)
        {
            if (model_.winner() == Player::dark)
            {
                set.add_sprite(gray_sprite, board_to_screen(pos), 2);
            }
            set.add_sprite(dark_piece, board_to_screen(pos), 3);
        }

        if (model_[pos] == Player::light)
        {
            if (model_[pos] == Player::light)
            {
                set.add_sprite(gray_sprite, board_to_screen(pos), 2);
            }
            set.add_sprite(light_piece, board_to_screen(pos), 3);
        }

        if (model_[pos] == Player::neither)
        {
            if (pos == physical_pos)
            {
                if (model_.turn() == Player::dark)
                {
                    set.add_sprite(small_dark_piece, board_to_screen(pos), 5);
                }
                if (model_.turn() == Player::light)
                {
                    set.add_sprite(small_light_piece, board_to_screen(pos), 5);
                }
            }
        }

    }

    Move const *ppos = model_.find_move(physical_pos);
    if (ppos != nullptr)
    {
        for (auto pos: ppos->second)
        {
            set.add_sprite(red_sprite, board_to_screen(pos), 2);
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
    return "Reversi";
}

// TODO: board_to_screen() & screen_to_board()
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