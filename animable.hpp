#ifndef ANIMABLE_HPP
#define ANIMABLE_HPP

#include "drawable.hpp"
#include <variant>
#include <vector>

template <int SPEED = 5, typename... Ts> class Animable {
private:
  std::vector<std::variant<Ts...>> image_list = {(Ts::generate())...};
  int counter = 0;
  int x;

public:
  static Animable<SPEED, Ts...> generate() { return {}; }
  static Animable<SPEED, Ts...> generate_x(int x) { return {}; }

  bool update() {
    for (auto &image : image_list) {
      if (std::visit([](auto &arg) { return arg.update(); }, image)) {
        return true;
      }
    }
    counter++;
    return false;
  }

  void draw() const {
    int mod = (counter / SPEED) % image_list.size();
    std::visit([](auto &arg) { arg.draw(); }, image_list[mod]);
  }
};

#endif
