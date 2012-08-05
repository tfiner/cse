#pragma once

#include <ostream>

namespace cse {
    

    struct Point2D { 
        Point2D() : x(0), y(0) {}
        Point2D(float x_, float y_) : x(x_), y(y_) {}
        float x, y; 
    };

    inline std::ostream& operator<<(std::ostream& os, const Point2D& p) {
        os << p.x << "," << p.y;
        return os;
    }


}