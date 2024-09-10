void ActivityManager::initExtenderItem(Plasma::ExtenderItem *item) {
  // create the widget
  QGraphicsWidget *widget = new QGraphicsWidget(this);
  // TODO: use the size of the longest activity name
  widget->setPreferredWidth(350);
  // create the layout
  QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(widget);
  layout->setOrientation(Qt::Vertical);
  widget->setLayout(layout);
  // set up the widget
  item->setWidget(widget);
  // create a lock/unlock action
  toggleLockAction = new QAction(item);
  toggleLockAction->setIcon(KIcon("object-locked"));
  toggleLockAction->setEnabled(true);
  toggleLockAction->setVisible(true);
  toggleLockAction->setToolTip(i18n("Activities are unlocked. Click to lock."));
  item->addAction("toggleLock", toggleLockAction);
  connect(toggleLockAction, SIGNAL(triggered()), this, SLOT(toggleLock()));
}