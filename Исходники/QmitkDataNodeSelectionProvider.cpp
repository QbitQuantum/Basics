void QmitkDataNodeSelectionProvider::SetSelection(berry::ISelection::ConstPointer selection,
        QItemSelectionModel::SelectionFlags flags)
{
    if (!qSelectionModel) return;

    mitk::DataNodeSelection::ConstPointer dataNodeSelection = selection.Cast<const mitk::DataNodeSelection>();
    if (dataNodeSelection)
    {
        const QAbstractItemModel* model = qSelectionModel->model();

        QItemSelection newSelection;
        const std::list<mitk::DataNode::Pointer> selectedNodes = dataNodeSelection->GetSelectedDataNodes();
        for (auto i = selectedNodes.begin();
                i != selectedNodes.end(); ++i)
        {
            QModelIndexList matched = model->match(model->index(0, 0), QmitkDataNodeRawPointerRole,
                                                   QVariant::fromValue<mitk::DataNode*>(i->GetPointer()), 1, Qt::MatchRecursive);
            if (!matched.empty())
            {
                newSelection.select(matched.front(), matched.front());
            }
        }
        qSelectionModel->select(newSelection, flags);
    }
    else
    {
        QtSelectionProvider::SetSelection(selection, flags);
    }
}