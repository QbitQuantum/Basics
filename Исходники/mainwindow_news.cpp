/*
 * This is the TextBrowser News tab, which shows the latest news from Distro news feed
 */
void MainWindow::initTabNews()
{
  QString aux(StrConstants::getTabNewsName());
  QWidget *tabNews = new QWidget();
  QGridLayout *gridLayoutX = new QGridLayout(tabNews);
  gridLayoutX->setSpacing(0);
  gridLayoutX->setMargin(0);

  QTextBrowser *text = new QTextBrowser(tabNews);
  text->setObjectName("textBrowser");
  text->setReadOnly(true);
  text->setFrameShape(QFrame::NoFrame);
  text->setFrameShadow(QFrame::Plain);
  text->setOpenExternalLinks(true);
  gridLayoutX->addWidget(text, 0, 0, 1, 1);
  text->show();

#if QT_VERSION > 0x050000
  int tindex = ui->twProperties->insertTab(ctn_TABINDEX_NEWS, tabNews, QApplication::translate (
      "MainWindow", aux.toUtf8(), 0/*, QApplication::UnicodeUTF8*/ ) );
  ui->twProperties->setTabText(ui->twProperties->indexOf(tabNews), QApplication::translate(
      "MainWindow", aux.toUtf8(), 0/*, QApplication::UnicodeUTF8*/));
#else
  int tindex = ui->twProperties->insertTab(ctn_TABINDEX_NEWS, tabNews, QApplication::translate (
      "MainWindow", aux.toUtf8(), 0, QApplication::UnicodeUTF8 ) );
  ui->twProperties->setTabText(ui->twProperties->indexOf(tabNews), QApplication::translate(
      "MainWindow", aux.toUtf8(), 0, QApplication::UnicodeUTF8));
#endif

  SearchBar *searchBar = new SearchBar(this);

  connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(searchBarTextChangedInTextBrowser(QString)));
  connect(searchBar, SIGNAL(closed()), this, SLOT(searchBarClosedInTextBrowser()));
  connect(searchBar, SIGNAL(findNext()), this, SLOT(searchBarFindNextInTextBrowser()));
  connect(searchBar, SIGNAL(findPrevious()), this, SLOT(searchBarFindPreviousInTextBrowser()));

  gridLayoutX->addWidget(searchBar, 1, 0, 1, 1);

  connect(text, SIGNAL(sourceChanged(QUrl)), this, SLOT(onTabNewsSourceChanged(QUrl)));

  text->show();

  ui->twProperties->setCurrentIndex(tindex);
  text->setFocus();
}