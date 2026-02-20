#include "istatistics.h"

class Mean : public IStatistics {
public:
    Mean() : m_sum{0.0}, m_count{0} {
    }

    void update(double next) override {
        m_sum += next;
        ++m_count;
    }

    double eval() const override {
        if (m_count == 0) {
            return 0.0;
        }
        return m_sum / m_count;
    }

    const char * name() const override {
        return "mean";
    }

private:
    double m_sum;
    size_t m_count;
};
