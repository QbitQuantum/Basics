void ConnectionErrorMarshallerTest::testTightMarshal() {

    ConnectionErrorMarshaller marshaller;
    Properties props;
    OpenWireFormat openWireFormat( props );

    // Configure for this test.
    openWireFormat.setVersion( 1 );
    openWireFormat.setTightEncodingEnabled( true );

    ConnectionError outCommand;
    ConnectionError inCommand;

    try {

        // Marshal the dataStructure to a byte array.
        ByteArrayOutputStream baos;
        DataOutputStream dataOut( &baos );
        // Phase 1 - count the size
        int size = 1;
        BooleanStream bs;
        size += marshaller.tightMarshal1( &openWireFormat, &outCommand, &bs );
        size += bs.marshalledSize();
        // Phase 2 - marshal
        dataOut.writeByte( outCommand.getDataStructureType() );
        bs.marshal( &dataOut );
        marshaller.tightMarshal2( &openWireFormat, &outCommand, &dataOut, &bs );

        // Now read it back in and make sure it's all right.
        std::pair<const unsigned char*, int> array = baos.toByteArray();
        ByteArrayInputStream bais( array.first, array.second, true );
        DataInputStream dataIn( &bais );

        unsigned char dataType = dataIn.readByte();
        CPPUNIT_ASSERT( dataType == outCommand.getDataStructureType() );
        bs.clear();
        bs.unmarshal( &dataIn );
        marshaller.tightUnmarshal( &openWireFormat, &inCommand, &dataIn, &bs );

        CPPUNIT_ASSERT( inCommand.equals( &outCommand ) == true );

    } catch( ActiveMQException& e ) {
        e.printStackTrace();
        CPPUNIT_ASSERT( false );
    } catch( ... ) {
        CPPUNIT_ASSERT( false );
    }
}