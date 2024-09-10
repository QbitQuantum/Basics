int main( const int argc, char** argv )
{
    eq::NodeFactory nodeFactory;
    TEST( eq::init( argc, argv, &nodeFactory ));

    eq::Config* config = eq::getConfig( argc, argv );
    TEST( config );

    size_t nLoops = 0;
    const lunchbox::Clock clock;
    while( clock.getTime64() < RUNTIME )
    {
        TEST( config->update( ));
        ++nLoops;
    }
    const float time = clock.getTimef();

    std::cout << nLoops << " Config::update in " << time << " ms (" << 
        time/float(nLoops) << " ms/update)" << std::endl;

    eq::releaseConfig( config );
    eq::exit();
    return EXIT_SUCCESS;
}