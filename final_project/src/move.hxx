/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#pragma once

#include "position_set.hxx"

#include <ge211.hxx>

#include <unordered_map>
#include <utility>

using Move = std::pair<ge211::Posn<int> const, Position_set>;

using Move_map = std::unordered_map<ge211::Posn<int>, Position_set>;

/// Prints a `Move`; suitable for debugging.
std::ostream&
operator<<(std::ostream&, Move const&);
