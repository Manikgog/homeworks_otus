#pragma once

template<typename T>
class Vector {
public:
    class Iterator {
    public:
        Iterator() = delete;

        Iterator(T *data) : data_(data) {
        }

        Iterator &operator++() {
            data_++;
            return *this;
        }

        Iterator &operator++(int) {
            Iterator tmp(*this);
            data_++;
            return tmp;
        }

        Iterator &operator--() {
            data_--;
            return *this;
        }

        Iterator &operator--(int) {
            Iterator tmp(*this);
            data_++;
            return tmp;
        }

        Iterator &operator+(int num) {
            Iterator it(this->data_ + num);
            (*this) = it;
            return *this;
        }

        Iterator &operator-(int num) {
            Iterator it(this->data_ - num);
            (*this) = it;
            return *this;
        }

        bool operator==(const Iterator &obj) const {
            return this->data_ == obj.data_;
        }

        bool operator!=(const Iterator &obj) const {
            return this->data_ != obj.data_;
        }

        T &operator*() {
            return *data_;
        }

    private:
        T *data_;
    };

    Vector() : _capacity(_initial_capacity), _array(new T[_initial_capacity]), _size(0) {
    }

    Vector(const Vector &v) : _capacity(v.size() * static_cast<int>(1.5)), _array(new T[v._size]), _size(v._size) {
        for (size_t i = 0; i < _size; i++) {
            _array[i] = v._array[i];
        }
    }

    Vector(Vector &&v) {
        this->_array = nullptr;
        _size = 0;
        std::swap(_capacity, v._capacity);
        std::swap(this->_array, v._array);
        std::swap(this->_size, v._size);
    }

    explicit Vector(int size) : _capacity(size * static_cast<int>(1.5)), _array(new T[_capacity]), _size(size) {
    }

    Vector(const std::initializer_list<T> &list) : Vector(list.size()) {
        int i = 0;
        for (auto &el: list) {
            this->_array[i] = el;
            i++;
        }
    }

    ~Vector() {
        this->clear();
    }

    Vector &operator=(const Vector &v) {
        if (this != &v) {
            if (this->_array != nullptr) {
                delete[] this->_array;
                this->_array = nullptr;
            }
            this->_size = v._size;
            for (size_t i = 0; i < this->_size; i++) {
                this->_array[i] = v._array[i];
            }
            return *this;
        }
        return *this;
    }

    void push_back(const T &data) {
        this->_size++;
        if (_size >= _capacity) {
            T *newArray = new T[_capacity]{};
            for (size_t i = 0; i < this->_size - 1; i++) {
                newArray[i] = this->_array[i];
            }
            newArray[this->_size - 1] = data;
            delete[] this->_array;
            this->_array = newArray;
            return;
        }
        this->_array[this->_size - 1] = data;
    }

    void pop_back() {
        this->_size--;
    }

    void insert(const T &data, int index) {
        this->_size++;
        if (this->_size >= this->_capacity) {
            T *newArray = new T[this->_size]{};
            for (size_t i = 0; i < index; ++i) {
                newArray[i] = this->_array[i];
            }
            newArray[index] = data;
            for (size_t i = index; i < this->_size - 1; ++i) {
                newArray[i + 1] = this->_array[i];
            }
            delete[] this->_array;
            this->_array = newArray;
            return;
        }
        for (size_t i = this->_size; i > index; --i) {
            _array[i] = _array[i - 1];
        }
        _array[index] = data;
    }

    void erase(int index) {
        for (size_t i = index; i < this->_size - 1; ++i) {
            _array[i] = _array[i + 1];
        }
        this->_size--;
    }

    void clear() {
        if (_array) {
            delete[] _array;
            _array = nullptr;
        }
        _size = 0;
        _capacity = _initial_capacity;
        _array = new T[_capacity];
    }

    T front() {
        return *_array;
    }

    int size() const {
        return _size;
    }

    T &operator[](int i) {
        return _array[i];
    }

    const T &operator[](int i) const {
        return _array[i];
    }

    T &at(int i) {
        if (i < 0 || i >= _size) {
            throw 1;
        }
        return _array[i];
    }

    const T &at(int i) const {
        if (i < 0 || i >= _size) {
            throw 1;
        }
        return _array[i];
    }

    Iterator begin() {
        return Iterator(_array);
    }

    Iterator begin() const {
        return Iterator(_array);
    }

    Iterator end() {
        return Iterator(_array + _size);
    }

    Iterator end() const {
        return Iterator(_array + _size);
    }

    Iterator rbegin() {
        return Iterator(_array + _size - 1);
    }

    Iterator rend() {
        return Iterator(_array - 1);
    }

    void swap(Vector &v) {
        if (this->_size != v._size)
            return;
        for (size_t i = 0; i < this->_size; i++) {
            std::swap(this->_array[i], v._array[i]);
        }
        _capacity = v._capacity;
    }

private:
    int _initial_capacity = 10;
    int _capacity;
    T *_array;
    int _size;
};
