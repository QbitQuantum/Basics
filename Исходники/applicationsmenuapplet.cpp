ApplicationsMenuApplet::ApplicationsMenuApplet(void)
  : Applet()
{
  if(QIcon::themeName() == "hicolor" ||
     QIcon::themeName().isEmpty())
  {
    QIcon::setThemeName("nuvola"); // kde
    if(QIcon::fromTheme("start-here").isNull())
      QIcon::setThemeName("gnome"); // gnome
    if(QIcon::fromTheme("start-here").isNull())
      QIcon::setThemeName("hicolor"); // default
  }

  qDebug() << "using theme:" << QIcon::themeName();

//  QIcon::setThemeSearchPaths(CXDGDirs::iconDirectories());
  QPushButton* button = new QPushButton();
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
  button->setMenu(m_menu = new QMenu());
  button->setText("Applications");
  button->setIcon(QIcon::fromTheme("start-here").pixmap(button->height(), button->height()));
  setWidget(button);
}