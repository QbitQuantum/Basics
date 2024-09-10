// Check if any managed widgets are selected. If so, iterate over
// selection and deselect all unmanaged objects
bool ObjectInspector::ObjectInspectorPrivate::checkManagedWidgetSelection(const QModelIndexList &rowSelection)
{
    bool isManagedWidgetSelection = false;
    QItemSelectionModel *selectionModel = m_treeView->selectionModel();
    const QModelIndexList::const_iterator cscend = rowSelection.constEnd();
    for (QModelIndexList::const_iterator it = rowSelection.constBegin(); it != cscend; ++it) {
        QObject *object = m_model->objectAt(*it);
        if (selectionType(m_formWindow, object) == ManagedWidgetSelection) {
            isManagedWidgetSelection = true;
            break;
        }
    }

    if (!isManagedWidgetSelection)
        return false;
    // Need to unselect unmanaged ones
    const bool blocked = selectionModel->blockSignals(true);
    for (QModelIndexList::const_iterator it = rowSelection.constBegin(); it != cscend; ++it) {
        QObject *object = m_model->objectAt(*it);
        if (selectionType(m_formWindow, object) != ManagedWidgetSelection)
            selectionModel->select(*it, QItemSelectionModel::Deselect|QItemSelectionModel::Rows);
    }
    selectionModel->blockSignals(blocked);
    return true;
}