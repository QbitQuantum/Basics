void ByteArrayBufferTest::testPutChar() {

    ByteBuffer* readOnly = testBuffer1->asReadOnlyBuffer();
    readOnly->clear();
    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should throw a ReadOnlyBufferException",
        readOnly->putChar( (char)1 ),
        ReadOnlyBufferException );
    delete readOnly;

    testBuffer1->clear();

    for( int i = 0; testBuffer1->remaining() > 0; i++ ) {

        testBuffer1->mark();
        testBuffer1->putChar( (char)i );
        testBuffer1->reset();
        CPPUNIT_ASSERT( testBuffer1->get() == (char)i );
    }

    CPPUNIT_ASSERT_THROW_MESSAGE(
        "Should throw a BufferOverflowException",
        testBuffer1->putChar( 'A' ),
        BufferOverflowException );
}