void CGUIWindowManager::LoadNotOnDemandWindows()
{
  CSingleLock lock(g_graphicsContext);
  for (const auto& entry : m_mapWindows)
  {
    CGUIWindow *pWindow = entry.second;
    if (pWindow->GetLoadType() == CGUIWindow::LOAD_ON_GUI_INIT)
    {
      pWindow->FreeResources(true);
      pWindow->Initialize();
    }
  }
}