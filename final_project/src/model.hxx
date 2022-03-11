#pragma once

#include "player.hxx"
#include "game_state.hxx"
#include "ship.hxx"
#include "board.hxx"

#include <ge211.hxx>

class Model
{
public:
    using Dimensions = Board::Dimensions;

    /// Model positions will use `int` coordinates, as board positions do.
    using Position = Board::Position;

    /// Model rectangles will use `int` coordinates, as board rectangles do.
    using Rectangle = Board::Rectangle;
    Model(int width, int height);

    Rectangle board() const;

    /// Returns whether the game is finished. This is true when neither
    /// player can move.
    bool is_game_over() const
    { return turn() == Player::neither; }

    /// Returns the current turn, or `Player::neither` if the game is
    /// over.
    Game_State gamestate() const
    { return game_state_; }

    Player turn() const
    { return turn_; }

    /// Returns the winner, or `Player::neither` if there is no winner
    /// (either because the game isn't over, or because it's a draw).
    Player winner() const
    { return winner_; }

    /// Returns the player at the given position, or `Player::neither` if
    /// the position is unoccupied.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if the position is out of
    ///    bounds.
    // Player operator[](Position) const;
    const Move* find_valid_move(Position) const;
    void play_move(Position);

private:
    Player turn_   = Player::p1;
    Player winner_ = Player::neither;
    Game_State game_state_ = Game_State::pregame;
    Ship p1 = Ship::fiveship;
    Ship p2 = Ship::fiveship;

    Board board_;
    Move_map next_moves_;

    bool advance_turn_();
    void set_game_over_();
    void really_play_move_(Move move);

    void
    p1_pregame();
    void
    p2_pregame();
};
