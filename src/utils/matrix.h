#pragma once
#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <vector>
#include "image/color.h"

namespace image_processor::utils {

template <typename T>
class Matrix {
public:
    Matrix() : Matrix(0, 0) {
    }

    Matrix(size_t width, size_t height, const T& fill_value = {})
        : width_(width), height_(height), data_(width * height, fill_value) {
    }

    Matrix(std::initializer_list<std::initializer_list<T>> data)
        : width_(data.size()), height_(data.size() > 0 ? data.begin()->size() : 0), data_() {
        data_.reserve(width_ * height_);
        for (std::initializer_list<T> row : data) {
            for (const auto& value : row) {
                data_.emplace_back(value);
            }
        }
    }

    Matrix(size_t width, size_t height, std::vector<T> data) : width_(width), height_(height), data_(data) {
    }

    Matrix<T> operator*(Matrix<T> matrix1) {
        for (size_t i = 0; i < matrix1.GetWidth() * matrix1.GetHeight(); ++i) {
            matrix1.data_[i] = matrix1.data_[i] * this->data_[i];
        }
        return matrix1;
    }

    T& operator()(size_t row, size_t col) {
        return data_[PointToIndex(row, col)];
    }

    const T& operator()(size_t row, size_t col) const {
        return data_[PointToIndex(row, col)];
    }

    size_t GetWidth() const {
        return width_;
    }

    size_t GetHeight() const {
        return height_;
    }

    const std::vector<T>& GetData() const {
        return (*this).data_;
    }

    void SetWidth(size_t new_width) {
        width_ = std::min(new_width, width_);
    }

    void SetHeight(size_t new_height) {
        height_ = std::min(new_height, height_);
    }

private:
    size_t PointToIndex(size_t row, size_t col) const {
        return row * width_ + col;
    }

private:
    size_t width_;
    size_t height_;
    std::vector<T> data_;
};

}  // namespace image_processor::utils
