#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
    Velocity    velocity_;
    Point       center_;
    Color       color_;
    double      radius_;
    bool        isCollidable_;
    double      mass_;
public:
    Ball();
    Ball(const Velocity& velocity, const Point& center, const Color& color, double radius, bool isCollidable);
    //Ball(double vx, double vy, double x, double y, int red, int green, int blue, double radius, bool isCollidable);
    Ball(const Ball&) = default;
    Ball& operator=(const Ball&) = default;
    Ball(Ball&&) = delete;
    Ball& operator=(Ball&&) = delete;
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
        Ball temp(speed, center, color, radius, isCollidable);
        ball = temp;
    }
    return is;
}
