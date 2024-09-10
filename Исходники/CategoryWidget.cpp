CategoryWidget::CategoryWidget(QWidget *parent) : QTreeWidget(parent), d(new CategoryWidgetPrivate()) {
  connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(toggleItemState(QModelIndex)));
  connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
  // get elements from the element manager
  QStringList categories = ElementManager::instance()->categories();
  // create the category nodes
  QHash<QString, QTreeWidgetItem *> categoryNodes;
  foreach(QString category, categories) {
    QTreeWidgetItem *parent = 0;
    int numSections = category.count("/") + 1;
    for (int i = 0; i < numSections; ++i) {
      QString path = category.section("/", 0, i, QString::SectionSkipEmpty);
      if (!categoryNodes.contains(path)) {
        QTreeWidgetItem *node = new QTreeWidgetItem();
        if (parent == 0)
          this->addTopLevelItem(node);
        else
          parent->addChild(node);
        QString name = category.section("/", i, i, QString::SectionSkipEmpty);
        node->setText(0, qApp->translate("Categories", name.toUtf8()));
        node->setData(0, Qt::UserRole, name);
        node->setData(1, Qt::UserRole, path);
        // use bigger fonts for items at higher levels
        QFont font = node->font(0);
        font.setPointSize(font.pointSize() + 2 - qMin(i, 3));
        node->setFont(0, font);
        if (i >= 3)
          node->setTextColor(0, QColor(96, 96, 96));
        categoryNodes[path] = node;
      }
      parent = categoryNodes[path];
    }
  }