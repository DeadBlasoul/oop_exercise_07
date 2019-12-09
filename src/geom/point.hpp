#pragma once

#include <iostream>
#include <cstddef>
#include <cassert>
#include <cmath>

template<typename _Type, size_t _Dimensions>
struct point {
    static_assert(_Dimensions != 0, "can not create 0d point");

    using type = _Type;
    using reference = type&;
    using const_reference = const type&;
    using pointer = type*;
    using const_pointer = const type*;

    using iterator = pointer;
    using const_iterator = const_pointer;

    type dots[_Dimensions];

    type& operator[](size_t ix) noexcept {
        return dots[ix];
    }

    const type& operator[](size_t ix) const noexcept {
        return const_cast<point&>(*this).operator[](ix);
    }

    iterator begin() noexcept {
        return &dots[0];
    }

    const_iterator begin() const noexcept {
        return const_cast<point&>(*this).begin();
    }

    iterator end() noexcept {
        return &dots[_Dimensions];
    }

    const_iterator end() const noexcept {
        return const_cast<point&>(*this).end();
    }

    static constexpr size_t size() noexcept {
        return _Dimensions;
    }

    point operator+(const point& other) const {
        point result = *this;

        for (size_t i = 0; i < result.size(); i++) {
            result[i] += other[i];
        }

        return result;
    }

    point operator-(const point& other) const {
        point result = *this;

        for (size_t i = 0; i < result.size(); i++) {
            result[i] -= other[i];
        }

        return result;
    }
};

template<typename _Type, size_t _Dims>
std::ostream& operator<<(std::ostream& stream, const point<_Type, _Dims>& p) {
    stream << "{ ";
    for (const auto& d : p) {
        stream << d << " ";
    }
    stream << "}";

    return stream;
}

template<typename _Type, size_t _Dims>
std::istream& operator>>(std::istream& stream, point<_Type, _Dims>& p) {
    for (auto& d : p) {
        stream >> d;
    }

    return stream;
}

// Examples:
using point2d = point<double, 2>;

inline double distance(const point2d& left, const point2d& right) {
    double x = left[0] - right[0];
    double y = left[1] - right[1];
    return std::sqrt((x * x) + (y * y));
}
