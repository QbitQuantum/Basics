void Tracker::LogTime() {
  TimeStamp now;
  m_clock.CurrentTime(&now);
  TimeInterval delta = now - m_send_time;
  if (delta > m_max) {
    m_max = delta;
  }
  m_sum += delta.MicroSeconds();

  OLA_INFO << "RPC took " << delta;
  if (FLAGS_count == ++m_count) {
    m_wrapper.GetSelectServer()->Terminate();
  } else {
    SendRequest();
  }
}