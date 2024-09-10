int OSGScaleViewer::run()
{
    // 1. connect to server
    eq::ServerPtr server = new eq::Server();
    if( !connectServer( server ))
    {
        EQERROR << "Can't open server" << std::endl;
        return EXIT_FAILURE;
    }

    // 2. choose config
    eq::ConfigParams configParams;
    Config* config = static_cast<Config*>( server->chooseConfig( configParams));

    if( !config )
    {
        EQERROR << "No matching config on server" << std::endl;
        disconnectServer( server );
        return EXIT_FAILURE;
    }

    config->setInitData( _initData );
    if( !config->init( ))
    {
        server->releaseConfig( config );
        disconnectServer( server );
        return EXIT_FAILURE;
    }
    else if( config->getError( ))
        EQWARN << "Error during initialization: " << config->getError()
               << std::endl;

    // 4. run main loop
    while( config->isRunning( ))
    {
        config->startFrame();
        config->finishFrame();
    }
    config->finishAllFrames();

    // 5. exit config
    config->exit();

    // 6. cleanup and exit
    server->releaseConfig( config );
    if( !disconnectServer( server ))
        EQERROR << "Client::disconnectServer failed" << std::endl;

    server = 0;

    return EXIT_SUCCESS;
}