#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <array>
#include "drawable.hpp"


struct CharacterImage {
  static constexpr std::array<std::array<char, 3>, 3> image_array {{
    {'.', ' ', '.'},
    {' ', '.', ' '},
    {'.', ' ', '.'}
    }};
};

class Character: public Drawable<CharacterImage, 3, 3, 5> {
private:

public:
  bool jumping, can_jump;
  int init_y, dy;
  Character(int a, int b) : Drawable(a, b), can_jump{true}, init_y{b} {};
  void update() override;
  void jump(int);
};

#endif
