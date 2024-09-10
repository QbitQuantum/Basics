void FolderManager::runCommand(const QString &name)
{
  qDebug() << "FolderManager::runCommand()" << name;

  FolderView *sourceView = currentFolderView(m_active_side);
  FolderView *targetView = currentFolderView((m_active_side == LeftSide) ? RightSide : LeftSide);

  if (! sourceView) {
    qDebug() << "no source view";
    return;
  }

  if (name == "parent") {
    QDir dir(sourceView->fileSystemModel()->rootPath());
    dir.cdUp();
    sourceView->navigateToPath(dir.absolutePath());
  }
  else if (name == "select-all") {
    sourceView->selectAll();
  }
  else if (name == "select-none") {
    sourceView->clearSelection();
  }
  else if (name == "invert-selection") {
    QItemSelectionModel *selectionModel  = sourceView->selectionModel();
    selectionModel->select(selectionModel->selection(), QItemSelectionModel::Toggle);

#if 0
    QAbstractItemModel  *model        = sourceView->model();
    QModelIndex          topLeft      = model->index(0, 0);
    QModelIndex          bottomRight  = model->index(model->rowCount(parent)-1,
                                                     model->columnCount(parent)-1);
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Toggle);
#endif
  }
}