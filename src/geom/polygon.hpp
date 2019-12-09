#pragma once

#include <cstddef> // size_t
#include <tuple>
#include <type_traits>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <vector>

/*
    basic_polygon traits
*/
template<typename _Vertex>
struct basic_polygon_traits {
    using vertex          = _Vertex;
    using pointer         = vertex*;
    using const_pointer   = const vertex*;
    using reference       = vertex&;
    using const_reference = const vertex&;

    using iterator       = pointer;
    using const_iterator = const_pointer;
};

/*
    basic_polygon class
    tuple-like
    structured binding is available
*/
template<typename _Vertex, size_t _NumOfPoints>
class basic_polygon {
    static_assert(_NumOfPoints >= 3, "can not create polygon from points when there are less than three");
    using traits = basic_polygon_traits<_Vertex>;

    struct tag_prepare_initializer{};
    struct tag_emplace_initializer{};
public:
    using vertex          = typename traits::vertex;
    using pointer         = typename traits::pointer;
    using const_pointer   = typename traits::const_pointer;
    using reference       = typename traits::reference;
    using const_reference = typename traits::const_reference;

    using iterator       = typename traits::iterator;
    using const_iterator = typename traits::const_iterator;


    // constructors
    basic_polygon() = default;

    basic_polygon(std::istream& stream) {
        for (auto& point : points) {
            stream >> point;
        }
        if (stream.fail()) {
            throw std::runtime_error("bad polygon initialization");
        }
    }

    basic_polygon(const vertex& v) noexcept {
        for (auto& point : points) {
            point = v;
        }
    }

    basic_polygon(const std::vector<vertex>& v) noexcept {
        if (v.size() < _NumOfPoints) {
            throw std::runtime_error("too few vertices for initialization");
        }
    }

    // element getters
    reference at(size_t ix) {
        return points[ix];
    }
    const_reference at(size_t ix) const {
        return const_cast<basic_polygon&>(*this).at(ix);
    }

    reference operator[](size_t ix) {
        return at(ix);
    }
    const_reference operator[](size_t ix) const {
        return const_cast<basic_polygon&>(*this)[ix];
    }



    // iterators
    iterator begin() {
        return &points[0];
    }
    const_iterator begin() const {
        // cast const to mutable and use non-const begin
        return const_cast<basic_polygon&>(*this).begin();
    }

    /* NEVER DEREFERENCE */
    iterator end() {
        return &points[_NumOfPoints];
    }
    /* NEVER DEREFERENCE */
    const_iterator end() const {
        // cast const to mutable and use non-const end
        return const_cast<basic_polygon&>(*this).end();
    };



    // structured binding
    template<size_t _Ix>
    constexpr auto& get() & {
        // check out of bounds
        if constexpr (_Ix < _NumOfPoints) {
            return points[_Ix];
        }
        else {
            // generate compile-time error
            static_assert(_Ix < _NumOfPoints, "ix is out of range");
        }
    }

    template<size_t _Ix>
    constexpr auto const& get() const& {
        // cast const to mutable and use non-const get
        // which does no effect on storage
        return const_cast<basic_polygon&>(*this).get<_Ix>();
    }

    template<size_t _Ix>
    constexpr auto&& get() && {
        // cast lvalue reference to rvalue and return it
        return std::move(this->get<_Ix>());
    }

    constexpr size_t size() const {
        return _NumOfPoints;
    }

private:
    vertex points[_NumOfPoints];

    template<size_t _Ix, typename _V, size_t _N>
    friend constexpr auto std::get(const basic_polygon<_V, _N>& polygon);
};

// std types spetializations for structured binding of basic_polygon
namespace std {
    template<size_t _Ix, typename _Vertex, size_t _NumOfPoints>
    constexpr auto get(const basic_polygon<_Vertex, _NumOfPoints>& polygon) {
        return polygon.points[_Ix];
    }

    template<typename _Vertex, size_t _NumOfPoints>
    struct tuple_size<::basic_polygon<_Vertex, _NumOfPoints>>
        : integral_constant<size_t, _NumOfPoints> {};

    template<size_t _Ix, typename _Vertex, size_t _NumOfPoints>
    struct tuple_element<_Ix, ::basic_polygon<_Vertex, _NumOfPoints>> {
        using type = typename basic_polygon_traits<_Vertex>::vertex;
    };
} // namespace std
