bool UniverseTracker::Run() {
  m_clock.CurrentTime(&m_start_time);
  m_wrapper->GetSelectServer()->Run();
  return true;
}