#include "game_state.hxx"

Game_State 
change_Game_State(Game_State);
{
    switch (Game_State) {
    case Game_State::pregame:
        return Game_State::gamestart;
    case Game_State::gamestart:
        return Game_State::gameend;
    default:
        return Game_State;
    }
}
