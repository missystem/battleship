#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set,  ge211::Posn<int> physical_pos);
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;
    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;
    View::Position board_to_screen(Model::Position logical) const;
    Model::Position screen_to_board(View::Position physical) const;

private:
    Model const& model_;
    ge211::Circle_sprite const hit;
    ge211::Circle_sprite const miss;

    ge211::Rectangle_sprite const fiveship_p1_v;
    ge211::Rectangle_sprite const fourship_p1_v;
    ge211::Rectangle_sprite const threeship_p1_v;
    ge211::Rectangle_sprite const twoship1_p1_v;
    ge211::Rectangle_sprite const twoship2_p1_v;
    ge211::Rectangle_sprite const fiveship_p2_v;
    ge211::Rectangle_sprite const fourship_p2_v;
    ge211::Rectangle_sprite const threeship_p2_v;
    ge211::Rectangle_sprite const twoship1_p2_v;
    ge211::Rectangle_sprite const twoship2_p2_v;

    ge211::Rectangle_sprite const fiveship_p1_h;
    ge211::Rectangle_sprite const fourship_p1_h;
    ge211::Rectangle_sprite const threeship_p1_h;
    ge211::Rectangle_sprite const twoship1_p1_h;
    ge211::Rectangle_sprite const twoship2_p1_h;
    ge211::Rectangle_sprite const fiveship_p2_h;
    ge211::Rectangle_sprite const fourship_p2_h;
    ge211::Rectangle_sprite const threeship_p2_h;
    ge211::Rectangle_sprite const twoship1_p2_h;
    ge211::Rectangle_sprite const twoship2_p2_h;

    ge211::Rectangle_sprite const possiblesprite;

    ge211::Rectangle_sprite const spritewin;
    ge211::Rectangle_sprite const blue_sprite;
    ge211::Rectangle_sprite const red_sprite;
};
