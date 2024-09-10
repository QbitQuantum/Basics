/*
 * Test the time based checks
 */
void DmxSourceTest::testIsActive() {
  DmxBuffer buffer("123456789");
  TimeStamp timestamp;
  m_clock.CurrentTime(&timestamp);

  DmxSource source(buffer, timestamp, 100);
  OLA_ASSERT(source.IsSet());

  OLA_ASSERT(source.IsActive(timestamp));
  TimeInterval interval(1000000);
  TimeStamp later = timestamp + interval;
  OLA_ASSERT(source.IsActive(later));

  later = timestamp + TimeInterval(2500000);
  OLA_ASSERT_FALSE(source.IsActive(later));
}