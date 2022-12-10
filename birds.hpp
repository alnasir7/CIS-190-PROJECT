#ifndef BIRDS_HPP
#define BIRDS_HPP

#include "drawable.hpp"
#include "drawablecollection.hpp"
#include "ncurses.h"
#include <array>

template <typename T1, typename T2> class Bird {
private:
  Drawable<T1> image1;
  Drawable<T2> image2;
  int counter = 0;
  int x;
public:
  // All obstacles start outside of screen at same x and y value
  Bird() : image1(Drawable<T1>(COLS, LINES-18)),
           image2(Drawable<T2>(COLS, LINES-18)),
           x(COLS)
    {};
  static Bird<T1, T2> generate() { return {}; }

  bool update() {
    image1.update();
    image1.update();
    image2.update();
    image2.update();
    counter++;
    x -= 2;
    return x < 0;
  }

  void draw() const {
    if (counter / 5 % 2) {
      image1.draw();
    } else {
      image2.draw();
    }
  }

};

struct BirdImage1 {
  static constexpr std::array<std::array<char, 3>, 3> image_array{{
      // clang-format off
      {'X', ' ', 'X'},
      {' ', 'X', ' '},
      {' ', ' ', ' '}
      // clang-format on
    }};
};

struct BirdImage2 {
  static constexpr std::array<std::array<char, 3>, 3> image_array{{
      // clang-format off
      {' ', ' ', ' '},
      {' ', 'X', ' '},
      {'X', ' ', 'X'}
      // clang-format on
  }};
};

using Bird1 = Bird<BirdImage1, BirdImage2>;
using BirdCollection = DrawableCollection<Bird1>;

#endif
