void GameContext::Release()
  {
  ReleaseContext();
  m_objects.clear();
  m_controllers.clear();
  }