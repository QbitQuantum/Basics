/**
 * Inserts an item with text \a failure to the listview. \a details will be shown
 * when double-clicking on the matching listitem.
 */
void UnitTestDialog::insertError(const QString& failure, const QString& details)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(treeViewFailure);
    item->setText(0,failure);
    item->setTextColor(0, Qt::red);
    item->setData(0, Qt::UserRole, QVariant(details));
}