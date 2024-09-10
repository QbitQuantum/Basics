void AMScanThumbnailGridView::onSelectionExtended(int itemIndex)
{
    QModelIndex extendToIndex = model()->index(itemIndex, 0, QModelIndex());
    if(!extendToIndex.isValid())
        return;

    // Get the lowest currently selected row index
    int lowestSelectedRowIndex = 0;
    int rowCount = model()->rowCount();
    bool lowestSelectedRowIndexFound = false;
    while(lowestSelectedRowIndex < rowCount && !lowestSelectedRowIndexFound) {
        if(selectionModel()->isRowSelected(lowestSelectedRowIndex, QModelIndex())) {
            lowestSelectedRowIndexFound = true;
        } else {
            ++lowestSelectedRowIndex;
        }
    }

    if(lowestSelectedRowIndexFound)	{
        QModelIndex lowestSelectedModelIndex =
                model()->index(lowestSelectedRowIndex, 1, QModelIndex());

        if(lowestSelectedModelIndex.isValid()) {

            QItemSelection newSelectedItems;

            if(extendToIndex.row() < lowestSelectedModelIndex.row())
                newSelectedItems.select(extendToIndex, lowestSelectedModelIndex);
            else
                newSelectedItems.select(lowestSelectedModelIndex, extendToIndex);

            selectionModel()->select(newSelectedItems, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        }
    }
}