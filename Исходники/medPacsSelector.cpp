void medPacsSelector::fillWidget( QList<QVariant> nodes )
{
    d->selectionList->clear();
    foreach(QVariant node, nodes)
    {
        QListWidgetItem* myItem = new QListWidgetItem(node.toStringList().at(0),d->selectionList);
        myItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        myItem->setCheckState(Qt::Checked);
    }