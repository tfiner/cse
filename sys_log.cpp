#include "sys_log.h"
#include "point.h"
#include "vector.h"
#include "entity_map.h"
#include "comp_keys.h"

#include <boost/variant.hpp>

using namespace cse;


namespace {


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

} // namespace {


void cse::LogStdout( CompVal& val ) {
    boost::apply_visitor( LogToStdout(), val );
}


void cse::LogSystem( const EntityMap& em ) {
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

