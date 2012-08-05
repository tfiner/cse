#pragma once

#include <boost/variant.hpp>

#include <map>
#include <string>


namespace cse {
    
    enum CompKey : unsigned int;
    struct Point2D;
    struct Vector2D;

    // This is used for the Component Map as the comparator to turn CompKey enums into ints.
    struct CompKeyLess : public std::binary_function<CompKey,CompKey,bool> {
        bool operator()(const CompKey& lhs, const CompKey& rhs) const {
            return static_cast<unsigned int>(lhs) < static_cast<unsigned int>(rhs);
        }
    };

    // Every component is made up of one of these types:
    typedef boost::variant< int, float, std::string, Point2D, Vector2D > CompVal;

    // A component is made up of map of component keys and component values.
    typedef std::map< CompKey, CompVal, CompKeyLess > Component;

} // namespace cse
