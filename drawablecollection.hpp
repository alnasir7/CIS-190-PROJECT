#ifndef DRAWABLECOLLECTION_HPP
#define DRAWABLECOLLECTION_HPP

#include "character.hpp"
#include "drawable.hpp"
#include <any>
#include <deque>
#include <functional>
#include <memory>
#include <random>
#include <time.h>
#include <tuple>
#include <variant>

template <typename... Ts> class DrawableCollection {
private:
  std::vector<std::function<std::variant<Ts...>()>> list = {
    (
      []() {
        std::variant<Ts...> tmp (Ts::generate());
        return tmp;
      }
      )...
  };
  // std::vector<std::function<std::variant<Ts*...>()>> list = {
  //   (Ts::generate)...};
  std::deque<std::variant<Ts ...>> container;
  std::random_device rd;
  std::mt19937 rng_seed;
  std::uniform_real_distribution<double> rng;
  int rng_generate() { return rng(rng_seed) * sizeof...(Ts); }

public:
  DrawableCollection()
      : rng_seed(rd()), rng(std::uniform_real_distribution<double>(0.0, 1.0)) {
    rng_seed.seed(::time(NULL));
  };
  void draw() {
    for (const auto &elem : container) {
      std::visit([](auto &arg) { arg.draw(); }, elem);
    }
  }

  void update() {
    for (auto &elem : container) {
      if (std::visit([](auto &arg) { return arg.update(); }, elem)) {
        container.pop_front();
      }
    }
  }

  int size() { return container.size(); }

  bool collides_with_character(const std::shared_ptr<Character> &c) {
    for (auto it = container.cbegin(); it != container.cend(); ++it) {
      if (std::visit([c](auto &arg) { return c.get()->collides(&arg); }, *it)) {
        return true;
      }
    }
    return false;
  }

  void generate() {
    std::variant<Ts...> new_item = list[rng_generate()]();
    container.push_back(new_item);
  }
};

#endif
