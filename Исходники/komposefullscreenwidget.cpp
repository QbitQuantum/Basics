KomposeFullscreenWidget::KomposeFullscreenWidget( int displayType, KomposeLayout *l )
    : AbstractViewWidget( 0, l )
{
  //   if ( QT_VERSION < 0x030300 )

  /* use showMaximized instead of setWindowState to make it compile on qt 3.1 or whatever */
  //   showMaximized();
  //   KWin::setState( winId(), NET::KeepAbove );

  // Set Desktop background as our background
  setBackgroundMode( Qt::FixedPixmap );
//   setBackgroundPixmap(*(KomposeGlobal::self()->getDesktopBgPixmap()));
  rootpix = new KRootPixmap (this);
  rootpix->start();
  m_menu = KomposeGlobal::self()->getViewMenu();
  initView();

  // Alternate showFullscreen
  setWindowState(windowState() | WindowFullScreen);

  if (KomposeSettings::self()->viewScreen() == -1)
    setGeometry( KGlobalSettings::desktopGeometry( this ) );
  else
  {
    QDesktopWidget deskwidget;
    QRect deskRect = deskwidget.screenGeometry(KomposeSettings::self()->viewScreen());
    setGeometry(deskRect);
    kdDebug() << deskRect << endl;
  }

  if (!isTopLevel())
    QApplication::sendPostedEvents(this, QEvent::ShowFullScreen);
  setActiveWindow();

  KWin::setOnAllDesktops( winId(), true );
}