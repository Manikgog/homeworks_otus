#pragma once
#include "Ball.hpp"
#include "Dust.hpp"        // новый include
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
  void updateDust(double timePerTick);
  // Границы мира заданы углами прямоугольника
  Point topLeft;
  Point bottomRight;
  // Объект физического движка
  Physics physics;
  // Контейнер с шарами
  std::vector<Ball> balls;
  // Контейнер с частицами пыли
  std::vector<Dust> dustParticles;
  // Длина отрезка времени, который не был
  // учтен при прошлой симуляции. См. реализацию update
  double restTime = 0.;
};