#include "controller.hxx"

Controller::Controller()
        : model_(10,21),
        view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse_position);
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int> physical_pos)
{
    // ge211::Posn<int> board_pos = view_.screen_to_board(physical_pos);
    //
    // if (model_.find_valid_move(board_pos))
    // {
    //     model_.play_move(board_pos);
    // }
}

void
Controller::on_mouse_move(ge211::Posn<int> physical_move)
{
    // mouse_position = view_.screen_to_board(physical_move);
}


