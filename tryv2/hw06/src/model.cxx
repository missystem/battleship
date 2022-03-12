#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(10, 10)
{ }

Model::Model(int width, int height)
        : board_({10, 10})
{
    set_ship_positions_p1();
    compute_next_moves_();
    // TODO: initialize `next_moves_` to `turn_`'s available moves
}

int RandomNumberGenerator( int min, int max )
{
    static std::random_device rd;
    static std::mt19937 generator( rd( ) );
    std::uniform_int_distribution<int> randomNumber( min, max );

    return randomNumber( generator );
}
void
Model::set_ship_positions_p1()
{
    Position_set p2;
    p2.clear();
    int size[5] = {5,4,3,2,2};
    std::cout << "Hello";
    srand(clock());
    for (int i = 0; i<5; i++)
    {
        int ship = size[i];
        int flag2 = 0;
        while(true) {
            Position_set pset2;
            pset2.clear();
            int hv2 = rand()%2;
            int x2 = rand()%20;
            int y2 = rand()%20;
            // int hv2 = RandomNumberGenerator(0, 1);
            // int x2 = RandomNumberGenerator(0, 19);
            // int y2 = RandomNumberGenerator(0, 19);
            if (x2 > 9) {
                x2 -= 10;
            }
            if (y2 > 9) {
                y2 -= 10;
            }
            for (int j = 0; j < ship; j++) {
                if (hv2 == 0) {
                    Position test = Posn<int>(x2 + j, y2);
                    if (board_.good_position(test) && p2[test] != true) {
                        flag2 += 1;
                        pset2[test] = true;
                    }
                } else {
                    Position test = Posn<int>(x2, y2 + j);
                    if (board_.good_position(test) && p2[test] != true) {
                        flag2 += 1;
                        pset2[test] = true;
                    }
                }
            }
            if (flag2 == ship) {
                p2 |= pset2;
                break;
                // printf("%")
            } else {
                pset2.clear();
                flag2 = 0;
            }
        }

    }
    board_.set_all(p2, turn_);
    p2.clear();
    other_player(turn_);
}

Model::Rectangle
Model::board() const
{
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
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
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

// Position_set
// Model::find_flips_(Position current, Dimensions dir) const
// {
//     // TODO: HELPER FUNCTION
//     // create an empty position set
//     Position_set pset;
//     /// iterate move by move in the specified direction, one step at a time,
//     /// until we either (1) go out of the bounds or (2) reach a position that
//     /// does not contain the opposite player
//     while (true)
//     {
//         /// adding positions to it
//         current = current + dir;
//         if ((!board_.good_position(current) ||
//              (board_[current] == Player::neither))) {
//             return {};
//         }
//         /// if the current player (`turn_`) were to play at position `start`.
//         if (board_[current] == turn_) {
//             /// then it returns the `Position_set`
//             return pset;
//         }
//         pset[current] = true;
//     }
//
// }

/// Given a pos, determine all of the other board pos that would be
// gained if the curr player went at this pos
// i.e., is this pos a viable move for the curr player?
Position_set
Model::evaluate_position_(Position pos) const
{
    // TODO: HELPER FUNCTION
    Position_set pset = {};
    if (board_[pos] == Player::neither)
    {
        pset[pos] = true;
    }
    if (board_[pos] == Player::dark) {
        pset[pos] = true;
    }
    return pset;
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
    for (auto pos: board_.all_positions())
    {
        if (!evaluate_position_(pos).empty())
        {
            next_moves_[pos] = evaluate_position_(pos);
        }
    }
}
bool
Model::advance_turn_()
{
    // TODO: HELPER FUNCTION
    return false;
    // ^^^ this is wrong
}

void
Model::set_game_over_()
{
    turn_ = Player::neither;
    // count the number of tiles occupied by each player (light & dark)
    // and set the winner accordingly
    int x = 0;
    for (auto pos: board_.all_positions())
    {
        if (board_[pos]==Player::both)
        {
            x +=1;
        }
    }
    next_moves_.clear();
    if (x>=16) {
        winner_ = Player::light;
    } else {
        winner_ = Player::dark;
    }
}

bool
Model::check_game_over_(){
    int x = 0;
    int y = 0;
    for (auto pos: board_.all_positions())
    {
        if (board_[pos]==Player::both)
        {
            x +=1;
            y+=1;
        }
        if (board_[pos]==Player::light)
        {
            y +=1;
        }
    }
    if(x==16 || y==50){
        return true;
    }
    else{
        compute_next_moves_();
        return false;
    }
}

void
Model::really_play_move_(Move move)
{
    board_.set_all(move.second, Player::light);
    bool x = check_game_over_();
    if(x){
        set_game_over_();
    }
}
