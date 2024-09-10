TEST_F(AutoGenerateTest, OrderDoesNotMatterTypesAreDetected)
{
    factory.registerNodeType(GenericNodeFactory::createConstructorFromFunction(f3, "f3"));

    UUID node_id = UUIDProvider::makeUUID_without_parent("foobarbaz");
    NodeFacadeImplementationPtr node = factory.makeNode("f3", node_id, uuid_provider);

    ASSERT_TRUE(node != nullptr);
    ASSERT_EQ(node_id, node->getUUID());

    ASSERT_EQ(node->getParameters().size(), 3);

    ASSERT_EQ(node->getInputs().size(), 2 + node->getParameters().size());
    ASSERT_EQ(node->getOutputs().size(), 1 + node->getParameters().size());

    GenericValueMessage<int>::Ptr a(new GenericValueMessage<int>);
    GenericValueMessage<double>::Ptr b(new GenericValueMessage<double>);

    a->value = 23;
    b->value = 42.0;

    InputPtr i1 = node->getNodeHandle()->getInput(UUIDProvider::makeDerivedUUID_forced(node_id, "in_0"));
    ASSERT_TRUE(i1 != nullptr);

    InputPtr i2 = node->getNodeHandle()->getInput(UUIDProvider::makeDerivedUUID_forced(node_id, "in_1"));
    ASSERT_TRUE(i2 != nullptr);

    TokenPtr ta = std::make_shared<Token>(a);
    TokenPtr tb = std::make_shared<Token>(b);

    param::ParameterPtr p_1 = node->getParameter("param 0");
    ASSERT_TRUE(p_1 != nullptr);
    p_1->set<int>(1337);

    param::ParameterPtr p_2 = node->getParameter("param 4");
    ASSERT_TRUE(p_2 != nullptr);
    p_2->set<int>(4);

    param::ParameterPtr p_3 = node->getParameter("param 5");
    ASSERT_TRUE(p_3 != nullptr);
    p_3->set<int>(5);

    i1->setToken(ta);
    i2->setToken(tb);

    NodePtr n = node->getNode();
    n->process(*node->getNodeHandle(), *n);

    OutputPtr o = node->getNodeHandle()->getOutput(UUIDProvider::makeDerivedUUID_forced(node_id, "out_0"));
    ASSERT_TRUE(o != nullptr);

    o->commitMessages(false);

    TokenPtr to = o->getToken();
    ASSERT_TRUE(to != nullptr);
    ASSERT_TRUE(to->getTokenData() != nullptr);

    GenericValueMessage<std::string>::ConstPtr result = std::dynamic_pointer_cast<GenericValueMessage<std::string> const>(to->getTokenData());
    ASSERT_TRUE(result != nullptr);

    ASSERT_EQ("1411", result->value);
}