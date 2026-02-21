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
    const double          mass_;
public:
    Ball();
    Ball(const Velocity& velocity, const Point& center, const Color& color, double radius, bool isCollidable);
    Ball(double vx, double vy, double x, double y, int red, int green, int blue, double radius, bool isCollidable);
    Ball(const Ball&) = delete;
    Ball& operator=(Ball&) = delete;
    Ball(Ball&& other) noexcept;
    Ball& operator=(Ball&& other) noexcept;
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
    Color getColor() const;
};

inline std::istream& operator>>(std::istream& is, Ball& ball) {
    Point center;
    Point speed;
    Color color;
    double radius;
    bool isCollidable;
    is >> center >> speed;
    is >> color;
    is >> radius;
    is >> std::boolalpha >> isCollidable;
    
    if (is) {
        ball = Ball(speed, center, color, radius, isCollidable);
    }
    return is;
}
