#pragma once

#include <type_traits>
#include <tuple>
#include <utility>
#include <ostream>
#include <cmath>

#include "point.hpp"
#include "../editor/figure.hpp"

namespace detail {
    template<size_t _Off, size_t ... _Ix>
    std::index_sequence<(_Off + _Ix)...> add_offset(std::index_sequence<_Ix...>) {
        return {};
    }

    template<size_t _Off, size_t _N>
    auto make_index_sequence_with_offset() {
        return add_offset<_Off>(std::make_index_sequence<_N>{});
    }

    template<typename _T, size_t... _Ix>
    double area2d(const _T& tuple, std::index_sequence<_Ix...>) {
        using vertex = std::remove_const_t<std::remove_reference_t<decltype(std::get<0>(tuple))>>;
        static_assert(std::is_same_v<vertex, point2d>, "incorrect type");

        auto constexpr tuple_size = std::tuple_size<_T>{}();
        auto constexpr x = 0;
        auto constexpr y = 1;

        using std::get;

        double result = ((get<_Ix>(tuple)[x] * (get<_Ix + 1>(tuple)[y] - get<_Ix - 1>(tuple)[y])) + ...);
        auto constexpr first = 0;
        auto constexpr last = tuple_size - 1;
        result += get<first>(tuple)[x] * (get<first + 1>(tuple)[y] - get<last>(tuple)[y]);
        result += get<last>(tuple)[x] * (get<first>(tuple)[y] - get<last - 1>(tuple)[y]);
        result /= 2;

        return std::abs(result);
    }

    template<typename _T, std::size_t... _Ix>
    auto center2d(const _T& tuple, std::index_sequence<_Ix...>) {
        using vertex = std::remove_const_t<std::remove_reference_t<decltype(std::get<0>(tuple))>>;
        static_assert(std::is_same_v<vertex, point2d>, "incorrect type");

        auto constexpr tuple_size = std::tuple_size<_T>{}();
        auto constexpr x = 0;
        auto constexpr y = 1;

        vertex result = (std::get<_Ix>(tuple) + ...);
        result[x] /= tuple_size;
        result[y] /= tuple_size;

        return result;
    }

    template<typename _T, std::size_t... _Ix>
    auto print_points2d(std::ostream& out, const _T& tuple, std::index_sequence<_Ix...>) {
        auto constexpr tuple_size = std::tuple_size<_T>{}();
        (out << ... << std::get<_Ix>(tuple));
    }
}

template<typename _T>
double area2d(const _T& tuple) {
    auto constexpr tuple_size = std::tuple_size<_T>{}();
    using vertex = std::remove_reference_t<decltype(std::get<0>(tuple))>;
    return detail::area2d(tuple, detail::make_index_sequence_with_offset<1, tuple_size - 2>());
}

template<typename _T>
auto center2d(const _T& tuple) {
    auto constexpr tuple_size = std::tuple_size<_T>{}();
    return detail::center2d(tuple, std::make_index_sequence<tuple_size>{});
}

template<typename _T>
auto print2d(std::ostream& stream, const _T& tuple) {
    auto constexpr tuple_size = std::tuple_size<_T>{}();

    using std::endl;

    stream << "\ntype:   ";
    switch (tuple_size) {
    case 4:
        stream << "rhombus" << endl; break;
    case 5:
        stream << "pentagon" << endl; break;
    case 6:
        stream << "hexagon" << endl; break;
    default:
        stream << "unknown" << endl;
    }

    stream << "center: " << center2d(tuple) << endl
           << "area:   " << area2d(tuple) << endl
           << "points: ";
    detail::print_points2d(stream, tuple, std::make_index_sequence<tuple_size>{});
    stream << endl << endl;
}

#include <algorithm>

// Define Infinite (Using INT_MAX caused overflow problems) 
#define INF 10000 

//struct Point
//{
//    int x;
//    int y;
//};

typedef oop::editor::vec2 Point;

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool on_segment(Point p, Point q, Point r)
{
    using namespace std;
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear 
    return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool do_intersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case 
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases 
}

// Returns true if the point p lies inside the polygon[] with n vertices 
bool is_inside(Point polygon[], int n, Point p)
{
    // There must be at least 3 vertices in polygon[] 
    if (n < 3)  return false;

    // Create a point for line segment from p to infinite 
    Point extreme = { INF, p.y };

    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0;
    do
    {
        int next = (i + 1) % n;

        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (do_intersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return on_segment(polygon[i], p, polygon[next]);

            count++;
        }
        i = next;
    } while (i != 0);

    // Return true if count is odd, false otherwise 
    return count & 1;  // Same as (count%2 == 1) 
}