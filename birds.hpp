#ifndef BIRDS_HPP
#define BIRDS_HPP

#include "drawable.hpp"
#include "drawablecollection.hpp"
#include "ncurses.h"
#include <array>

#include "animable.hpp"

template <typename T> class Bird : public Drawable<T> {
public:
  // All birds start outside of screen at same x and y value
  // TODO change?
  Bird() : Drawable<T>(COLS, LINES - 18){};
  static Bird<T> generate() { return {}; };
};

struct BirdImage1 {
  static constexpr std::array<std::array<char, 3>, 2> image_array{{
      // clang-format off
      {'X', ' ', 'X'},
      {' ', 'X', ' '},
      // clang-format on
  }};
};

struct BirdImage2 {
  static constexpr std::array<std::array<char, 3>, 2> image_array{{
      // clang-format off
      {' ', 'X', ' '},
      {'X', ' ', 'X'},
      // clang-format on
  }};
};

using Bird1 = Bird<BirdImage1>;
using Bird2 = Bird<BirdImage2>;
using BirdAnimable1 = Animable<20, Bird1, Bird2>;
using BirdCollection = DrawableCollection<BirdAnimable1>;

#endif
