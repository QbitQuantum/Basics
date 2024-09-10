int main()
{
    printf( "EXCOK: start\n" );
    set_terminate( &no_handler );
    test_basics();
    test_scalars();
    init_class();
    test_class();
    test_cl_ptrs();
    test_passthru();
    test_rethrow();
    try {
        ++throws;
        set_unexpected( &unexp );
        test_unexpected();
    } catch( long l ) {
        ++catches;
        if( l != 675L ) {
            printf( "unexpected failure %l\n", l );
        }
    }
    if( throws != catches ) {
        printf( "catches != throws\n" );
    }
    set_terminate( &my_term );
    test_term();

    printf( "terminate did not abort\n" );
    return( 0 );
}