#pragma once

#include <ostream>

namespace cse {
    

    // Another simple class, this represents a math vector.
    struct Vector2D { 
        Vector2D() : x(0), y(0) {}
        Vector2D(float x_, float y_) : x(x_), y(y_) {}
        float x, y; 
    };


} // namespace cse