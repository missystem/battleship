#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

TEST_CASE("Initialization")
{
    Model m(20, 20);
    m.set_time_delay(0);
    CHECK(m.board() == Model::Rectangle {0, 0, 20, 20});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
}

// This should pass.
TEST_CASE("Success with intialization: find_move")
{
    Model m(6);
    m.set_time_delay(0);
    CHECK(m.find_move({2, 2}));
}

// This should pass.
TEST_CASE("Success with intialization: play_move")
{
    Model m(4);
    m.set_time_delay(0);
    m.play_move({1, 1});
}

// out of range.
TEST_CASE("Fails with intialization: find_move")
{
    Model m(20);
    m.set_time_delay(0);
    CHECK(m.find_move({21, 21}) == nullptr);
}

// out of range.
TEST_CASE("Throws with intialization: play_move")
{
    Model m(20);
    m.set_time_delay(0);
    CHECK_THROWS_AS(m.play_move({21, 21}), Client_logic_error);
}

struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    // Sets the player at `posn` to `player`.
    void set_player(Model::Position posn, Player player);
    // Gives direct access to `model.next_moves_` so our tests can modify it:
    Move_map& next_moves();
};

TEST_CASE("Check that player 1 places missile first and cannot access player 2 board")
{

    Model m(20, 20);
    m.set_time_delay(0);
    CHECK(m.board() == Model::Rectangle {0, 0, 20, 20});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    for(int i = 10; i< 19; i++){
        for(int j = 10; j<19; j++){
            CHECK_THROWS(m.play_move({i,j}));
        }
    }
    m.play_move({0,0});
    CHECK(m.turn() == Player::light);
    CHECK(m.winner() == Player::neither);
    bool dark = m[{0, 0}] == Player::dark;
    bool both = m[{0, 0}] == Player::both;
    CHECK_FALSE(m[{0, 0}] == Player::light);
    CHECK_FALSE(m[{0, 0}] == Player::neither);
    bool testing = dark || both;
    CHECK(testing);

}

TEST_CASE("Check that player2 must place second missile and cannot place on player 1 board")
{

    Model m(20, 20);
    m.set_time_delay(0);
    CHECK(m.board() == Model::Rectangle {0, 0, 20, 20});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    m.play_move({0,0});
    CHECK(m.turn() == Player::light);
    CHECK(m.winner() == Player::neither);
    for(int i = 0; i< 10; i++){
        for(int j = 0; j<10; j++){
            CHECK_THROWS(m.play_move({i,j}));
        }
    }
    m.play_move({10,10});
    bool dark = m[{10, 10}] == Player::light;
    bool both = m[{10, 10}] == Player::both;
    CHECK_FALSE(m[{10, 10}] == Player::dark);
    CHECK_FALSE(m[{10, 10}] == Player::neither);
    bool testing = dark || both;
    CHECK(testing);
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
}

TEST_CASE("Check that a location that has been hit cannot be hit again by the player")
{

    Model m(20, 20);
    m.set_time_delay(0);
    CHECK(m.board() == Model::Rectangle {0, 0, 20, 20});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    m.play_move({0,0});
    CHECK(m.turn() == Player::light);
    CHECK(m.winner() == Player::neither);
    m.play_move({10,10});
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    CHECK_THROWS(m.play_move({0,0}));
    m.play_move({1,1});
    CHECK(m.turn() == Player::light);
    CHECK(m.winner() == Player::neither);
    bool dark = m[{0, 0}] == Player::dark;
    bool both = m[{0, 0}] == Player::both;
    CHECK_FALSE(m[{0, 0}] == Player::light);
    CHECK_FALSE(m[{0, 0}] == Player::neither);
    bool testing = dark || both;
    CHECK(testing);
    dark = m[{1, 1}] == Player::dark;
    both = m[{1, 1}] == Player::both;
    CHECK_FALSE(m[{1, 1}] == Player::light);
    CHECK_FALSE(m[{1, 1}] == Player::neither);
    testing = dark || both;
    CHECK(testing);

    CHECK_THROWS(m.play_move({10,10}));
    m.play_move({11,11});
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    dark = m[{10, 10}] == Player::light;
    both = m[{10, 10}] == Player::both;
    CHECK_FALSE(m[{10, 10}] == Player::dark);
    CHECK_FALSE(m[{10, 10}] == Player::neither);
    testing = dark || both;
    CHECK(testing);
    dark = m[{11, 11}] == Player::light;
    both = m[{11, 11}] == Player::both;
    CHECK_FALSE(m[{11, 11}] == Player::dark);
    CHECK_FALSE(m[{11, 11}] == Player::neither);
    testing = dark || both;
    CHECK(testing);

}

TEST_CASE("Check that no player can attack board that showcases their own ships and opponent hits")
{

    Model m(20, 20);
    m.set_time_delay(0);
    CHECK(m.board() == Model::Rectangle {0, 0, 20, 20});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    for(int i = 0; i< 10; i++){
        for(int j = 10; j<20; j++){
            CHECK_THROWS(m.play_move({i,j}));
        }
    }
    m.play_move({0,0});
    CHECK(m.turn() == Player::light);
    CHECK(m.winner() == Player::neither);
    for(int i = 10; i< 20; i++){
        for(int j = 0; j<10; j++){
            CHECK_THROWS(m.play_move({i,j}));
        }
    }
    m.play_move({10,10});
    bool dark = m[{10, 10}] == Player::light;
    bool both = m[{10, 10}] == Player::both;
    CHECK_FALSE(m[{10, 10}] == Player::dark);
    CHECK_FALSE(m[{10, 10}] == Player::neither);
    bool testing = dark || both;
    CHECK(testing);
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
}

TEST_CASE("Check Full Game End Result")
{
    Model m(20, 20);
    m.set_time_delay(0);
    CHECK(m.board() == Model::Rectangle {0, 0, 20, 20});
    CHECK_FALSE(m.is_game_over());
    int flag = 0;
    for(int i = 0; i< 10; i++){
        for(int j = 0; j<10; j++){
            if(m.winner() == Player::neither) {
                m.play_move({i,j});
            }
            if(m.winner() == Player::neither) {
                m.play_move({i+10,j+10});
            }
            if(!(m.winner() == Player::neither)){
                if(m.winner() == Player::dark){
                    flag = 1;
                    CHECK(m.turn() == Player::neither);
                }
                else if(m.winner() == Player::light){
                    flag = 2;
                    CHECK(m.turn() == Player::neither);
                }
                break;
            }
        }
        if(flag==1 || flag == 2){
            break;
        }
    }
    CHECK(m.turn() == Player::neither);
    int hitsp1 = 0;
    int hitsp2 = 0;
    for(int i = 0; i< 10; i++){
        for(int j = 0;j < 10; j++){
            if (m[{i, j}] == Player::both){
                hitsp1+=1;
            }
            if (m[{i+10, j+10}] == Player::both){
                hitsp2+=1;
            }
        }
    }
    CHECK_FALSE(m.winner()==Player::neither);
    if(m.winner()==Player::dark){
        CHECK(hitsp1==16); // 16 = 5 + 4 + 3 + 2 + 2 which is the
        // total number of ship pieces
        // that must be hit
        CHECK_FALSE(hitsp2==16);
    }
    if(m.winner()==Player::light){
        CHECK(hitsp2==16);
        CHECK_FALSE(hitsp1==16);
    }
    CHECK_THROWS(m.play_move({19,19}));
    CHECK_THROWS(m.play_move({9,9}));
}
