KonvergoWindow::KonvergoWindow(QWindow* parent) : QQuickWindow(parent), m_debugLayer(false), m_lastScale(1.0)
{
  // NSWindowCollectionBehaviorFullScreenPrimary is only set on OSX if Qt::WindowFullscreenButtonHint is set on the window.
  setFlags(flags() | Qt::WindowFullscreenButtonHint);

  m_infoTimer = new QTimer(this);
  m_infoTimer->setInterval(1000);

  installEventFilter(new EventFilter(this));

  connect(m_infoTimer, &QTimer::timeout, this, &KonvergoWindow::updateDebugInfo);

  InputComponent::Get().registerHostCommand("close", this, "close");
  InputComponent::Get().registerHostCommand("toggleDebug", this, "toggleDebug");
  InputComponent::Get().registerHostCommand("reload", this, "reloadWeb");
  InputComponent::Get().registerHostCommand("fullscreen", this, "toggleFullscreen");

#ifdef TARGET_RPI
  // On RPI, we use dispmanx layering - the video is on a layer below Konvergo,
  // and during playback the Konvergo window is partially transparent. The OSD
  // will be visible on top of the video as part of the Konvergo window.
  setColor(QColor("transparent"));
#else
  setColor(QColor("#111111"));
#endif

  loadGeometry();
  m_lastScale = CalculateScale(size());

  connect(SettingsComponent::Get().getSection(SETTINGS_SECTION_MAIN), &SettingsSection::valuesUpdated,
          this, &KonvergoWindow::updateMainSectionSettings);

  connect(this, &KonvergoWindow::visibilityChanged,
          this, &KonvergoWindow::onVisibilityChanged);

  connect(this, &KonvergoWindow::enableVideoWindowSignal,
          this, &KonvergoWindow::enableVideoWindow, Qt::QueuedConnection);

//  connect(QGuiApplication::desktop(), &QDesktopWidget::screenCountChanged,
//              this, &KonvergoWindow::onScreenCountChanged);

  connect(&PlayerComponent::Get(), &PlayerComponent::windowVisible,
          this, &KonvergoWindow::playerWindowVisible);

  connect(&PlayerComponent::Get(), &PlayerComponent::playbackStarting,
          this, &KonvergoWindow::playerPlaybackStarting);

  // this is using old syntax because ... reasons. QQuickCloseEvent is not public class
  connect(this, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(closingWindow()));

  connect(qApp, &QCoreApplication::aboutToQuit, this, &KonvergoWindow::saveGeometry);

  if (!SystemComponent::Get().isOpenELEC())
  {
    // this is such a hack. But I could not get it to enter into fullscreen
    // mode if I didn't trigger this after a while.
    //
    QTimer::singleShot(500, [=]() {
        updateFullscreenState();
    });
  }
  else
  {
    setWindowState(Qt::WindowFullScreen);
  }

  emit enableVideoWindowSignal();
}