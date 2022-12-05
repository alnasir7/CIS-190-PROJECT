#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "drawable.hpp"
#include <array>
#include <vector>

struct ObstacleImage {
  static constexpr std::array<std::array<char, 1>, 3> image_array{
    {{'X'}, {'X'}, {'X'}}};
};

class Obstacle : public Drawable<ObstacleImage, 1, 3, 3> {
public:
  Obstacle(int a, int b) : Drawable(a, b) {};
};

#endif
