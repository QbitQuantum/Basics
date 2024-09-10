int main( int argc, char **argv )
{
    // setup
    eq::NodeFactory nodeFactory;
    TEST( eq::init( argc, argv, &nodeFactory ));

    for( size_t c = 0; c < 10; ++c )
    {
        eq::ClientPtr client = new Client;
        TEST( client->getRefCount() == 1 );
        TEST( client->initLocal( argc, argv ));

        eq::ServerPtr server = new eq::Server;
        TEST( server->getRefCount() == 1 );
        TEST( client->connectServer( server ));

        Config* config = new Config( server );
        for( size_t i = 0; i < 3; ++i )
        {
            Node* node = new Node( config );
            for( size_t j = 0; j < 3; ++j )
            {
                Pipe* pipe = new Pipe( node );
                for( size_t k = 0; k < 3; ++k )
                {
                    eq::Window* window = new eq::Window( pipe );
                    for( size_t l = 0; l < 3; ++l )
                        new Channel( window );
                }
            }
        }

        // tests
        TestVisitor visitor;
        const VisitorResult result = config->accept( visitor );

        TESTINFO( result == TRAVERSE_TERMINATE, result );
        TESTINFO( visitor.nConfigs == 1,   visitor.nConfigs );
        TESTINFO( visitor.nNodes == 3,     visitor.nNodes );
        TESTINFO( visitor.nPipes == 5,     visitor.nPipes );
        TESTINFO( visitor.nWindows == 12,  visitor.nWindows );
        TESTINFO( visitor.nChannels == 36, visitor.nChannels );

        // cleanup and exit
        server->releaseConfig( config );
        TEST( client->disconnectServer( server ));
        // teardown
        TEST( client->exitLocal( ));
    }
    return EXIT_SUCCESS;
}