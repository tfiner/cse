#pragma once

#include <ostream>

namespace cse {
    

    // A simple point class.  Note the lack of member functions. 
    struct Point2D { 
        Point2D() : x(0), y(0) {}
        Point2D(float x_, float y_) : x(x_), y(y_) {}
        float x, y; 
    };

} // namespace cse {
