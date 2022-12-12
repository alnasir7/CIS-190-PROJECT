#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "drawable.hpp"
#include "ncurses.h"
#include <array>
#include <vector>
#include "animable.hpp"

struct CharacterImage1 {
  static constexpr std::array<std::array<char, 3>, 5> image_array{{
      // clang-format off
      {' ', 'r', '@'},
      {' ', '|', ' '},
      {'-', '+', '-'},
      {'|', ' ', '|'},
      {'b', ' ', ' '}
      // clang-format on
  }};
};

struct CharacterImage2 {
  static constexpr std::array<std::array<char, 3>, 5> image_array{{
      // clang-format off
      {' ', 'r', '@'},
      {' ', '|', ' '},
      {'-', '+', '-'},
      {'|', ' ', '|'},
      {' ', ' ', 'b'}
      // clang-format on
  }};
};

template <typename T>
class Character : public Drawable<T> {
private:
public:
  bool jumping, can_jump;
  double init_y, dy;
  Character() : Drawable<T>(8, LINES - 8), can_jump{true} { init_y = LINES - 8; };
  static Character<T> generate() { return {}; };
  bool update() override {
    this->y += dy;
    if (this->y >= init_y) {
      this->y = init_y;
      jumping = false;
      can_jump = true;
      dy = 0;
    }
    if (jumping) {
      dy += 0.05;
    }
    return false;
  };
  void jump(double jump_strength) {
    if (can_jump) {
      dy = -1.0 + -jump_strength;
      jumping = true;
      can_jump = false;
    }
  }
};

using Character1 = Character<CharacterImage1>;
using Character2 = Character<CharacterImage2>;

class CharacterAnimate : public Animable<10, Character1, Character2> {

public:
  void jump(double jump_strength) {
    for (auto &image : this->image_list) {
      std::visit([jump_strength](auto &arg) { return arg.jump(jump_strength); }, image);
    }
  }

};


#endif
