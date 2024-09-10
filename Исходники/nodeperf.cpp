int main( int argc, char **argv )
{
    if( !co::init( argc, argv ))
        return EXIT_FAILURE;

    co::ConnectionDescriptionPtr remote;
    size_t packetSize = 1048576u; // needs to be modulo 8
    uint32_t nPackets = 0xFFFFFFFFu;
    uint32_t waitTime = 0;
    bool useZeroconf = true;
    bool useObjects = false;

    try // command line parsing
    {
        TCLAP::CmdLine command(
            "nodeperf - Collage node-to-node network benchmark tool", ' ',
            co::Version::getString( ));
        TCLAP::ValueArg< std::string > remoteArg( "c", "connect",
                "connect to remote node, implies --disableZeroconf",
                false, "",
                "IP[:port][:protocol]",
                command );
        TCLAP::SwitchArg zcArg( "d", "disableZeroconf",
                                "Disable automatic connect using zeroconf",
                                command, false );
        TCLAP::SwitchArg objectsArg( "o", "object",
                                     "Benchmark object-object instead of node-node communication",
                                     command, false );
        TCLAP::ValueArg<size_t> sizeArg( "p", "packetSize", "packet size",
                                         false, packetSize, "unsigned",
                                         command );
        TCLAP::ValueArg<size_t> packetsArg( "n", "numPackets",
                                            "number of packets to send",
                                            false, nPackets, "unsigned",
                                            command );
        TCLAP::ValueArg<uint32_t> waitArg( "w", "wait",
                                           "wait time (ms) between sends",
                                           false, 0, "unsigned", command );
        command.parse( argc, argv );

        if( remoteArg.isSet( ))
        {
            remote = new co::ConnectionDescription;
            remote->port = 4242;
            remote->fromString( remoteArg.getValue( ));
        }
        useZeroconf = !zcArg.isSet();
        useObjects = objectsArg.isSet();

        if( sizeArg.isSet( ))
            packetSize = sizeArg.getValue();
        if( packetsArg.isSet( ))
            nPackets = uint32_t( packetsArg.getValue( ));
        if( waitArg.isSet( ))
            waitTime = waitArg.getValue();
    }
    catch( TCLAP::ArgException& exception )
    {
        LBERROR << "Command line parse error: " << exception.error()
                << " for argument " << exception.argId() << std::endl;

        co::exit();
        return EXIT_FAILURE;
    }

    // Set up local node
    co::LocalNodePtr localNode = new PerfNode;
    if( !localNode->initLocal( argc, argv ))
    {
        co::exit();
        return EXIT_FAILURE;
    }
    localNode->getZeroconf().set( "coNodeperf", co::Version::getString( ));

    Object object;
    object.setID( _objectID + localNode->getNodeID( ));
    LBCHECK( localNode->registerObject( &object ));

    // run
    if( remote )
    {
        co::NodePtr node = new PerfNodeProxy;
        node->addConnectionDescription( remote );
        localNode->connect( node );
    }
    else if( useZeroconf )
    {
        co::Zeroconf zeroconf = localNode->getZeroconf();
        const co::Strings& instances = localNode->getZeroconf().getInstances();
        BOOST_FOREACH( const std::string& instance, instances )
        {
            if( !zeroconf.get( instance, "coNodeperf" ).empty( ))
                localNode->connect( co::uint128_t( instance ));
        }
    }
    {
        lunchbox::ScopedFastRead _mutex( nodes_ );
        if( nodes_->empty( ))
            // Add default listener so others can connect to me
            localNode->addListener( new co::ConnectionDescription );
    }

    co::Nodes nodes;
    while( true )
    {
        lunchbox::Thread::yield();

        lunchbox::ScopedFastRead _mutex( nodes_ );
        if( !nodes_->empty( ))
            break;
    }

    Buffer buffer;
    const size_t bufferElems = packetSize / sizeof( uint64_t );
    buffer.resize( bufferElems );
    for( size_t i = 0; i < bufferElems; ++i )
        buffer[i] = i;

    const float mBytesSec = buffer.getNumBytes() / 1024.0f / 1024.0f * 1000.0f;
    lunchbox::Clock clock;
    size_t sentPackets = 0;

    clock.reset();
    while( nPackets-- )
    {
        {
            lunchbox::ScopedFastRead _mutex( nodes_ );
            if( nodes != *nodes_ )
            {
                for( co::NodesCIter i = nodes_->begin(); i != nodes_->end(); ++i)
                {
                    co::NodePtr node = *i;
                    co::NodesCIter j = stde::find( nodes, node );
                    if( j == nodes.end( ))
                    {
                        // new node, map perf object
                        LBASSERT( node->getType() == 0xC0FFEEu );
                        PerfNodeProxyPtr peer =
                            static_cast< PerfNodeProxy* >( node.get( ));
                        LBCHECK( localNode->mapObject( &peer->object,
                                                       _objectID + peer->getNodeID( )));
                    }
                }
                nodes = *nodes_;
            }
        }
        if( nodes.empty( ))
            break;

        for( co::NodesCIter i = nodes.begin(); i != nodes.end(); ++i )
        {
            co::NodePtr node = *i;
            if( node->getType() != 0xC0FFEEu )
                continue;

            if( useObjects )
            {
                const size_t j = (object.getID().low() + nPackets) %
                                 bufferElems;
                buffer[ j ] = nPackets;
                object.send( node, co::CMD_OBJECT_CUSTOM ) << nPackets <<buffer;
                buffer[ j ] = 0xDEADBEEFu;
            }
            else
            {
                const size_t j = (node->getNodeID().low() + nPackets) %
                                 bufferElems;
                buffer[ j ] = nPackets;
                node->send( co::CMD_NODE_CUSTOM ) << nPackets << buffer;
                buffer[ j ] = 0xDEADBEEFu;
            }
            ++sentPackets;

            if( waitTime > 0 )
                lunchbox::sleep( waitTime );
        }

        const float time = clock.getTimef();
        if( time > 1000.f )
        {
            const lunchbox::ScopedMutex<> mutex( print_ );
            std::cerr << "Send perf: " << mBytesSec / time * sentPackets
                      << "MB/s (" << sentPackets / time * 1000.f  << "pps)"
                      << std::endl;
            sentPackets = 0;
            clock.reset();
        }
    }

    const float time = clock.getTimef();
    if( time > 1000.f )
    {
        const lunchbox::ScopedMutex<> mutex( print_ );
        std::cerr << "Send perf: " << mBytesSec / time * sentPackets
                  << "MB/s (" << sentPackets / time * 1000.f  << "pps)"
                  << std::endl;
        sentPackets = 0;
        clock.reset();
    }

    localNode->deregisterObject( &object );
    LBCHECK( localNode->exitLocal( ));
    LBCHECK( co::exit( ));
    return EXIT_SUCCESS;
}