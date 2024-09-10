/*
 * Check the UpdateDmxData method works
 */
void OlaServerServiceImplTest::testUpdateDmxData() {
  UniverseStore store(NULL, NULL);
  ola::TimeStamp time1;
  ola::Client client(NULL);
  ola::Client client2(NULL);
  OlaServerServiceImpl impl(&store,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            &time1,
                            m_uid);
  OlaClientService service1(&client, &impl);
  OlaClientService service2(&client2, &impl);

  GenericMissingUniverseCheck<UpdateDmxDataCheck, ola::proto::Ack>
    missing_universe_check;
  GenericAckCheck<UpdateDmxDataCheck> ack_check;
  unsigned int universe_id = 0;
  DmxBuffer dmx_data("this is a test");
  DmxBuffer dmx_data2("different data hmm");

  // Update a universe that doesn't exist
  m_clock.CurrentTime(&time1);
  CallUpdateDmxData(&service1, universe_id, dmx_data, missing_universe_check);
  Universe *universe = store.GetUniverse(universe_id);
  OLA_ASSERT_FALSE(universe);

  // Update a universe that exists
  m_clock.CurrentTime(&time1);
  universe = store.GetUniverseOrCreate(universe_id);
  CallUpdateDmxData(&service1, universe_id, dmx_data, ack_check);
  OLA_ASSERT(dmx_data == universe->GetDMX());

  // Update a second client with an older timestamp
  // make sure we're in ltp mode
  OLA_ASSERT_EQ(universe->MergeMode(), Universe::MERGE_LTP);
  time1 = time1 - ola::TimeInterval(1000000);
  CallUpdateDmxData(&service2, universe_id, dmx_data2, ack_check);
  OLA_ASSERT_EQ(dmx_data.Size(), universe->GetDMX().Size());
  // Should continue to hold the old data
  OLA_ASSERT(dmx_data == universe->GetDMX());

  // Now send a new update
  m_clock.CurrentTime(&time1);
  CallUpdateDmxData(&service2, universe_id, dmx_data2, ack_check);
  OLA_ASSERT(dmx_data2 == universe->GetDMX());
}