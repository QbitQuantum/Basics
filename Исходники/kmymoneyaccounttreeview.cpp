void KMyMoneyAccountTreeView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  QTreeView::selectionChanged(selected, deselected);
  if (!selected.empty()) {
    QModelIndexList indexes = selected.front().indexes();
    if (!indexes.empty()) {
      QVariant data = model()->data(model()->index(indexes.front().row(), AccountsModel::Account, indexes.front().parent()), AccountsModel::AccountRole);
      if (data.isValid()) {
        if (data.canConvert<MyMoneyAccount>()) {
          emit selectObject(data.value<MyMoneyAccount>());
        }
        if (data.canConvert<MyMoneyInstitution>()) {
          emit selectObject(data.value<MyMoneyInstitution>());
        }
        // an object was successfully selected
        return;
      }
    }
  }
  // since no object was selected reset the object selection
  emit selectObject(MyMoneyAccount());
  emit selectObject(MyMoneyInstitution());
}