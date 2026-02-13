#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
    Velocity        velocity_;
    Point           center_;
    const Color     color_;
    const double    radius_;
    bool            isCollidable_;
public:
    Ball();
    Ball(const Velocity& velocity, const Point& center, const Color& color, const double radius, const bool isCollidable);
    Ball(const double vx, const double vy, const double x, const double y, const int red, const int green, const int blue, const double radius, const bool isCollidable);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
    Color getColor();
};
