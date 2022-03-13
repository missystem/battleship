#pragma once

#include "model.hxx"
#include "view.hxx"

// The main game class for Reversi.
class Controller : public ge211::Abstract_game
{
public:

    // Constructs a game with `size` as both its width and height.
    //

    explicit Controller(int size = 10);

    // Constructs a game with the given width and height.
    //
    // ERRORS:

    Controller(int width, int height);

// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //
    void on_mouse_down(ge211::Mouse_button, ge211::Posn<int>) override;
    // if you want to react to mouse motion
    void on_mouse_move(ge211::Posn<int>) override;

    void on_frame(double) override;

    void on_start() override;
    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View  view_;
    ge211::Posn<int> mouse_position {0, 0};
    void start_animation_();
    bool animating_ = true;
    double animation_seconds_ = 0;
    unsigned long animation_step_ = 0;

};
