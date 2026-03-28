#include <iostream>

#include "../src/simple_vector.h"
#include "gtest/gtest.h"

// Вспомогательный класс для отслеживания вызовов деструктора
class DestructorCounter {
private:
    static int _alive_count;
    int _id;

public:
    DestructorCounter() : _id(0) {
        _alive_count++;
    }

    DestructorCounter(int id) : _id(id) {
        _alive_count++;
    }

    DestructorCounter(const DestructorCounter& other) : _id(other._id) {
        _alive_count++;
    }

    DestructorCounter(DestructorCounter&& other) noexcept : _id(other._id) {
        _alive_count++;
        other._id = -1;
    }

    ~DestructorCounter() {
        _alive_count--;
    }

    DestructorCounter& operator=(const DestructorCounter& other) {
        if (this != &other) {
            _id = other._id;
        }
        return *this;
    }

    DestructorCounter& operator=(DestructorCounter&& other) noexcept {
        if (this != &other) {
            _id = other._id;
            other._id = -1;
        }
        return *this;
    }

    int get_id() const { return _id; }

    static int get_alive_count() { return _alive_count; }
    static void reset_alive_count() { _alive_count = 0; }
};

int DestructorCounter::_alive_count = 0;

// Существующие тесты
TEST(Vector, empty) {
    // Arrange
    Vector<int> vector;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(vector.size(), 0);
    ASSERT_TRUE(vector.empty());
}

TEST(Vector, push_back) {
    // Arrange
    const size_t count = 10;
    Vector<size_t> vector;

    // Act
    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    // Assert
    ASSERT_EQ(vector.size(), count);
    ASSERT_FALSE(vector.empty());
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], i);
    }

    vector.push_back(100);
    ASSERT_EQ(vector[vector.size() - 1], 100);
}

TEST(Vector, insert) {
    // Arrange
    const size_t count = 10;
    Vector<size_t> vector;

    // Act
    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    // Assert
    vector.insert(100, 0);
    ASSERT_EQ(vector[0], 100);
    vector.insert(200, 5);
    ASSERT_EQ(vector[5], 200);
    vector.insert(300, vector.size());
    ASSERT_EQ(vector[vector.size() - 1], 300);
}

TEST(Vector, pop_back) {
    // Arrange
    Vector<size_t> vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    vector.pop_back();
    ASSERT_EQ(vector[vector.size() - 1], 9);
    ASSERT_FALSE(vector.empty());
}

TEST(Vector, erase) {
    // Arrange
    Vector<size_t> vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    vector.erase(5);
    ASSERT_EQ(vector[5], 6);
    ASSERT_FALSE(vector.empty());

    vector.erase(0);
    ASSERT_EQ(vector[0], 1);
    ASSERT_FALSE(vector.empty());
}

TEST(Vector, size) {
    // Arrange
    Vector<size_t> vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Act

    // Assert
    ASSERT_EQ(vector.size(), 11);
    ASSERT_FALSE(vector.empty());

    vector.erase(0);
    ASSERT_EQ(vector.size(), 10);
    ASSERT_FALSE(vector.empty());
}


TEST(Vector, copy_constructor) {
    // Arrange
    Vector<int> original;
    for (int i = 0; i < 10; ++i) {
        original.push_back(i);
    }

    // Act
    Vector<int> copy(original);

    // Assert
    ASSERT_EQ(original.size(), copy.size());

    for (size_t i = 0; i < original.size(); ++i) {
        ASSERT_EQ(original[i], copy[i]);
    }

    copy.push_back(100);
    ASSERT_EQ(original.size(), 10);
    ASSERT_EQ(copy.size(), 11);
    ASSERT_EQ(original[0], copy[0]);
}

TEST(Vector, copy_assignment) {
    // Arrange
    Vector<int> original;
    for (int i = 0; i < 10; ++i) {
        original.push_back(i);
    }

    Vector<int> copy;
    for (int i = 0; i < 5; ++i) {
        copy.push_back(i * 10);
    }

    // Act
    copy = original;

    // Assert
    ASSERT_EQ(original.size(), copy.size());

    for (size_t i = 0; i < original.size(); ++i) {
        ASSERT_EQ(original[i], copy[i]);
    }

    copy.push_back(100);
    ASSERT_EQ(original.size(), 10);
    ASSERT_EQ(copy.size(), 11);
}

TEST(Vector, copy_self_assignment) {
    // Arrange
    Vector<int> vector;
    for (int i = 0; i < 10; ++i) {
        vector.push_back(i);
    }

    // Act
    vector = vector;

    // Assert
    ASSERT_EQ(vector.size(), 10);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(vector[i], i);
    }
}


TEST(Vector, move_constructor) {
    // Arrange
    Vector<int> original;
    for (int i = 0; i < 10; ++i) {
        original.push_back(i);
    }

    size_t original_size = original.size();

    // Act
    Vector<int> moved(std::move(original));

    // Assert
    ASSERT_EQ(moved.size(), original_size);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(moved[i], i);
    }

    ASSERT_EQ(original.size(), 0);
    ASSERT_TRUE(original.empty());
}

TEST(Vector, move_assignment) {
    // Arrange
    Vector<int> source;
    for (int i = 0; i < 10; ++i) {
        source.push_back(i);
    }

    Vector<int> destination;
    for (int i = 0; i < 5; ++i) {
        destination.push_back(i * 100);
    }

    size_t source_size = source.size();

    // Act
    destination = std::move(source);

    // Assert
    ASSERT_EQ(destination.size(), source_size);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(destination[i], i);
    }

    ASSERT_EQ(source.size(), 0);
    ASSERT_TRUE(source.empty());
}

TEST(Vector, move_constructor_with_complex_types) {
    // Arrange
    DestructorCounter::reset_alive_count();

    Vector<DestructorCounter> original;
    for (int i = 0; i < 5; ++i) {
        original.push_back(DestructorCounter(i));
    }

    int alive_before_move = DestructorCounter::get_alive_count();

    // Act
    Vector<DestructorCounter> moved(std::move(original));

    // Assert
    ASSERT_EQ(DestructorCounter::get_alive_count(), alive_before_move);
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(original.size(), 0);

    moved.clear();
    ASSERT_EQ(DestructorCounter::get_alive_count(), 10);
}
