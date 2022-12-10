#include <ncurses.h>
#include "character.hpp"

using namespace std;
// const vector<vector<int>> Character::character_image =
//     {
//     {'X', 'X', 'X'},
//     {'X', '-', 'X'},
//     {'X', 'X', 'X'}
//     };

// void Character::draw() {
//   for (size_t j = 0; j < character_image.size(); ++j) {
//     for (size_t i = 0; i < character_image[0].size(); ++i) {
//       mvaddch(y + j, x + i, character_image[j][i]);
//     }
//   }
// }

bool Character::update() {
  y  += dy;
  if (y >= init_y) {
    y = init_y;
    jumping = false;
    can_jump = true;
    dy = 0;
  }
  if (jumping) {
    dy += 0.05;
  }
  return false;
}
void Character::jump(double jump_strength) {
  if (can_jump){
    dy = -1.0 + -jump_strength;
    jumping = true;
    can_jump = false;
  }
}
