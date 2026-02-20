#include "istatistics.h"
#include <vector>
#include <algorithm>
#include <cmath>

class Percentile : public IStatistics {
public:
    explicit Percentile(double percentile) : m_percentile(percentile) {
    }

    void update(double next) override {
        m_values.push_back(next);
    }

    double eval() const override {
        if (m_values.empty()) {
            return 0.0;
        }

        std::vector<double> sorted = m_values;
        std::sort(sorted.begin(), sorted.end());

        double index = m_percentile * (static_cast<double>(sorted.size()) - 1) / 100.0;
        size_t floorIndex = static_cast<size_t>(std::floor(index));
        size_t ceilIndex = static_cast<size_t>(std::ceil(index));

        if (floorIndex == ceilIndex) {
            return sorted[floorIndex];
        }

        double fraction = index - static_cast<double>(floorIndex);
        return sorted[floorIndex] * (1.0 - fraction) + sorted[ceilIndex] * fraction;
    }

    virtual const char * name() const override = 0;

protected:
    std::vector<double> m_values;
    double m_percentile;
};

// Класс для вычисления 90-го процентиля
class Percentile90 : public Percentile {
public:
    Percentile90() : Percentile(90.0) {
    }

    const char * name() const override {
        return "p90";
    }
};

// Класс для вычисления 95-го процентиля
class Percentile95 : public Percentile {
public:
    Percentile95() : Percentile(95.0) {
    }

    const char * name() const override {
        return "p95";
    }
};
