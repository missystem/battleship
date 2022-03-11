#pragma once

enum class Game_State
{
    pregame,
   	gamestart,
    gameend,
};

// Returns the other player.
Game_State change_Game_State(Game_State);