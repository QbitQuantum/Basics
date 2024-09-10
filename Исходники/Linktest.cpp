void Linktest::test_send_connected()
{
    CommSocket_flush_called = false;

    m_encoder = new Atlas::Objects::ObjectsEncoder(*m_bridge);
    m_link->setEncoder(m_encoder);

    Operation op;

    m_link->send(op);

    ASSERT_TRUE(CommSocket_flush_called);
}