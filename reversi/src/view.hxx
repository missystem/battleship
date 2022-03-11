#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // TODO: your code here
    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Posn<int> physical_pos);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    // TODO: Add any public member functions you need.
    View::Position board_to_screen(Model::Position logical) const;
    Model::Position screen_to_board(View::Position physical) const;

private:
    Model const& model_;

    // TODO: Add any additional private members you need, such as helper
    // functions or sprites.
    ge211::Circle_sprite const dark_piece;
    ge211::Circle_sprite const small_dark_piece;
    ge211::Circle_sprite const light_piece;
    ge211::Circle_sprite const small_light_piece;

    ge211::Rectangle_sprite const gray_sprite;
    ge211::Rectangle_sprite const red_sprite;
    ge211::Rectangle_sprite const lime_sprite;
};
