void FunctionViewerPanel::attachHandles() {
  TApp *app = TApp::instance();

  m_functionViewer->setXsheetHandle(app->getCurrentXsheet());
  m_functionViewer->setFrameHandle(app->getCurrentFrame());
  m_functionViewer->setObjectHandle(app->getCurrentObject());
  m_functionViewer->setFxHandle(app->getCurrentFx());
  m_functionViewer->setColumnHandle(app->getCurrentColumn());
  m_functionViewer->setSceneHandle(app->getCurrentScene());
}