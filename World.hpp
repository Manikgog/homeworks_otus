#pragma once
#include "Ball.hpp"
#include "Physics.hpp"
#include <string>
#include <vector>

class Painter;

class World {
  public:
    explicit World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);

  private:
    void readBoxFromStream(std::ifstream& stream);
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    // Контейнер с шарами
    std::vector<Ball> balls;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;
};
