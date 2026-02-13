#include "Dust.hpp"
#include "Painter.hpp"

Dust::Dust(const Point& center, const Velocity& velocity, const Color& color, double lifetime)
    : center_(center)
    , velocity_(velocity)
    , color_(color)
    , lifetime_(lifetime)
{}

void Dust::update(double timePerTick) {
    // Обновляем позицию
    center_ = center_ + velocity_.vector() * timePerTick;
    // Уменьшаем время жизни
    lifetime_ -= timePerTick;
}

void Dust::draw(Painter& painter) const {
    // Рисуем маленькую частицу (радиус 1-2 пикселя)
    // Чем меньше осталось времени жизни, тем прозрачнее частица
    // (уменьшаем яркость цвета)
    Color fadedColor(
        color_.red() * (lifetime_ / 0.5),
        color_.green() * (lifetime_ / 0.5),
        color_.blue() * (lifetime_ / 0.5)
    );

    // Радиус частицы также уменьшаем со временем
    double radius = 1.5 * (lifetime_ / 0.5);
    if (radius < 0.5) radius = 0.5;

    painter.draw(center_, radius, fadedColor);
}

bool Dust::isAlive() const {
    return lifetime_ > 0;
}