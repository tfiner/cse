#include "sys_physics.h"
#include "sys_log.h"
#include "entity_map.h"

#include "entity.h"
#include "component.h"
#include "comp_keys.h"
#include "point.h"
#include "vector.h"

#include <iostream>


using namespace cse;


int main( int argc, char** argv ) {
    using namespace std;

    CompVal cv;
    cv = 0;
    LogStdout( cv );
    cout << endl;

    cv = "First, Last";
    LogStdout( cv );
    cout << endl;

    Component cm;
    cm[Name] = cv;
    cm[Position] = Point2D(1,2);
    cm[Velocity] = Vector2D(3,4);
    LogStdout( cm[Name] );

    cout << endl;

    EntityMap em;
    em.insert( make_pair(0, cm) );

    cout << "pre physics:\n";
    LogSystem( em );
    PhysicsSystem( em );

    cout << "post physics:\n";
    LogSystem( em );

    return 0;
}

