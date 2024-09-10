void ActiveMQMapMessageTest::testReadOnlyBody() {

    ActiveMQMapMessage msg;
    std::vector<unsigned char> buffer(2);

    msg.setBoolean( "boolean", true );
    msg.setByte( "byte", (unsigned char)1 );
    msg.setBytes( "bytes", buffer );
    msg.setChar( "char", 'a' );
    msg.setDouble( "double", 1.5 );
    msg.setFloat( "float", 1.5f );
    msg.setInt( "int", 1 );
    msg.setLong( "long", 1 );
    msg.setShort( "short", (short)1 );
    msg.setString( "string", "string" );

    msg.setReadOnlyBody( true );

    try {
        msg.getBoolean( "boolean" );
        msg.getByte( "byte" );
        msg.getBytes( "bytes" );
        msg.getChar( "char" );
        msg.getDouble( "double" );
        msg.getFloat( "float" );
        msg.getInt( "int" );
        msg.getLong( "long" );
        msg.getShort( "short" );
        msg.getString( "string" );
    } catch( MessageNotReadableException& mnre ) {
        CPPUNIT_FAIL( "should be readable" );
    }
    try {
        msg.setBoolean( "boolean", true );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setByte( "byte", (unsigned char)1 );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setBytes( "bytes", buffer );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setChar( "char", 'a' );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setDouble( "double", 1.5 );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setFloat( "float", 1.5f );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setInt( "int", 1 );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setLong( "long", 1 );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setShort( "short", (short)1 );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
    try {
        msg.setString( "string", "string" );
        CPPUNIT_FAIL( "should throw exception" );
    } catch( MessageNotWriteableException& mnwe ) {
    }
}