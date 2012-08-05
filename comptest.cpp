#include "entity.h"

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include <string>
#include <unordered_map>
#include <map>
#include <functional>
#include <iostream>


enum CompKey {
    Position,
    Velocity,
    Health,
    Shield,
    Direction,
    Name
};

struct CompKeyLess : public std::binary_function<CompKey,CompKey,bool> {
    bool operator()(const CompKey& lhs, const CompKey& rhs) const {
        return static_cast<unsigned int>(lhs) < static_cast<unsigned int>(rhs);
    }
};

struct Point2D { 
    Point2D() : x(0), y(0) {}
    Point2D(float x_, float y_) : x(x_), y(y_) {}
    float x, y; 
};

std::ostream& operator<<(std::ostream& os, const Point2D& p) {
    os << p.x << "," << p.y;
    return os;
}

struct Vector2D { 
    Vector2D() : x(0), y(0) {}
    Vector2D(float x_, float y_) : x(x_), y(y_) {}
    float x, y; 
};

std::ostream& operator<<(std::ostream& os, const Vector2D& p) {
    os << p.x << "," << p.y;
    return os;
}


typedef boost::variant< int, float, std::string, Point2D, Vector2D> CompVal;
typedef std::map< CompKey, CompVal, CompKeyLess > CompMap;
typedef std::unordered_map< cse::Entity, CompMap > EntityMap;

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

class LogToStdout : public boost::static_visitor<void> {
public:
    LogToStdout(int indent=0) : indent_(indent) {}

    template<typename T>
    void operator()( const T& t ) const {
        for ( int i = 0; i < indent_; ++i )
            std::cout << " ";
        std::cout << t;
        // std::cout << __FUNCTION__ << "\n";
        // std::cout << typeid(t).name() << "\n";
        // std::cout << t << std::endl;
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

void PhysicsSystem( EntityMap& em ) {
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

        boost::apply_visitor( UpdatePosition(), pos->second, vel->second );
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

    CompMap cm;
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

