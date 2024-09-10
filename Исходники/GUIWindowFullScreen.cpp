void CGUIWindowFullScreen::PreloadDialog(unsigned int windowID)
{
  CGUIWindow *pWindow = m_gWindowManager.GetWindow(windowID);
  if (pWindow)
  {
    pWindow->Initialize();
    pWindow->DynamicResourceAlloc(false);
    pWindow->AllocResources(false);
  }
}