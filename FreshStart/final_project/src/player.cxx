#include "player.hxx"

Player
other_player(Player player)
{
    switch (player) {
    case Player::p1:
        return Player::p2;
    case Player::p2:
        return Player::p1;
    default:
        return player;
    }
}