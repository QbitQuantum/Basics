void ProjectCreatePopup::showEvent(QShowEvent *) {
  int i;
  QString fldName;
  for (i = 0; i < m_folderFlds.size(); i++) {
    fldName = QString::fromStdString(m_folderFlds[i].first);
    m_folderFlds[i].second->setPath(fldName);
  }
  for (i = 0; i < m_useScenePathCbs.size(); i++) {
    CheckBox *cb                = m_useScenePathCbs[i].second;
    bool signalesAlreadyBlocked = cb->blockSignals(true);
    cb->setChecked(false);
    cb->blockSignals(signalesAlreadyBlocked);
  }

  m_nameFld->setText("");
  // Must refresh the tree.
  DvDirModelNode *rootNode = m_model->getNode(QModelIndex());
  QModelIndex index        = m_model->getIndexByNode(rootNode);
  m_model->refreshFolderChild(index);
  // Select the first Item in the treeView
  QItemSelectionModel *selection = new QItemSelectionModel(m_model);
  index                          = m_model->index(0, 0, QModelIndex());
  selection->select(index, QItemSelectionModel::Select);
  m_treeView->setSelectionModel(selection);
}