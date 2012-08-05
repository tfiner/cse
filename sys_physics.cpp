#include "sys_physics.h"
#include "point.h"
#include "vector.h"
#include "entity_map.h"
#include "comp_keys.h"

#include <boost/variant.hpp>

using namespace cse;


namespace {

    // This takes two variants and if 
    // one is a position and the other is a vector,
    // updates the position with the vector as a velocity.

    class UpdatePosition
        : public boost::static_visitor<void> {
    public:
        template<typename T, typename U> 
        void operator()( const T& t, const U& u ) const {
            assert( !"This function is only valid for position vs vector!" );
        }

        void operator()( Point2D& p, const Vector2D& v ) const
        {
            p.x += v.x;
            p.y += v.y;
        }
    };

} // namespace {


void cse::PhysicsSystem( EntityMap& em ) {
    auto updatePos = UpdatePosition();

    for( auto & e : em ) {
        auto & comps = e.second;

        // If the entity has components for position and vector, then
        // update the position component.
        auto pos = comps.find(Position);
        if ( pos == comps.end() )
            continue;

        auto vel = comps.find(Velocity);
        if ( vel == comps.end() )
            continue;

        // The actual updating is performed  
        boost::apply_visitor( updatePos, pos->second, vel->second );
    }
}

