/*************************************************/
/*** DO NOT CHANGE THE PUBLIC API IN THIS FILE ***/
/*************************************************/
//
// You may add private members if you like, or even remove
// the private helper functions, but you mustn't change the
// existing public members, nor add new ones. If you do, your
// code may not build for automated tests.

#pragma once

#include "player.hxx"
#include "board.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>
#include <unistd.h>

class Model
{
public:

    using Dimensions = Board::Dimensions;

    using Position = Board::Position;

    using Rectangle = Board::Rectangle;

    explicit Model(int size = 8);

    Model(int width, int height);

    Rectangle board() const;

    bool is_game_over() const
    { return turn() == Player::neither; }

    Player turn() const
    { return turn_; }

    Player winner() const
    { return winner_; }

    Player operator[](Position) const;
    const Move* find_move(Position) const;
    void play_move(Position);
    void
    set_ship_positions_p1();
    void
    set_ship_positions_p2();
    Player turn_   = Player::dark;
    int timedelay = 3;
    void set_time_delay(int x);

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

private:

    Player winner_ = Player::neither;
    Board board_;

    Move_map next_moves_;

    Position_set find_flips_(Position start, Dimensions dir) const;

    Position_set evaluate_position_(Position) const;

    void compute_next_moves_();

    bool advance_turn_();

    void set_game_over_();

    void really_play_move_(Move move);

    bool
    check_game_over_();
};

