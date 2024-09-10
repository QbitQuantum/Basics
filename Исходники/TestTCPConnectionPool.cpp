// TestMultipleServersOneClient
//------------------------------------------------------------------------------
void TestTestTCPConnectionPool::TestMultipleServersOneClient() const
{
    const uint16_t testPort( TEST_PORT );

    for ( uint32_t i=0; i<NUM_TEST_PASSES; ++i )
    {
        // multiple servers
        TCPConnectionPool serverA;
        TEST_ASSERT( serverA.Listen( testPort ) );
        TCPConnectionPool serverB;
        TEST_ASSERT( serverB.Listen( testPort + 1 ) );
        TCPConnectionPool serverC;
        TEST_ASSERT( serverC.Listen( testPort + 2 ) );
        TCPConnectionPool serverD;
        TEST_ASSERT( serverD.Listen( testPort + 3 ) );

        // connect client to multiple servers
        TCPConnectionPool clientA;
        TEST_ASSERT( clientA.Connect( AStackString<>( "127.0.0.1" ), testPort ) );
        TEST_ASSERT( clientA.Connect( AStackString<>( "127.0.0.1" ), testPort + 1 ) );
        TEST_ASSERT( clientA.Connect( AStackString<>( "127.0.0.1" ), testPort + 2 ) );
        TEST_ASSERT( clientA.Connect( AStackString<>( "127.0.0.1" ), testPort + 3 ) );
    }
}