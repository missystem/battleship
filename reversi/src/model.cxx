#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

// Player turn_ --> current player in game
// Player winner_ --> winner of the game, if one exists
// Board board_ --> current game board
// Move_map next_moves_
//    |___ Set of all moves where current player can go next
Model::Model(int width, int height)
        : board_({width, height})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves
    compute_next_moves_();
}

Model::Rectangle
Model::board() const
{
    // rectangle containing ALL board all_positions
    return board_.all_positions();
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

const Move*
Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end()) {
        // Nothing was found, so return NULL (nullptr in C++)
        return nullptr;
    } else {
        // Dereferences the iterator to get the value then returns a pointer
        // to that value. This is safe as the pointer is to a value living
        // within the `next_moves_` structure.
        return &(*i);
    }
}

void
Model::play_move(Position pos)
{
    // returns if game is over
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    // find_move()
    //    |___ returns a pointer to the move based on the current position
    //    |___ i.e. can be used to determine if the current move is valid
    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
    // if (!movep) {
        throw Client_logic_error("Model::play_move: no such move");
    }

    // TODO: actually execute the move, advance the turn, refill
    // `next_moves_`, etc.
    really_play_move_(*movep);
}

//
// BELOW ARE HELPER FUNCTIONS
// Our tests will run on the public functions, not the helper functions
// However, these will be extremely useful in writing the above functions
//
Position_set
Model::find_flips_(Position current, Dimensions dir) const
{
    // TODO: HELPER FUNCTION
    // create an empty position set
    Position_set pset;
    /// iterate move by move in the specified direction, one step at a time,
    /// until we either (1) go out of the bounds or (2) reach a position that
    /// does not contain the opposite player
    while (true)
    {
        /// adding positions to it
        current = current + dir;
        if ((!board_.good_position(current) ||
            (board_[current] == Player::neither))) {
            return {};
        }
        /// if the current player (`turn_`) were to play at position `start`.
        if (board_[current] == turn_) {
            /// then it returns the `Position_set`
            return pset;
        }
        pset[current] = true;
    }

}

/// Given a pos, determine all of the other board pos that would be
// gained if the curr player went at this pos
// i.e., is this pos a viable move for the curr player?
Position_set
Model::evaluate_position_(Position pos) const
{
    // TODO: HELPER FUNCTION
    Position_set pset = {};
    // check if it’s unoccupied
    if (board_[pos] == Player::neither)
    {
        // loop over each board direction -- Board::all_directions()
        for (auto dir: Board::all_directions())
        {
            // for each direction, determine the pos that would flip &
            // keep track of these pos in a "Position_set" object as you iterate
            pset |= (find_flips_(pos, dir));
        }
    }
    // if at least one pos flips here, then this is a viable move
    // add the initial input position to the Position_set before returning
    if (!pset.empty()) {
        pset[pos] = true;
    }
    // if (pset.empty()) {
    //     return pset;
    // }
    // pset[pos] = true;
    return pset;
    // ^^^ this is wrong
}

/// Given the curr player's turn & the state of the board,
/// determine the next possible moves for the curr player
/// two cases:
/// (1) the opening phase (center four squares) or
/// (2) the main phase (everything after that)
void
Model::compute_next_moves_()
{
    // TODO: HELPER FUNCTION
    next_moves_.clear();
    // opening phase (center four squares)
    //      each unoccupied pos is valid move
    for (auto ct: board_.center_positions())
    {
        if (board_[ct] == Player::neither) {
            next_moves_[ct] = {ct};
        }
    }
    // main phase
    if (next_moves_.empty())
    {
        // loop over each board position -- board_.all_positions()
        // -- for each pos, check if anything flips (evaluate_position())
        for (auto pos: board_.all_positions())
        {
            // if something flips (a viable move),
            // evaluate each position in the board and
            // record each non-empty evaluation in next_moves_
            if (!evaluate_position_(pos).empty())
            {
                // add this to the next_moves_ field
                next_moves_[pos] = evaluate_position_(pos);
            }
        }
    }
}

// switches to the other player,
// computes the set of next moves for the new
bool
Model::advance_turn_()
{
    // TODO: HELPER FUNCTION
    // switch to the other player
    turn_ = other_player(turn_);
    // compute the set of viable moves for the new player
    compute_next_moves_();
    // return if any moves are available (next_moves_ is non-empty)
    //     this will be used to help us determine if the game is over yet
    //     i.e., if no moves are available for either player
    // if (next_moves_.empty()) {
    //     return false;
    // }
    // return true;
    return !(next_moves_.empty());
}

// compute a winner based on the number of occupied tiles for each player
void
Model::set_game_over_()
{
    // TODO: HELPER FUNCTION
    // set the player equal to neither (i.e., Player::neither)
    turn_ = Player::neither;
    // count the number of tiles occupied by each player (light & dark)
    // and set the winner accordingly
    if ((board_.count_player(Player::dark)) <
        (board_.count_player (Player::light))) {
        winner_ = Player::light;
    } else {
        winner_ = Player::dark;
    }
}

// given a move, set all relevant pos equal to the curr player
// (i.e., actually play this move)
// also check if the game is over
void
Model::really_play_move_(Move move)
{
    // TODO: HELPER FUNCTION
    // recall that a move maps a pos to a set of pos gained, so
    // move.second tells us all of the positions we gained
    // set each position in move.second to the curr player
    board_.set_all(move.second, turn_);
    // check if the game is over (call advance_turn_()) twice &
    // both times return false to make sure neither player can move,
    // ---> the game is over
    if (!advance_turn_()) {
        if (!advance_turn_()) {
            set_game_over_();
        }
    }
}
