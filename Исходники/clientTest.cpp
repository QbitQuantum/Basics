/*
 * Check that the DMX get/set works correctly.
 */
void ClientTest::testGetSetDMX() {
  DmxBuffer buffer(TEST_DATA);
  const DmxBuffer empty;
  Client client(NULL);

  ola::TimeStamp timestamp;
  m_clock.CurrentTime(&timestamp);
  ola::DmxSource source(buffer, timestamp, 100);

  // check get/set works
  client.DMXRecieved(TEST_UNIVERSE, source);
  const ola::DmxSource &source2 = client.SourceData(TEST_UNIVERSE);
  OLA_ASSERT(source2.IsSet());
  OLA_ASSERT(source2.Data() == buffer);
  OLA_ASSERT_EQ(timestamp, source2.Timestamp());
  OLA_ASSERT_EQ((uint8_t) 100, source2.Priority());

  // check update works
  ola::DmxBuffer old_data(buffer);
  buffer.Set(TEST_DATA2);
  OLA_ASSERT(source2.Data() == old_data);
  OLA_ASSERT_EQ(timestamp, source2.Timestamp());
  OLA_ASSERT_EQ((uint8_t) 100, source2.Priority());

  source.UpdateData(buffer, timestamp, 120);
  client.DMXRecieved(TEST_UNIVERSE, source);
  const ola::DmxSource source3 = client.SourceData(TEST_UNIVERSE);
  OLA_ASSERT(source3.IsSet());
  OLA_ASSERT(buffer == source3.Data());
  OLA_ASSERT_EQ(timestamp, source3.Timestamp());
  OLA_ASSERT_EQ((uint8_t) 120, source3.Priority());

  // check fetching an unknown universe results in an empty buffer
  const ola::DmxSource source4 = client.SourceData(TEST_UNIVERSE2);
  OLA_ASSERT_FALSE(source4.IsSet());
  OLA_ASSERT(empty == source4.Data());
}