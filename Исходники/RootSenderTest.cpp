void RootSenderTest::Stop() {
  if (m_ss)
    m_ss->Terminate();
}