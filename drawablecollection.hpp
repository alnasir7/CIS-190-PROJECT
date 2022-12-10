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
  std::vector<std::function<std::variant<Ts...>()>> list_generate = {([]() {
    std::variant<Ts...> tmp(Ts::generate());
    return tmp;
  })...};

  std::vector<std::function<std::variant<Ts...>(int)>> list_generate_x = {
      ([](int x) {
        std::variant<Ts...> tmp(Ts::generate_x(x));
        return tmp;
      })...};
  // std::vector<std::function<std::variant<Ts*...>()>> list = {
  //   (Ts::generate)...};
  std::deque<std::variant<Ts...>> container;
  std::random_device rd;
  std::mt19937 rng_seed;
  std::uniform_real_distribution<double> rng;
  int rng_generate() { return rng(rng_seed) * sizeof...(Ts); }

  void generate() {
    std::variant<Ts...> new_item = list_generate[rng_generate()]();
    container.push_back(new_item);
  }
  void generate_x(int x) {
    std::variant<Ts...> new_item = list_generate_x[rng_generate()](x);
    container.push_back(new_item);
  }
  int cnt = 0;
  int generate_frequency;

public:
  DrawableCollection()
      : rng_seed(rd()), rng(std::uniform_real_distribution<double>(0.0, 1.0)) {
    rng_seed.seed(::time(NULL));
  };
  DrawableCollection(int freq) : DrawableCollection() {
    generate_frequency = freq;
  };
  DrawableCollection(int freq, bool populate) : DrawableCollection(freq) {

    for (int i = 0; i < COLS; i += generate_frequency) {
      generate_x(i);
    }
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

    if (generate_frequency > 0 && ++cnt % generate_frequency == 0) {
      generate();
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
};

#endif
