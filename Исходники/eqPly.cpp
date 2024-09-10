int EqPly::run()
{
    // 1. connect to server
    eq::ServerPtr server = new eq::Server;
    if( !connectServer( server ))
    {
        LBERROR << "Can't open server" << std::endl;
        return EXIT_FAILURE;
    }

    // 2. choose config
    eq::fabric::ConfigParams configParams;
    Config* config = static_cast<Config*>(server->chooseConfig( configParams ));

    if( !config )
    {
        LBERROR << "No matching config on server" << std::endl;
        disconnectServer( server );
        return EXIT_FAILURE;
    }

    // 3. init config
    lunchbox::Clock clock;

    config->setInitData( _initData );
    if( !config->init( ))
    {
        LBWARN << "Error during initialization: " << config->getError()
               << std::endl;
        server->releaseConfig( config );
        disconnectServer( server );
        return EXIT_FAILURE;
    }
    if( config->getError( ))
        LBWARN << "Error during initialization: " << config->getError()
               << std::endl;

    LBLOG( LOG_STATS ) << "Config init took " << clock.getTimef() << " ms"
                       << std::endl;

    // 4. run main loop
    uint32_t maxFrames = _initData.getMaxFrames();
    int lastFrame = 0;

    clock.reset();
    while( config->isRunning( ) && maxFrames-- )
    {
        config->startFrame();
        if( config->getError( ))
            LBWARN << "Error during frame start: " << config->getError()
                   << std::endl;
        config->finishFrame();

        if( config->getAnimationFrame() == 1 )
        {
            const float time = clock.resetTimef();
            const size_t nFrames = config->getFinishedFrame() - lastFrame;
            lastFrame = config->getFinishedFrame();

            LBLOG( LOG_STATS ) << time << " ms for " << nFrames << " frames @ "
                               << ( nFrames / time * 1000.f) << " FPS)"
                               << std::endl;
        }

        while( !config->needRedraw( )) // wait for an event requiring redraw
        {
            if( hasCommands( )) // execute non-critical pending commands
            {
                processCommand();
                config->handleEvents(); // non-blocking
            }
            else  // no pending commands, block on user event
            {
                const eq::EventICommand& event = config->getNextEvent();
                if( !config->handleEvent( event ))
                    LBVERB << "Unhandled " << event << std::endl;
            }
        }
        config->handleEvents(); // process all pending events
    }
    const uint32_t frame = config->finishAllFrames();
    const float time = clock.resetTimef();
    const size_t nFrames = frame - lastFrame;
    LBLOG( LOG_STATS ) << time << " ms for " << nFrames << " frames @ "
                       << ( nFrames / time * 1000.f) << " FPS)" << std::endl;

    // 5. exit config
    clock.reset();
    config->exit();
    LBLOG( LOG_STATS ) << "Exit took " << clock.getTimef() << " ms" <<std::endl;

    // 6. cleanup and exit
    server->releaseConfig( config );
    if( !disconnectServer( server ))
        LBERROR << "Client::disconnectServer failed" << std::endl;

    return EXIT_SUCCESS;
}