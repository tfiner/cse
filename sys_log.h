#pragma once

#include "component.h"

namespace cse {
    

    class EntityMap;

    // Sends CompVal to Stdout.
    void LogStdout( CompVal& val );

    // Displays all of the component values of all of the entities.
    void LogSystem( const EntityMap& em );

}