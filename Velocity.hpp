#pragma once
#include "Point.hpp"
#include <cmath>

class Velocity {
  public:
    inline Velocity() = default;

    /**
     * @brief Конструктор скорости, заданной модулем и направлением.
     * 
     * Вычисляет компоненты скорости (x, y) на основе полярных координат.
     * 
     * @param abs Модуль скорости (абсолютная величина).
     * @param angle Угол направления в радианах, отсчитываемый от оси X.
     */    
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }

  private:
    Point vec;
};
