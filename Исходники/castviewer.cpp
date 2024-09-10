void CastTreeViewer::onCastFolderAdded(const TFilePath &path) {
  QTreeWidgetItem *root = topLevelItem(0)->child(0);
  assert(root->data(1, Qt::DisplayRole).toString() ==
         toQString(getLevelSet()->getDefaultFolder()));
  QString childName     = QString::fromStdWString(path.getWideName());
  QString childPathQstr = QString::fromStdWString(path.getWideString());
  QTreeWidgetItem *childItem =
      new QTreeWidgetItem(root, QStringList(childName) << childPathQstr);
  childItem->setFlags(childItem->flags() | Qt::ItemIsEditable);
  root->addChild(childItem);
  setCurrentItem(childItem);
}