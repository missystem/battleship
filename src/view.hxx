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
    explicit View(Model const&, ge211::Mixer& mixer);

    // TODO: your code here
    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Posn<int> physical_pos);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;
    void set_animating(bool);

    /// Plays hit.mp3
    void play_hit_effect() const;
    /// Plays miss.mp3
    void play_miss_effect() const;
    void play_winner_effect() const;

    void play_p1_wins_effect() const;
    void play_p2_wins_effect() const;

    /// Keeps the music going.
    void resume_music_if_ended() const;

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

    ge211::Rectangle_sprite const lime_sprite2;
    ge211::Rectangle_sprite const ship_sprite;
    ge211::Rectangle_sprite const potential_attack_sprite;
    ge211::Rectangle_sprite const PC_wins;
    ge211::Rectangle_sprite const human_wins;
    ge211::Rectangle_sprite const black;
    ge211::Rectangle_sprite const transparent;
    ge211::Rectangle_sprite const lightgreyfilter;

    void load_audio_();
    // For audio:
    ge211::Mixer& mixer_;
    ge211::Music_track bg_music_;
    ge211::Sound_effect hit_sound_;
    ge211::Sound_effect miss_sound_;
    ge211::Sound_effect_handle success_handle_;
    ge211::Sound_effect winner_sound_;
    ge211::Sound_effect p1_wins_sound_;
    ge211::Sound_effect p2_wins_sound_;
};
