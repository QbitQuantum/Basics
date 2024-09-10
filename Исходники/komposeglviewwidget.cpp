KomposeGLViewWidget::KomposeGLViewWidget( int displayType , KomposeLayout *l )
 : AbstractViewWidget( 0, l, 0 )
{
  m_menu = KomposeGlobal::self()->getViewMenu();

  m_glWidget = new KomposeGLWidget(this,displayType,l);

  QDesktopWidget deskwidget;
  if (KomposeSettings::self()->viewScreen() == -1)
  {
    setGeometry( deskwidget.availableGeometry( this ) );
  } else {
    QRect deskRect = deskwidget.availableGeometry(KomposeSettings::self()->viewScreen());
    setGeometry(deskRect);
  }

  setActiveWindow();
  // Qt::WStyle_Customize | Qt::WStyle_NoBorder | Qt::WStyle_Tool | Qt::WPaintUnclipped | Qt::WNoAutoErase
  KWin::setType(winId(), NET::Dock);
  KWin::setOnAllDesktops( winId(), true );
}