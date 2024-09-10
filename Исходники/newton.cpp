int main( int argc , char *argv[] )
{
    using namespace std;

    cout.precision( 14 );

    auto f = []( auto x ) { return exp( - x * x ) - 0.5; };
    auto df = []( auto x ) { return -2.0 * x * exp( -x * x ); };

    { // example 1 without ranges

        double x = 1.0;
        double root = newton( x , f , df );
        cout << "Solution: " << root << " " << f( root ) << endl;
    }

    { // example 2 with ranges
        double x = 1.0;
        auto r = make_newton_range( x , f , df );
        auto r2 = ranges::view::take_while( r , [f]( auto x ) {
                using std::abs;
                return abs( f(x) ) > 1.0e-12; } );

        ranges::for_each( r2 , [f]( auto x ) {
                cout << x << " " << f(x) << "\n";
        } );
        cout << "Solution: " << r.x() << " " << r.y() << endl;
    }


        

    return 0;
}