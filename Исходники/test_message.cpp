    static const fudge_byte rawBytesArray [ 16 ] = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };
    static const fudge_i16 rawShortsArray [ 10 ] = { -32767, 32767, 0, 1, -1, 100, -100, 0, 16385 };
    static const fudge_i32 rawIntsArray [ 4 ] = { 2147483647, 0, -2147483647, 0 };
    static const fudge_i64 rawLongsArray [ 12 ] = { ( fudge_i64 ) -9223372036854775807ll, 0, ( fudge_i64 ) 9223372036854775807ll, -1, 2, -3, 5, -8, 13, -21, 34, -55 };
    static const fudge_f32 rawFloatsArray [ 8 ] = { 0.0f, 2147483647.0f, 214748364.7f, 21474836.47f, 2147483.647f, 2.147483647f, 21.47483647f, 214.7483647f };
    static const fudge_f64 rawDoublesArray [ 5 ] = { 9223372036854775807.0, 0.0, 0.0000000123456, 1234560000000.0, -9223372036854775807.0 };

    std::vector<fudge_byte> rawBytes ( rawBytesArray, rawBytesArray + sizeof ( rawBytesArray ) / sizeof ( fudge_byte ) );
    std::vector<fudge_i16> rawShorts ( rawShortsArray, rawShortsArray + sizeof ( rawShortsArray ) / sizeof ( fudge_i16 ) );
    std::vector<fudge_i32> rawInts ( rawIntsArray, rawIntsArray + sizeof ( rawIntsArray ) / sizeof ( fudge_i32 ) );
    std::vector<fudge_i64> rawLongs ( rawLongsArray, rawLongsArray + sizeof ( rawLongsArray ) / sizeof ( fudge_i64 ) );
    std::vector<fudge_f32> rawFloats ( rawFloatsArray, rawFloatsArray + sizeof ( rawFloatsArray ) / sizeof ( fudge_f32 ) );
    std::vector<fudge_f64> rawDoubles ( rawDoublesArray, rawDoublesArray + sizeof ( rawDoublesArray ) / sizeof ( fudge_f64 ) );

    static const date exampleDate ( 2010, 3, 21 );
    static const time exampleTime ( 15 * 3600 + 39 * 60 + 27, 0, FUDGE_DATETIME_PRECISION_SECOND );
    static const datetime exampleDateTime ( exampleDate.year ( ), exampleDate.month ( ), exampleDate.day ( ), exampleTime.seconds ( ), exampleTime.nanoseconds ( ), exampleTime.precision ( ) );

    // Will need a large byte array for the fixed array testing
    fudge_byte largeByteArray [ 512 ];
    for ( size_t index ( 0 ); index < sizeof ( largeByteArray ); ++index )
        largeByteArray [ index ] = index % 256 - 128;

    // Construct an empty message
    message message1;
    TEST_EQUALS_INT( message1.size ( ), 0 );

    // Test some failure cases
    TEST_THROWS_EXCEPTION( message1.getFieldAt (  0 ), exception );                         // Invalid index
    TEST_THROWS_EXCEPTION( message1.getField ( static_cast<fudge_i16> ( 0 ) ), exception ); // Invalid ordinal
    TEST_THROWS_EXCEPTION( message1.getField ( string ( "Field Name" ) ), exception );      // Invalid field name