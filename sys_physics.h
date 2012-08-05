#pragma once


namespace cse {
    

    class EntityMap;

    // Update entities' Position components based upon the Velocity component.
    void PhysicsSystem( EntityMap& em );

}