#pragma once

#include "entity.h"
#include "component.h"

#include <unordered_map>


namespace cse {

    typedef std::unordered_map< Entity, Component > Map;
    

    class EntityMap {
    public:
        Map::iterator begin() { return entities_.begin(); }
        Map::iterator end() { return entities_.end(); }

        Map::const_iterator begin() const { return entities_.begin(); }
        Map::const_iterator end() const { return entities_.end(); }

        std::pair<Map::iterator,bool> insert( const Map::value_type& value ) {
            return entities_.insert(value);
        }

    private:
        Map entities_;
    };
    

}