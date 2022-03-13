#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(20, 20)
{ }

Model::Model(int width, int height)
        : board_({20, 20})
{
    set_ship_positions_p2();
    set_ship_positions_p1();
    compute_next_moves_();
}

void
Model::set_ship_positions_p1()
{
    Position_set p2;
    p2.clear();
    int size[5] = {5,4,3,2,2};
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
                    Position test2 = Posn<int>(x2 + j +10, y2);
                    if (board_.good_position_p1(test) && p2[test] != true) {
                        flag2 += 1;
                        pset2[test] = true;
                        pset2[test2] = true;
                    }
                } else {
                    Position test = Posn<int>(x2, y2 + j);
                    Position test2 = Posn<int>(x2 + 10, y2+j);
                    if (board_.good_position_p1(test) && p2[test] != true) {
                        flag2 += 1;
                        pset2[test] = true;
                        pset2[test2] = true;
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
    turn_ = other_player(turn_);
}
void
Model::set_ship_positions_p2()
{
    Position_set p2;
    Position_set p3;
    p2.clear();
    p3.clear();
    int size[5] = {5,4,3,2,2};
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
            if (x2 < 10) {
                x2 += 10;
            }
            if (y2 < 10) {
                y2 += 10;
            }
            for (int j = 0; j < ship; j++) {
                if (hv2 == 0) {
                    Position test = Posn<int>(x2 + j, y2);
                    Position test2 = Posn<int>(x2 + j - 10, y2);
                    if (board_.good_position_p2(test) && p2[test] != true) {
                        flag2 += 1;
                        pset2[test] = true;
                        pset2[test2] = true;
                    }
                } else {
                    Position test = Posn<int>(x2, y2 + j);
                    Position test2 = Posn<int>(x2 - 10, y2 +j);
                    if (board_.good_position_p2(test) && p2[test] != true) {
                        flag2 += 1;
                        pset2[test] = true;
                        pset2[test2] = true;
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
    turn_ = other_player(turn_);
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

void
Model::set_time_delay(int x)
{
    Model::timedelay = x;
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
    really_play_move_(*movep);
}

Position_set
Model::evaluate_position_(Position pos) const
{
    Position_set pset = {};
    if(turn_==Player::dark) {
        if (pos.x < 10 && pos.y < 10) {
            Position test2 = Posn<int>(pos.x + 10, pos.y);
            if (board_[pos] == Player::neither) {
                pset[pos] = true;
                pset[test2] = true;
            }
            if (board_[pos] == Player::light) {
                pset[pos] = true;
                pset[test2] = true;
            }
        }
    }
    else if(turn_==Player::light) {
            Position test2 = Posn<int>(pos.x - 10, pos.y);
            if (pos.x >= 10 && pos.y >= 10) {
                if (board_[pos] == Player::neither) {
                    pset[pos] = true;
                    pset[test2] = true;
                }
                if (board_[pos] == Player::dark) {
                    pset[pos] = true;
                    pset[test2] = true;
                }
            }
        }
    return pset;
}

void
Model::compute_next_moves_()
{
    next_moves_.clear();
    for (auto pos: board_.all_positions())
    {
        if (!evaluate_position_(pos).empty())
        {
            next_moves_[pos] = evaluate_position_(pos);
        }
    }
}

void
Model::set_game_over_()
{
    turn_ = Player::neither;
    next_moves_.clear();
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
    int p1count = 0;
    int p2count = 0;
    if (x>=16){
        for (auto pos: board_.all_positions())
        {
            if(pos.x < 10 && pos.y < 10){
                if (board_[pos]==Player::both)
                {
                    p1count +=1;
                }
            }
            if(pos.x >= 10 && pos.y >= 10){
                if (board_[pos]==Player::both)
                {
                    p2count +=1;
                }
            }
        }
    }

    if (p1count>=16) {
        winner_ = Player::dark;
    } else {
        winner_ = Player::light;
    }
}

bool
Model::check_game_over_(){
    int x = 0;
    for (auto pos: board_.all_positions())
    {
        if (board_[pos]==Player::both)
        {
            x +=1;
        }
    }
    int p1count = 0;
    int p2count = 0;
    if (x>=16){
        for (auto pos: board_.all_positions())
        {
            if(pos.x < 10 && pos.y < 10){
                if (board_[pos]==Player::both)
                {
                    p1count +=1;
                }
            }
            if(pos.x >= 10 && pos.y >= 10){
                if (board_[pos]==Player::both)
                {
                    p2count +=1;
                }
            }
        }
    }
    if(p2count==16 || p1count==16){
        return true;
    }
    else{
        sleep(timedelay);
        turn_ = other_player(turn_);
        compute_next_moves_();
        return false;
    }
}

void
Model::really_play_move_(Move move)
{
    board_.set_all(move.second, turn_);

    bool x = check_game_over_();
    if(x){
        set_game_over_();
    }
}
