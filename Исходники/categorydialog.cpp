void CategoryDialog::setParentCategory(int parent)
{
    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndex index = model->indexById(parent);
    selection->select(model->index(index.row(),0,index.parent()),QItemSelectionModel::Select);
    while(index != model->index(0,0) && index != QModelIndex())
    {
        ui->treeView->setExpanded(index,true);
        index = index.parent();
    }
}