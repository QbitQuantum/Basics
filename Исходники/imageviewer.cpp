void ImageViewer::contextMenuEvent(QContextMenuEvent *event) {
  if (!m_flipbook) return;

  QAction *action;

  if (m_isColorModel) {
    event->ignore();
    return;
  }

  QMenu *menu = new QMenu(this);

  if (m_flipbook->getPreviewedFx()) {
    if (!(windowState() & Qt::WindowFullScreen)) {
      action = menu->addAction(tr("Clone Preview"));
      action->setShortcut(QKeySequence(
          CommandManager::instance()->getKeyFromId(MI_ClonePreview)));
      connect(action, SIGNAL(triggered()), m_flipbook, SLOT(clonePreview()));
    }

    if (m_flipbook->isFreezed()) {
      action = menu->addAction(tr("Unfreeze Preview"));
      action->setShortcut(QKeySequence(
          CommandManager::instance()->getKeyFromId(MI_FreezePreview)));
      connect(action, SIGNAL(triggered()), m_flipbook, SLOT(unfreezePreview()));
    } else {
      action = menu->addAction(tr("Freeze Preview"));
      action->setShortcut(QKeySequence(
          CommandManager::instance()->getKeyFromId(MI_FreezePreview)));
      connect(action, SIGNAL(triggered()), m_flipbook, SLOT(freezePreview()));
    }

    action = menu->addAction(tr("Regenerate Preview"));
    action->setShortcut(QKeySequence(
        CommandManager::instance()->getKeyFromId(MI_RegeneratePreview)));
    connect(action, SIGNAL(triggered()), m_flipbook, SLOT(regenerate()));

    action = menu->addAction(tr("Regenerate Frame Preview"));
    action->setShortcut(QKeySequence(
        CommandManager::instance()->getKeyFromId(MI_RegenerateFramePr)));
    connect(action, SIGNAL(triggered()), m_flipbook, SLOT(regenerateFrame()));

    menu->addSeparator();
  }

  action = menu->addAction(tr("Load / Append Images"));
  connect(action, SIGNAL(triggered()), m_flipbook, SLOT(loadImages()));

  // history of the loaded paths of flipbook
  action = CommandManager::instance()->getAction(MI_LoadRecentImage);
  menu->addAction(action);
  action->setParent(m_flipbook);

  if (m_flipbook->isSavable()) {
    action = menu->addAction(tr("Save Images"));
    connect(action, SIGNAL(triggered()), m_flipbook, SLOT(saveImages()));
  }
  menu->addSeparator();

  QAction *reset = menu->addAction(tr("Reset View"));
  reset->setShortcut(
      QKeySequence(CommandManager::instance()->getKeyFromId(V_ZoomReset)));
  connect(reset, SIGNAL(triggered()), SLOT(resetView()));

  QAction *fit = menu->addAction(tr("Fit To Window"));
  fit->setShortcut(
      QKeySequence(CommandManager::instance()->getKeyFromId(V_ZoomFit)));
  connect(fit, SIGNAL(triggered()), SLOT(fitView()));

#ifdef _WIN32

  if (ImageUtils::FullScreenWidget *fsWidget =
          dynamic_cast<ImageUtils::FullScreenWidget *>(parentWidget())) {
    bool isFullScreen = (fsWidget->windowState() & Qt::WindowFullScreen) != 0;

    action = menu->addAction(isFullScreen ? tr("Exit Full Screen Mode")
                                          : tr("Full Screen Mode"));

    action->setShortcut(QKeySequence(
        CommandManager::instance()->getKeyFromId(V_ShowHideFullScreen)));
    connect(action, SIGNAL(triggered()), fsWidget, SLOT(toggleFullScreen()));
  }

#endif

  bool addedSep = false;

  if (m_isHistogramEnable &&
      visibleRegion().contains(event->pos() * getDevPixRatio())) {
    menu->addSeparator();
    addedSep = true;
    action   = menu->addAction(tr("Show Histogram"));
    connect(action, SIGNAL(triggered()), SLOT(showHistogram()));
  }

  if (m_visualSettings.m_doCompare) {
    if (!addedSep) menu->addSeparator();
    action = menu->addAction(tr("Swap Compared Images"));
    connect(action, SIGNAL(triggered()), SLOT(swapCompared()));
  }

  menu->exec(event->globalPos());

  action = CommandManager::instance()->getAction(MI_LoadRecentImage);
  action->setParent(0);

  delete menu;
  update();
}