#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <array>
#include "drawable.hpp"
#include "ncurses.h"


struct CharacterImage {
  static constexpr std::array<std::array<char, 3>, 4> image_array{
    {{' ', '#', '#'}, {' ', '#', ' '}, {'#', '#', '#'}, {'#', ' ', '#'}}};
};

class Character: public Drawable<CharacterImage> {
private:

public:
  bool jumping, can_jump;
  double init_y, dy;
  Character(double a, double b) : Drawable(a, b), can_jump{true}, init_y{b} {};
  bool update() override;
  void jump(double);
};

#endif
