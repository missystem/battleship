#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
    void
    on_mouse_down(ge211::Mouse_button, ge211::Posn<int> physical_pos);
    void
    on_mouse_move(ge211::Posn<int> physical_move);
    ge211::Posn<int> mouse_position {0, 0};
};
