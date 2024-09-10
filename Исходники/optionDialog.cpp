QTabWidget *OptionDialog::createTabs() {
  tabs = new QTabWidget(this);
  for (int i = 0; i < myFractal->_funcCount; ++i)
    tabs->addTab(new FunctionTab(myFractal->_functions[i]),
                 QString::number(i + 1));
  QToolButton *newTabButton = new QToolButton(tabs);
  newTabButton->setCursor(Qt::ArrowCursor);
  newTabButton->setAutoRaise(true);
  newTabButton->setIcon(QIcon(":/images/plus_16.png"));
  newTabButton->setToolTip(tr("Add function"));
  tabs->setCornerWidget(newTabButton, Qt::TopLeftCorner);

  QToolButton *closeTabButton = new QToolButton(tabs);
  closeTabButton->setCursor(Qt::ArrowCursor);
  closeTabButton->setAutoRaise(true);
  closeTabButton->setIcon(QIcon(":/images/delete_16.png"));
  closeTabButton->setToolTip(tr("Remove function"));
  tabs->setCornerWidget(closeTabButton, Qt::TopRightCorner);

  tabs->repaint();
  connect(closeTabButton, SIGNAL(clicked()), this, SLOT(remFunc()));
  connect(newTabButton, SIGNAL(clicked()), this, SLOT(addFunc()));
  // connect(tabs,SIGNAL(currentChanged(int)),this,SLOT(tabChange(false)));
  return tabs;
}