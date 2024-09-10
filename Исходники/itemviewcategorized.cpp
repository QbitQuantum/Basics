void ItemViewCategorized::setSelectedIndexes(const QList<QModelIndex>& indexes)
{
    if (selectedIndexes() == indexes)
    {
        return;
    }

    QItemSelection mySelection;

    foreach(const QModelIndex& index, indexes)
    {
        mySelection.select(index, index);
    }