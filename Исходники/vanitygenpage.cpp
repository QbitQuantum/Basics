void VanityGenPage::deleteRows()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();//selectedIndexes();//;
    QList<int> sortIndex;
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        sortIndex.append(index.row());
    }
    qSort(sortIndex);

    for(int i=sortIndex.length()-1; i>=0 ; i--)
    {
        VanityGenWorkList.removeAt(sortIndex[i]);
    }

    rebuildTableView();
    updateUi();

    VanityGenRunning = false;
    saveFile();

}