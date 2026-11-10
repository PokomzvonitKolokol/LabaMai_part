#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
private:
    T* data_;
    size_t size_;

    void checkValue(const T& value) const {
        if constexpr (std::is_integral_v<T>) {
            if (value < -100 || value > 100) {
                throw std::invalid_argument("Value in range [-100, 100]");
            }
        }
    }

    static T* newArray(size_t size) {
        T* ptr = new T[size];
        if (!ptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

public:
    explicit DynamicArray(size_t size) {
        size_ = size;
        data_ = newArray(size);
        for (size_t i = 0; i < size; i++) {
            data_[i] = T{};
        }
    }

    ~DynamicArray() {
        delete[] data_;
    }

    DynamicArray(const DynamicArray& other) {
        size_ = other.size_;
        data_ = newArray(size_);
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    size_t size() const {
        return size_;
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size_; i++) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "]" << std::endl;
    }

    void set(size_t index, const T& value) {
        if (index >= size_) {
            throw std::out_of_range("Index is out");
        }
        checkValue(value);
        data_[index] = value;
    }

    T get(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index is out");
        }
        return data_[index];
    }

    void push_back(const T& value) {
        checkValue(value);
        T* new_data = newArray(size_ + 1);
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        new_data[size_] = value;
        delete[] data_;
        data_ = new_data;
        size_++;
    }

    void add(const DynamicArray& other) {
        size_t minSize = (size_ < other.size_) ? size_ : other.size_;
        for (size_t i = 0; i < minSize; i++) {
            data_[i] = data_[i] + other.data_[i];
        }
    }

    void sub(const DynamicArray& other) {
        size_t minSize = (size_ < other.size_) ? size_ : other.size_;
        for (size_t i = 0; i < minSize; i++) {
            data_[i] = data_[i] - other.data_[i];
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "[";
        for (size_t i = 0; i < arr.size_; i++) {
            if (i > 0) os << ", ";
            os << arr.data_[i];
        }
        os << "]";
        return os;
    }

    double distance(const DynamicArray& other) const {
        if constexpr (std::is_arithmetic_v<T>) {
            if (other.size_ != size_) {
                throw std::invalid_argument("Different sizes");
            }
            double sum = 0;
            for (size_t i = 0; i < size_; i++) {
                double diff = data_[i] - other.data_[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }
};