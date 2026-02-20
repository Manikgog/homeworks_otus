#include <cmath>
#include "istatistics.h"

class StdDev : public IStatistics {
public:
    StdDev() : m_sum{0.0}, m_sumSquares{0.0}, m_count{0} {
    }

    void update(double next) override {
        m_sum += next;
        m_sumSquares += next * next;
        ++m_count;
    }

    double eval() const override {
        if (m_count < 2) {
            return 0.0;
        }

        double mean = m_sum / m_count;
        double variance = (m_sumSquares / m_count) - (mean * mean);
        return std::sqrt(variance);
    }

    const char * name() const override {
        return "stddev";
    }

private:
    double m_sum;
    double m_sumSquares;
    size_t m_count;
};
