TEST_F(ProcessingTest, CallToProcessViaNodeWorker)
{
    NodeFacadeImplementationPtr times_4 = factory.makeNode("StaticMultiplier4", UUIDProvider::makeUUID_without_parent("StaticMultiplier4"), graph);
    Node& node = *times_4->getNode();
    NodeHandle& nh = *times_4->getNodeHandle();

    ASSERT_TRUE(node.canProcess());
    ASSERT_FALSE(times_4->isProcessing());
    ASSERT_FALSE(times_4->canProcess());

    // create a temporary output and connect it to the input
    OutputPtr tmp_out = std::make_shared<StaticOutput>(UUIDProvider::makeUUID_without_parent("tmp_out"));
    InputPtr input = nh.getInput(UUIDProvider::makeUUID_without_parent("StaticMultiplier4:|:in_0"));
    ASSERT_NE(nullptr, input);
    ConnectionPtr connection = DirectConnection::connect(tmp_out, input);

    // set the input message
    msg::publish(tmp_out.get(), 23);

    // mark the messages as committed
    tmp_out->commitMessages(false);
    tmp_out->publish();

    ASSERT_TRUE(node.canProcess());
    ASSERT_TRUE(times_4->canProcess());
    ASSERT_TRUE(nh.getInputTransition()->isEnabled());
    ASSERT_TRUE(nh.getOutputTransition()->isEnabled());

    // no inputs are sent now -> node should multiply the input by 4
    ASSERT_FALSE(times_4->isProcessing());
    ASSERT_TRUE(times_4->startProcessingMessages());

    // commit the messages produced by the node
    OutputPtr output = nh.getOutput(UUIDProvider::makeUUID_without_parent("StaticMultiplier4:|:out_0"));
    ASSERT_NE(nullptr, output);

    // view outputs
    TokenPtr token_out = output->getToken();
    TokenDataConstPtr data_out = token_out->getTokenData();
    ASSERT_NE(nullptr, data_out);

    auto msg_out = std::dynamic_pointer_cast<connection_types::GenericValueMessage<int> const>(data_out);
    ASSERT_NE(nullptr, msg_out);

    ASSERT_EQ(23 * 4, msg_out->value);
}