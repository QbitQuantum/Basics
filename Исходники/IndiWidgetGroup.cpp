void IndiWidgetGroup::init()
{
  // Create the context menu actions
  QMenu* menu = new QMenu(this);
  connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(changeWindowCount(QAction*)));
  QAction* act;
  act = menu->addAction("+1");
  act->setData(1);
  act = menu->addAction("+2");
  act->setData(2);
  act = menu->addAction("+3");
  act->setData(3);
  act = new QAction(tr("More Indicators..."), this);
  act->setMenu(menu);
  addAction(act);

  menu = new QMenu(this);
  connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(changeWindowCount(QAction*)));
  act = menu->addAction("-1");
  act->setData(-1);
  act = menu->addAction("-2");
  act->setData(-2);
  act = menu->addAction("-3");
  act->setData(-3);
  act = new QAction(tr("Less Indicators..."), this);
  act->setMenu(menu);
  addAction(act);

  mFullIndiSetsPath = mRcFile->getPath("IndiSetsPath");
  mSplitter = new QSplitter(Qt::Vertical);

  QVBoxLayout* lay = new QVBoxLayout;
  lay->addWidget(mSplitter);

  setLayout(lay);
}