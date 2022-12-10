#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "drawable.hpp"
#include "drawablecollection.hpp"
#include "ncurses.h"
#include <array>
#include <vector>

template <typename T>
class Obstacle : public Drawable<T> {
public:
  // All obstacles start outside of screen at same x and y value
  Obstacle() : Drawable<T>(COLS, LINES - 8){};
  static Obstacle<T> generate() { return {}; }
};

struct ObstacleImage1 {
  static constexpr std::array<std::array<char, 1>, 3> image_array{
      {{'X'}, {'X'}, {'X'}}};
};

using Obstacle1 = Obstacle<ObstacleImage1>;

struct ObstacleImage2 {
  static constexpr std::array<std::array<char, 2>, 3> image_array{
      {{'X', 'X'}, {'X', 'X'}, {'X', 'X'}}};
};

using Obstacle2 = Obstacle<ObstacleImage2>;

struct ObstacleImage3 {
  static constexpr std::array<std::array<char, 5>, 2> image_array{
      {{'-', '-', '-', '-', '-'}, {'|', ' ', ' ', ' ', '|'}}};
};

using Obstacle3 = Obstacle<ObstacleImage3>;

using ObstacleCollection = DrawableCollection<Obstacle1, Obstacle2, Obstacle3>;

#endif
