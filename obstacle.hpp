#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "drawable.hpp"
#include "drawablecollection.hpp"
#include "ncurses.h"
#include <array>

template <typename T> class Obstacle : public Drawable<T> {
public:
  // All obstacles start outside of screen at same x and y value
  Obstacle() : Drawable<T>(COLS, LINES - 8){};
  Obstacle(int x) : Drawable<T>(x, LINES - 8){};
  static Obstacle<T> generate() { return {}; }
  static Obstacle<T> generate_x(int x) { return Obstacle(x); }
};

struct ObstacleImage1 {
  static constexpr std::array<std::array<char, 1>, 3> image_array{{
      // clang-format off
      {'X'},
      {'X'},
      {'X'}
      // clang-format on
  }};
};

using Obstacle1 = Obstacle<ObstacleImage1>;

struct ObstacleImage2 {
  static constexpr std::array<std::array<char, 2>, 3> image_array{{
      // clang-format off
      {'X', 'X'},
      {'X', 'X'},
      {'X', 'X'}
      // clang-format on
  }};
};

using Obstacle2 = Obstacle<ObstacleImage2>;

struct ObstacleImage3 {
  static constexpr std::array<std::array<char, 5>, 2> image_array{{
      // clang-format off
      {'-', '-', '-', '-', '-'},
      {'|', ' ', ' ', ' ', '|'}
      // clang-format on
  }};
};

using Obstacle3 = Obstacle<ObstacleImage3>;

using ObstacleCollection = DrawableCollection<Obstacle1, Obstacle2, Obstacle3>;

#endif
