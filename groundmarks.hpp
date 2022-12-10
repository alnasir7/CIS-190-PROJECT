#ifndef GROUNDMARKS_HPP
#define GROUNDMARKS_HPP

#include "drawable.hpp"
#include "drawablecollection.hpp"
#include "ncurses.h"
#include <array>

template <typename T> class GroundMarks : public Drawable<T> {
public:
  // All obstacles start outside of screen at same x and y value
  GroundMarks() : Drawable<T>(COLS, LINES - 7){};
  GroundMarks(int x) : Drawable<T>(x, LINES - 7){};
  static GroundMarks<T> generate() { return {}; }
  static GroundMarks<T> generate_x(int x) { return GroundMarks(x);}
};

struct GroundImage1 {
  static constexpr std::array<std::array<char, 2>, 2> image_array{{
      // clang-format off
      {' ', ' '},
      {' ', '-'},
      // clang-format on
  }};
};

using GroundMarks1 = GroundMarks<GroundImage1>;

struct GroundImage2 {
  static constexpr std::array<std::array<char, 2>, 2> image_array{{
      // clang-format off
      {'-', ' '},
      {' ', ' '},
      // clang-format on
  }};
};

using GroundMarks2 = GroundMarks<GroundImage2>;

struct GroundImage3 {
  static constexpr std::array<std::array<char, 2>, 2> image_array{{
      // clang-format off
      {' ', '-'},
      {'-', ' '}
      // clang-format on
  }};
};

using GroundMarks3 = GroundMarks<GroundImage3>;

struct GroundImage4 {
  static constexpr std::array<std::array<char, 2>, 2> image_array{{
      // clang-format off
      {'-', ' '},
      {' ', '-'}
      // clang-format on
  }};
};

using GroundMarks4 = GroundMarks<GroundImage4>;

using GroundMarkCollection = DrawableCollection<GroundMarks1, GroundMarks2, GroundMarks3, GroundMarks4>;

#endif
