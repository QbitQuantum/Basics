void ComboViewerPanel::showEvent(QShowEvent *) {
  TApp *app                    = TApp::instance();
  TFrameHandle *frameHandle    = app->getCurrentFrame();
  TSceneHandle *sceneHandle    = app->getCurrentScene();
  TXshLevelHandle *levelHandle = app->getCurrentLevel();
  TObjectHandle *objectHandle  = app->getCurrentObject();
  TXsheetHandle *xshHandle     = app->getCurrentXsheet();

  bool ret = true;

  /*!
  onSceneChanged(): called when the scene changed
  - set new scene's FPS
  - update the range of frame slider with a new framehandle
  - set the marker
  - update key frames
  */
  ret =
      connect(xshHandle, SIGNAL(xsheetChanged()), this, SLOT(onSceneChanged()));
  ret = ret && connect(sceneHandle, SIGNAL(sceneSwitched()), this,
                       SLOT(onSceneChanged()));
  ret = ret && connect(sceneHandle, SIGNAL(sceneChanged()), this,
                       SLOT(onSceneChanged()));

  /*!
  changeWindowTitle(): called when the scene / level / frame is changed
  - chenge the title text
  */
  ret = ret && connect(sceneHandle, SIGNAL(nameSceneChanged()), this,
                       SLOT(changeWindowTitle()));
  ret = ret && connect(levelHandle, SIGNAL(xshLevelChanged()), this,
                       SLOT(changeWindowTitle()));
  ret = ret && connect(frameHandle, SIGNAL(frameSwitched()), this,
                       SLOT(changeWindowTitle()));
  // onXshLevelSwitched(TXshLevel*)： changeWindowTitle() + updateFrameRange()
  ret = ret && connect(levelHandle, SIGNAL(xshLevelSwitched(TXshLevel *)), this,
                       SLOT(onXshLevelSwitched(TXshLevel *)));

  // updateFrameRange(): update the frame slider's range
  ret = ret && connect(levelHandle, SIGNAL(xshLevelChanged()), this,
                       SLOT(updateFrameRange()));

  // onFrameTypeChanged(): reset the marker positions in the flip console
  ret = ret && connect(frameHandle, SIGNAL(frameTypeChanged()), this,
                       SLOT(onFrameTypeChanged()));

  // onFrameChanged(): update the flipconsole according to the current frame
  ret = ret && connect(frameHandle, SIGNAL(frameSwitched()), this,
                       SLOT(onFrameChanged()));

  ret = ret && connect(app->getCurrentTool(), SIGNAL(toolSwitched()),
                       m_sceneViewer, SLOT(onToolSwitched()));
  ret = ret && connect(sceneHandle, SIGNAL(preferenceChanged()), m_flipConsole,
                       SLOT(onPreferenceChanged()));
  m_flipConsole->onPreferenceChanged();

  assert(ret);

  m_flipConsole->setActive(true);

  // refresh
  onSceneChanged();
  changeWindowTitle();
}