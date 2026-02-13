#include "World.hpp"
#include "Dust.hpp"
#include "Painter.hpp"
#include <fstream>
#include <algorithm>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    readBoxFromStream(stream);

    Point center;
    Point speed;
    Color color;
    double radius;
    bool isCollidable;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) и вектор
        // его скорости (vx, vy)
        stream >> center >> speed;
        // Читаем три составляющие цвета шара
        stream >> color;
        // Читаем радиус шара
        stream >> radius;
        stream >> std::boolalpha >> isCollidable;
        Ball ball(Velocity(speed), center, color, radius, isCollidable);
        balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    for (const Dust& dust : dustParticles) {
        dust.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, dustParticles, ticks);

    for (size_t i = 0; i < ticks; ++i) {
        updateDust(timePerTick);
    }
}



void World::updateDust(double timePerTick) {
    // Обновляем все частицы
    for (auto& dust : dustParticles) {
        dust.update(timePerTick);
    }

    dustParticles.erase(
        std::remove_if(dustParticles.begin(), dustParticles.end(),
            [](const Dust& d) { return !d.isAlive(); }),
        dustParticles.end()
    );
}



void World::readBoxFromStream(std::ifstream& stream) {
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);
}