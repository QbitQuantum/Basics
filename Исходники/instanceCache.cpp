int main( int argc, char **argv )
{
    co::init( argc, argv );
    co::CommandCache commandCache;
    co::LocalNodePtr node = new co::LocalNode;

    co::Command& command = commandCache.alloc( node, node, PACKET_SIZE );
    co::ObjectInstancePacket* packet = 
        command.get< co::ObjectInstancePacket >();
    *packet = co::ObjectInstancePacket();
    packet->last = true;
    packet->dataSize = PACKET_SIZE;
    packet->version = 1;
    packet->sequence = 0;

    Reader** readers = static_cast< Reader** >( 
        alloca( N_READER * sizeof( Reader* )));

    co::InstanceCache cache;
    co::base::RNG rng;

    size_t hits = 0;
    size_t ops = 0;

    for( co::base::UUID key; key.low() < 65536; ++key ) // Fill cache
        if( !cache.add( co::ObjectVersion( key, 1 ), 1, command ))
            break;

    _clock.reset();
    for( size_t i = 0; i < N_READER; ++i )
    {
        readers[ i ] = new Reader( cache );
        readers[ i ]->start();
    }

    while( _clock.getTime64() < RUNTIME )
    {
        const co::base::UUID id( 0, rng.get< uint16_t >( ));
        const co::ObjectVersion key( id, 1 );
        if( cache[ key.identifier ] != co::InstanceCache::Data::NONE )
        {
            TEST( cache.release( key.identifier ));
            ++ops;
            if( cache.erase( key.identifier ))
            {
                TEST( cache.add( key, 1, command ));
                ops += 2;
                hits += 2;
            }
        }
        else if( cache.add( key, 1, command ))
            ++hits;
        ++ops;
    }

    const uint64_t time = _clock.getTime64();
    std::cout << hits << " write hits in " << ops << " operations, "
              << ops / time << " ops/ms" << std::endl;

    for( size_t i = 0; i < N_READER; ++i )
    {
        readers[ i ]->join();
        delete readers[ i ];
    }

    std::cout << cache << std::endl;

    for( co::base::UUID key; key.low() < 65536; ++key ) // Fill cache
    {
        if( cache[ key ] != co::InstanceCache::Data::NONE )
        {
            TEST( cache.release( key ));
            TEST( cache.erase( key ));
        }
    }

    for( co::base::UUID key; key.low() < 65536; ++key ) // Fill cache
    {
        TEST( cache[ key ] == co::InstanceCache::Data::NONE );
    }

    std::cout << cache << std::endl;

    TESTINFO( cache.getSize() == 0, cache.getSize( ));
    TEST( command.isFree( ));

    TEST( co::exit( ));
    return EXIT_SUCCESS;
}