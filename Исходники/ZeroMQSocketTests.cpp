void ZeroMQSocketTests::testIPV6() {
    const std::string endpoint("tcp://[::1]:19992");  // IPv6 localhost
    const std::string outgoingMessage("Hello, world!");
    ZeroMQSocket::Message incomingMessage;
    
    ZeroMQSocket sender(ZMQ_PUSH);
    CPPUNIT_ASSERT( sender.setOption(ZMQ_IMMEDIATE, 1) );
    
    ZeroMQSocket receiver(ZMQ_PULL);
    
    CPPUNIT_ASSERT( sender.connect(endpoint) );
    CPPUNIT_ASSERT( receiver.bind(endpoint) );
    
    CPPUNIT_ASSERT( ZeroMQSocket::Result::ok == sender.send(outgoingMessage.data(), outgoingMessage.size()) );
    CPPUNIT_ASSERT( ZeroMQSocket::Result::ok == incomingMessage.recv(receiver) );
    CPPUNIT_ASSERT_EQUAL( outgoingMessage, std::string(static_cast<const char *>(incomingMessage.getData()),
                                                       incomingMessage.getSize()) );
    
    CPPUNIT_ASSERT( sender.disconnect(endpoint) );
    CPPUNIT_ASSERT( receiver.unbind(endpoint) );
}