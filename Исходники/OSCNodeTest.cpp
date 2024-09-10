/**
 * Called when we receive DMX data via OSC. We check this matches what we
 * expect, and then stop the SelectServer.
 */
void OSCNodeTest::DMXHandler(const DmxBuffer &dmx) {
  m_received_data = dmx;
  m_ss.Terminate();
}