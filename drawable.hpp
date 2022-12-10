#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "ncurses.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

struct Point {
  int x, y;
  char c;
};

template <typename T> class Drawable {
  template <typename T2> friend class Drawable;

private:
  static constexpr int image_cols = T::image_array[0].size();
  static constexpr int image_rows = T::image_array.size();

  static constexpr int image_non_empty = [](auto &image_array) {
    int cnt = 0;
    for (auto j = 0; j < image_array.size(); ++j) {
      for (auto i = 0; i < image_array[j].size(); ++i) {
        if (image_array[j][i] != ' ') {
          ++cnt;
        }
      }
    }
    return cnt;
  }(T::image_array);

  static constexpr const std::array<Point, image_non_empty>
  image_to_array(auto &image_array) {
    std::array<Point, image_non_empty> ret = {};
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

  static constexpr std::array<Point, image_non_empty> image =
      image_to_array(T::image_array);

public:
  double x, y;

  Drawable(double a, double b) : x{a}, y{b} {};

  static Drawable<T> generate(double a, double b) { return Drawable<T>(a, b); };

  void draw() const {
    for (size_t i = 0; i < image.size(); ++i) {
      int yi = image[i].y;
      int xi = image[i].x;
      char ci = image[i].c;
      mvaddch(y - image_rows + yi, x - image_cols + xi, ci);
    }
  }
  template <typename T1> bool collides(Drawable<T1> const *other) const {
    int i_x = x;
    int i_y = y;
    int i2_x = other->x;
    int i2_y = other->y;
    return std::max(0,
                    std::min(i_x + image_cols, i2_x + other->image_cols) -
                        std::max(i_x, i2_x)) *
               std::max(0,
                        std::min(i_y + image_rows, i2_y + other->image_rows) -
                            std::max(i_y, i2_y)) !=
           0;
  }

  // Update location of the drawable object
  // If the new location would make the object out of screen (to the left)
  // Return True, else False
  virtual bool update() {
    x -= 1;
    return x < 0;
  }
};

#endif
