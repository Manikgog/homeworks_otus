#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"

class Dust {
public:
    Dust(const Point& center, const Velocity& velocity, const Color& color, double lifetime);

    void update(double timePerTick);
    void draw(Painter& painter) const;
    bool isAlive() const;

private:
    Point center_;
    Velocity velocity_;
    Color color_;
    double lifetime_;
};