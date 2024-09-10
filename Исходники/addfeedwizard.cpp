QWizardPage *AddFeedWizard::createNameFeedPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle(tr("Create New Feed"));
  page->setFinalPage(false);

  nameFeedEdit_ = new LineEdit(this);

  foldersTree_ = new QTreeWidget(this);
  foldersTree_->setObjectName("foldersTree_");
  foldersTree_->setColumnCount(2);
  foldersTree_->setColumnHidden(1, true);
  foldersTree_->header()->hide();

  QStringList treeItem;
  treeItem << tr("Feeds") << "Id";
  foldersTree_->setHeaderLabels(treeItem);

  treeItem.clear();
  treeItem << tr("All Feeds") << "0";
  QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem(treeItem);
  treeWidgetItem->setIcon(0, QIcon(":/images/folder"));
  foldersTree_->addTopLevelItem(treeWidgetItem);
  foldersTree_->setCurrentItem(treeWidgetItem);

  QSqlQuery q;
  QQueue<int> parentIds;
  parentIds.enqueue(0);
  while (!parentIds.empty()) {
    int parentId = parentIds.dequeue();
    QString qStr = QString("SELECT text, id FROM feeds WHERE parentId='%1' AND (xmlUrl='' OR xmlUrl IS NULL)").
        arg(parentId);
    q.exec(qStr);
    while (q.next()) {
      QString folderText = q.value(0).toString();
      QString folderId = q.value(1).toString();

      QStringList treeItem;
      treeItem << folderText << folderId;
      QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem(treeItem);

      treeWidgetItem->setIcon(0, QIcon(":/images/folder"));

      QList<QTreeWidgetItem *> treeItems =
            foldersTree_->findItems(QString::number(parentId),
                                                       Qt::MatchFixedString | Qt::MatchRecursive,
                                                       1);
      treeItems.at(0)->addChild(treeWidgetItem);
      if (folderId.toInt() == curFolderId_)
        foldersTree_->setCurrentItem(treeWidgetItem);
      parentIds.enqueue(folderId.toInt());
    }
  }

  foldersTree_->expandAll();
  foldersTree_->sortByColumn(0, Qt::AscendingOrder);

  ToolButton *newFolderButton = new ToolButton(this);
  newFolderButton->setIcon(QIcon(":/images/addT"));
  newFolderButton->setToolTip(tr("New Folder..."));
  newFolderButton->setAutoRaise(true);

  QHBoxLayout *newFolderLayout = new QHBoxLayout;
  newFolderLayout->setMargin(0);
  newFolderLayout->addWidget(newFolderButton);
  newFolderLayout->addStretch();
  QVBoxLayout *newFolderVLayout = new QVBoxLayout;
  newFolderVLayout->setMargin(2);
  newFolderVLayout->addStretch();
  newFolderVLayout->addLayout(newFolderLayout);

  foldersTree_->setLayout(newFolderVLayout);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(new QLabel(tr("Displayed name:")));
  layout->addWidget(nameFeedEdit_);
  layout->addWidget(new QLabel(tr("Location:")));
  layout->addWidget(foldersTree_);
  page->setLayout(layout);

  connect(nameFeedEdit_, SIGNAL(textChanged(const QString&)),
          this, SLOT(nameFeedEditChanged(const QString&)));
  connect(newFolderButton, SIGNAL(clicked()),
          this, SLOT(newFolder()));

  return page;
}