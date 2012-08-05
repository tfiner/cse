#include "sys_physics.h"
#include "entity_map.h"

#include "entity.h"
#include "component.h"
#include "comp_keys.h"
#include "point.h"
#include "vector.h"

#include <iostream>


using namespace cse;



class LogToStdout : public boost::static_visitor<void> {
public:
    LogToStdout(int indent=0) : indent_(indent) {}

    template<typename T>
    void operator()( const T& t ) const {
        for ( int i = 0; i < indent_; ++i )
            std::cout << " ";
        std::cout << t;
    }

    int indent_;
};


void LogSystem( const EntityMap& em ) {
    using namespace std;
    for ( auto e : em ) {
        cout << "entity: " << e.first << "\n";

        auto & comps = e.second;
        for ( auto & c : comps ) {
            cout << "   key: " << c.first << " value: ";
            boost::apply_visitor( LogToStdout(3), c.second );
            cout <<  endl;
        }
    }
}


int main( int argc, char** argv ) {
    using namespace std;

    CompVal cv;
    cv = 0;
    boost::apply_visitor( LogToStdout(), cv );
    cout << endl;

    cv = "First, Last";
    boost::apply_visitor( LogToStdout(), cv );
    cout << endl;

    Component cm;
    cm[Name] = cv;
    cm[Position] = Point2D(1,2);
    cm[Velocity] = Vector2D(3,4);
    boost::apply_visitor( LogToStdout(), cm[Name] );
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

