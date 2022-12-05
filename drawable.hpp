#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "ncurses.h"
#include <algorithm>
#include <array>
#include <vector>
#include <iostream>
struct Point {
  int x, y;
  char c;
};

struct ImageArray {

  template <int sizeA, int sizeB, int sizeC>
  static constexpr const std::array<Point, sizeC>
  image_to_array(std::array<std::array<char, sizeA>, sizeB> image_array) {
    std::array<Point, sizeC> ret = {};
    int cnt = 0;
    for (auto j = 0; j < image_array.size(); ++j) {
      for (auto i = 0; i < image_array[j].size(); ++i) {
        if (image_array[j][i] != ' ') {
          ret[cnt++] = Point{i, j, image_array[j][i]};
        }
      }
    }
    return ret;
  }
};

template <typename T, int sizeA, int sizeB, int sizeC> class Drawable {
private:
  static constexpr std::array<Point, sizeC> image =
      ImageArray::image_to_array<sizeA, sizeB, sizeC>(T::image_array);

public:
  int x, y;

  Drawable(int a, int b) : x{a}, y{b} {};
  void draw() {
    for (size_t i = 0; i < image.size(); ++i) {
      int yi = image[i].y;
      int xi = image[i].x;
      char ci = image[i].c;
      mvaddch(y + yi, x + xi, ci);
    }
  }
  template <typename T1, int sizeA1, int sizeB1, int sizeC1>
  bool collides(Drawable<T1, sizeA1, sizeB1, sizeC1> *other) {
    return std::max(0, std::min(x + sizeA, other->x + sizeA1) -
                           std::max(x, other->x)) *
               std::max(0, std::min(y + sizeB, other->y + sizeB1) -
                               std::max(y, other->y)) !=
           0;
  }

  virtual void update() { --x; }
};

#endif
