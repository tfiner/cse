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
// typedef int CompVal;
typedef std::map< CompKey, CompVal, CompKeyLess > CompMap;
typedef std::unordered_map< cse::Entity, CompMap > EntityMap;

// This takes two variants and if 
// one is a position and the other is a vector,
// updates the position with the vector as a velocity.
/*
class UpdatePosition
    : public boost::static_visitor<void> {
public:
    void operator()( const Point2D& p, const Vector2D& v ) const {
        assert( !"You can't add a vector to a const point!" );
    }

    void operator()( const Vector2D& v, const Point2D& p ) const {
        assert( !"You can't add a point to a vector!" );
    }

    void operator()( Vector2D& v, const Point2D& p ) const {
        assert( !"You can't add a point to a vector!" );
    }

    void operator()( Point2D& p, const Vector2D& v ) const
    {
        p.x += v.x;
        p.y += v.y;
    }

};
*/

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

void PhysicsSys( EntityMap& em ) {
    for( auto & e : em ) {

        auto name = em.find(Name);
        if ( name != em.end() ) {
            auto & var = name->second;
//            auto & vars = boost::get<int>(var);
//            std::cout << vars;
//            boost::apply_visitor( LogToStdout(), var );
        }

        // If the entity has components for position and vector, then
        // update the position component.
        auto pos = em.find(Position);
        if ( pos == em.end() )
            continue;

        auto vel = em.find(Velocity);
        if ( vel == em.end() )
            continue;

//        boost::apply_visitor( UpdatePosition(), *pos, *vel );
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
    boost::apply_visitor( LogToStdout(), cm[Name] );
    cout << endl;

    EntityMap em;
    em.insert( make_pair(0, cm) );

    for ( auto e : em ) {
        cout << "entity: " << e.first << "\n";
        auto & comps = e.second;
        for ( auto & c : comps ) {
            cout << "   key: " << c.first << " value: ";
        // auto comps = em.equal_range(0);
        // for ( auto c = comps.first; c != comps.second; ++c ) {
            boost::apply_visitor( LogToStdout(3), c.second );
            cout <<  endl;

            // for( auto v : c.second ) 
            //     boost::apply_visitor( LogToStdout(3), v.second );
        }
    }

/*
    CompMap cm;
    cm[Name] = "0";
    // cm[Position] = Point2D(0,0);
    // cm[Velocity] = Vector2D(0,0);

    EntityMap em;
    em.insert( std::make_pair(0, cm) );
*/
    return 0;
}

