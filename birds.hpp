#ifndef BIRDS_HPP
#define BIRDS_HPP

#include "drawable.hpp"
#include "drawablecollection.hpp"
#include "ncurses.h"
#include <array>
#include <random>
#include "animable.hpp"

template <typename T> class Bird : public Drawable<T> {
private:
  static int rng_generate(int N) {
    static std::mt19937 rng_seed(::time(NULL));
    static std::uniform_real_distribution<double> rng =
        std::uniform_real_distribution<double>(0.0, 1.0);
    return rng(rng_seed) * N;
  }

public:
  // All birds start outside of screen at same x and y value
  // TODO change?
  int color = rng_generate(5);
  int speed = rng_generate(10);
  Bird() : Drawable<T>(COLS, LINES - 22){};
  Bird(int x) : Drawable<T>(x, LINES - 22){};
  Bird(int x, int y) : Drawable<T>(x, y){};
  static Bird<T> generate() {
    return Bird(COLS, LINES - 28 + rng_generate(20));
  };
  static Bird<T> generate_x(int x) { return Bird(x); }
  bool update() override {
    this->x -= 0.2 + 0.08 * speed;
    return this->x < 0;
  }
  void draw() const override {
    attron(COLOR_PAIR(2 + color));
    Drawable<T>::draw();
    attroff(COLOR_PAIR(2 + color));
  }
};

struct BirdImage1 {
  static constexpr std::array<std::array<char, 3>, 2> image_array{{
      // clang-format off
      {'_', ' ', '_'},
      {' ', 'V', ' '},
      // clang-format on
  }};
};

struct BirdImage2 {
  static constexpr std::array<std::array<char, 3>, 2> image_array{{
      // clang-format off
      {' ', '^', ' '},
      {'-', ' ', '-'},
      // clang-format on
  }};
};

struct BirdImage3 {
  static constexpr std::array<std::array<char, 5>, 2> image_array{{
      // clang-format off
      {'_', ' ', '^', ' ', '_'},
      {' ', 'V', ' ', 'V', ' '},
      // clang-format on
  }};
};

struct BirdImage4 {
  static constexpr std::array<std::array<char, 5>, 2> image_array{{
      // clang-format off
      {' ', '^', ' ', '^', ' '},
      {'-', ' ', 'V', ' ', '-'},
      // clang-format on
  }};
};

using Bird1 = Bird<BirdImage1>;
using Bird2 = Bird<BirdImage2>;
using BirdAnimable1 = Animable<20, Bird1, Bird2>;

using Bird3 = Bird<BirdImage3>;
using Bird4 = Bird<BirdImage4>;
using BirdAnimable2 = Animable<40, Bird3, Bird4>;
using BirdCollection = DrawableCollection<BirdAnimable1, BirdAnimable2>;

#endif
