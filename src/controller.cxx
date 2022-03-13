#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_, mixer())
{ }
void
Controller::on_frame(double dt)
{
    animation_seconds_ += dt;
    view_.set_animating(animating_);
    view_.resume_music_if_ended();
}

void
Controller::on_start()
{
    start_animation_();
}

void
Controller::start_animation_()
{
    animating_ = true;
    animation_seconds_ = 0;
    animation_step_ = 0;
}

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
        if (model_[board_pos] == Player::neither){
            view_.play_miss_effect();
        }
        else {
            view_.play_hit_effect();
        }
        model_.play_move(model_.find_move(board_pos)->first);
        if (model_.winner() != Player::neither) {
            if (model_.winner() != Player::light) {
                view_.play_p1_wins_effect();
                view_.play_winner_effect();
            } else {
                view_.play_p2_wins_effect();
                view_.play_winner_effect();
            }
        }
    }
}

// check if the move is valid
void
Controller::on_mouse_move(ge211::Posn<int> physical_move)
{
    mouse_position = view_.screen_to_board(physical_move);
}


