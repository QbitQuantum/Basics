void RpcChannelTest::EchoComplete() {
  m_ss.Terminate();
  OLA_ASSERT_FALSE(m_controller.Failed());
  OLA_ASSERT_EQ(m_reply.data(), m_request.data());
}