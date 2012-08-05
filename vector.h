#pragma once

#include <ostream>

namespace cse {
    

    struct Vector2D { 
        Vector2D() : x(0), y(0) {}
        Vector2D(float x_, float y_) : x(x_), y(y_) {}
        float x, y; 
    };

    inline std::ostream& operator<<(std::ostream& os, const Vector2D& p) {
        os << p.x << "," << p.y;
        return os;
    }


}