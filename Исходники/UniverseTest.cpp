/*
 * Check that HTP merging works correctly
 */
void UniverseTest::testHtpMerging() {
  DmxBuffer buffer1, buffer2, htp_buffer;
  buffer1.SetFromString("1,0,0,10");
  buffer2.SetFromString("0,255,0,5,6,7");
  htp_buffer.SetFromString("1,255,0,10,6,7");

  ola::PortBroker broker;
  ola::PortManager port_manager(m_store, &broker);

  TimeStamp time_stamp;
  MockSelectServer ss(&time_stamp);
  ola::PluginAdaptor plugin_adaptor(NULL, &ss, NULL, NULL, NULL, NULL);
  MockDevice device(NULL, "foo");
  MockDevice device2(NULL, "bar");
  TestMockInputPort port(&device, 1, &plugin_adaptor);  // input port
  TestMockInputPort port2(&device2, 1, &plugin_adaptor);  // input port
  port_manager.PatchPort(&port, TEST_UNIVERSE);
  port_manager.PatchPort(&port2, TEST_UNIVERSE);

  Universe *universe = m_store->GetUniverseOrCreate(TEST_UNIVERSE);
  OLA_ASSERT(universe);
  universe->SetMergeMode(Universe::MERGE_HTP);

  OLA_ASSERT_EQ(universe->OutputPortCount(), (unsigned int) 0);
  OLA_ASSERT_EQ(universe->OutputPortCount(), (unsigned int) 0);
  OLA_ASSERT(universe->IsActive());
  OLA_ASSERT_EQ((unsigned int) 0, universe->GetDMX().Size());

  // Setup the ports with some data, and check that signalling the universe
  // works.
  m_clock.CurrentTime(&time_stamp);
  port.WriteDMX(buffer1);
  port.DmxChanged();
  OLA_ASSERT_EQ(ola::dmx::SOURCE_PRIORITY_DEFAULT, universe->ActivePriority());
  OLA_ASSERT_EQ(buffer1.Size(), universe->GetDMX().Size());
  OLA_ASSERT(buffer1 == universe->GetDMX());

  // Now the second port gets data
  m_clock.CurrentTime(&time_stamp);
  port2.WriteDMX(buffer2);
  port2.DmxChanged();
  OLA_ASSERT_EQ(ola::dmx::SOURCE_PRIORITY_DEFAULT, universe->ActivePriority());
  OLA_ASSERT_EQ(htp_buffer.Size(), universe->GetDMX().Size());
  OLA_ASSERT(htp_buffer == universe->GetDMX());

  // now raise the priority of the second port
  uint8_t new_priority = 120;
  port2.SetPriority(new_priority);
  m_clock.CurrentTime(&time_stamp);
  port2.DmxChanged();
  OLA_ASSERT_EQ(new_priority, universe->ActivePriority());
  OLA_ASSERT_EQ(buffer2.Size(), universe->GetDMX().Size());
  OLA_ASSERT(buffer2 == universe->GetDMX());

  // raise the priority of the first port
  port.SetPriority(new_priority);
  m_clock.CurrentTime(&time_stamp);
  port.DmxChanged();
  OLA_ASSERT_EQ(new_priority, universe->ActivePriority());
  OLA_ASSERT_EQ(htp_buffer.Size(), universe->GetDMX().Size());
  OLA_ASSERT(htp_buffer == universe->GetDMX());

  // now check a client
  DmxBuffer client_buffer;
  client_buffer.SetFromString("255,0,0,255,10");
  m_clock.CurrentTime(&time_stamp);
  ola::DmxSource source(client_buffer, time_stamp, new_priority);
  MockClient input_client;
  input_client.DMXReceived(TEST_UNIVERSE, source);
  universe->SourceClientDataChanged(&input_client);

  DmxBuffer client_htp_merge_result;
  client_htp_merge_result.SetFromString("255,255,0,255,10,7");
  OLA_ASSERT_EQ(new_priority, universe->ActivePriority());
  OLA_ASSERT_EQ(client_htp_merge_result.Size(),
                       universe->GetDMX().Size());
  OLA_ASSERT(client_htp_merge_result == universe->GetDMX());

  // clean up
  universe->RemoveSourceClient(&input_client);
  universe->RemovePort(&port);
  universe->RemovePort(&port2);
  OLA_ASSERT_FALSE(universe->IsActive());
}