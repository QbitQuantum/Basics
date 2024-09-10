void DEFAULTPACKETSTREAMERTF::testProcessData() {
    DefaultPacketFactory *factory =  new DefaultPacketFactory();
    DefaultPacketStreamer *streamer = new DefaultPacketStreamer(factory);
    DataBuffer *buffer = new DataBuffer;
    StreamingContext *context = streamer->createContext();
    CPPUNIT_ASSERT(context);

    DefaultPacket *packet = new DefaultPacket;
    DefaultPacket *result = NULL;
    size_t bodyLength;
    CPPUNIT_ASSERT(streamer->processData(buffer, context));
    CPPUNIT_ASSERT(!context->isBroken());
    CPPUNIT_ASSERT(!context->isCompleted());

    packet->setBody("",0);
    CPPUNIT_ASSERT(streamer->encode(packet, buffer));
    CPPUNIT_ASSERT(streamer->processData(buffer, context));
    CPPUNIT_ASSERT(!context->isBroken());
    CPPUNIT_ASSERT(context->isCompleted());
    result = dynamic_cast<DefaultPacket*>(context->getPacket());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(!result->getBody(bodyLength));
    CPPUNIT_ASSERT_EQUAL((size_t)0, bodyLength);
    context->reset();

    packet->setBody("a",1);
    CPPUNIT_ASSERT(streamer->encode(packet, buffer));
    CPPUNIT_ASSERT(streamer->processData(buffer, context));
    CPPUNIT_ASSERT(!context->isBroken());
    CPPUNIT_ASSERT(context->isCompleted());
    result = dynamic_cast<DefaultPacket*>(context->getPacket());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(result->getBody(bodyLength));
    CPPUNIT_ASSERT_EQUAL('a', *(result->getBody(bodyLength)));
    CPPUNIT_ASSERT_EQUAL((size_t)1, bodyLength);
    context->reset();

    packet->setBody("ab",2);
    CPPUNIT_ASSERT(streamer->encode(packet, buffer));
    packet->setBody("a",1);
    CPPUNIT_ASSERT(streamer->encode(packet, buffer));
    CPPUNIT_ASSERT(streamer->processData(buffer, context));
    CPPUNIT_ASSERT(!context->isBroken());
    CPPUNIT_ASSERT(context->isCompleted());
    result = dynamic_cast<DefaultPacket*>(context->getPacket());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(result->getBody(bodyLength));
    CPPUNIT_ASSERT_EQUAL('a', *(result->getBody(bodyLength)));
    CPPUNIT_ASSERT_EQUAL('b', *(result->getBody(bodyLength) + 1));
    CPPUNIT_ASSERT_EQUAL((size_t)2, bodyLength);
    context->reset();
    CPPUNIT_ASSERT(streamer->processData(buffer, context));
    CPPUNIT_ASSERT(!context->isBroken());
    CPPUNIT_ASSERT(context->isCompleted());
    result = dynamic_cast<DefaultPacket*>(context->getPacket());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(result->getBody(bodyLength));
    CPPUNIT_ASSERT_EQUAL('a', *(result->getBody(bodyLength)));
    CPPUNIT_ASSERT_EQUAL((size_t)1, bodyLength);
    context->reset();


    delete streamer;
    delete factory;
    delete buffer;
    delete packet;
    delete context;
}