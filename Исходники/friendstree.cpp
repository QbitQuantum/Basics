void FriendsTree::addSelf(const QString &name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setExpanded(true);
    item->setText(0, name);
    item->setTextColor(0, QColor(255, 255, 255, 255));

    m_selfGroupItem = item;
}