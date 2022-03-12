#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites, mouse_position);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int> physical_pos)
{
    ge211::Posn<int> board_pos = view_.screen_to_board(physical_pos);

    if (model_.find_move(board_pos) != nullptr)
    {
        model_.play_move(model_.find_move(board_pos)->first);
    }
}

// check if the move is valid
void
Controller::on_mouse_move(ge211::Posn<int> physical_move)
{
    mouse_position = view_.screen_to_board(physical_move);
}


