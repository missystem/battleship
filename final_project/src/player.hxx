#pragma once

// A player or lack thereof.
enum class Player
{
    p1,
    p2,
    neither,
};

// Returns the other player.
Player other_player(Player);