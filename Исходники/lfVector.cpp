template< class V, class T > void _runSerialTest()
{
    V vector;

    _clock.reset();
    while( vector.size() < LOOPSIZE*10 )
        vector.push_back( T( 0 ));
    pTime_ = _clock.getTimef();

    _clock.reset();
    for( size_t i = 0; i < LOOPSIZE*10; ++i )
    {
        if( i < vector.size( ))
            vector[ i ] = i;
    }
    wTime_ = _clock.getTimef();

    _clock.reset();
    typename V::const_iterator it = vector.begin();
    for( size_t i = 0; i < LOOPSIZE*10; ++i )
    {
        const size_t value = *it;
        TESTINFO( i == value || value == 0, i << ", " << value );
        ++it;
        if( it == vector.end( ))
            it = vector.begin();
    }
    rTime_ = _clock.getTimef();

    _clock.reset();
    for( size_t i = 0; i < 10; ++i )
    {
        V copy;
        copy = vector;
        vector = copy;
        TEST( copy.size() >= vector.size( ));
    }
    cTime_ = _clock.getTimef();

    _clock.reset();
    const size_t pos = vector.size() / 2;
    typename V::iterator i = vector.begin() + pos;
    typename V::iterator j = vector.erase( i );
    TEST( j != vector.end( ));
    TEST( *j == 0 || *j >= pos );
    eTime_ = _clock.getTimef();

    _clock.reset();
    while( !vector.empty( ))
        vector.pop_back();
    const float fTime = _clock.getTimef();

    std::cerr << std::setw(11) << float(LOOPSIZE*10)/rTime_ << ", "
              << std::setw(11) << float(LOOPSIZE*10)/wTime_ << ", "
              << std::setw(11) << float(LOOPSIZE*10)/pTime_ << ", "
              << std::setw(9) << float(10)/cTime_ << ", "
              << std::setw(9) << float(10)/eTime_ << ", "
              << std::setw(9) << float(LOOPSIZE*10)/fTime << ", "
              << std::setw(3) << 0 << ", " << std::setw(3) << 0
              << std::endl;

    vector.push_back( 42 );
    i = vector.begin();
    i = vector.erase( i );
    TEST( i == vector.begin( ));
    TEST( vector.empty( ));

    vector.push_back( 42 );
    vector.push_back( 17 );
    vector.resize( 1 );
    TEST( vector.size() == 1 );
    TEST( vector[0] == 42 );

    vector.resize( 10, 17 );
    TEST( vector.size() == 10 );
    TEST( vector[0] == 42 );
    TEST( vector[1] == 17 );
    TEST( vector[9] == 17 );
}