bool StateTracker::CreateInstance()
{
  ASSERT(!s_state_tracker);
  s_state_tracker = std::make_unique<StateTracker>();
  if (!s_state_tracker->Initialize())
  {
    s_state_tracker.reset();
    return false;
  }
  return true;
}