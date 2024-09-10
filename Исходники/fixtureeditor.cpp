void QLCFixtureEditor::updateChannelItem(const QLCChannel* channel, QTreeWidgetItem* item)
{
    QString str;

    Q_ASSERT(channel != NULL);
    Q_ASSERT(item != NULL);

    item->setText(CH_COL_NAME, channel->name());
    item->setIcon(CH_COL_NAME, channel->getIcon());
    item->setText(CH_COL_GRP, QLCChannel::groupToString(channel->group()));
    item->setData(CH_COL_NAME, PROP_PTR, (qulonglong) channel);

    /* Destroy the existing list of children */
    QList <QTreeWidgetItem*> children(item->takeChildren());
    foreach (QTreeWidgetItem* child, children)
    delete child;

    /* Put all capabilities as non-selectable sub items */
    QListIterator <QLCCapability*> capit(channel->capabilities());
    while (capit.hasNext() == true)
    {
        QLCCapability* cap = capit.next();
        Q_ASSERT(cap != NULL);

        QTreeWidgetItem* capitem = new QTreeWidgetItem(item);
        capitem->setText(CH_COL_NAME,
                         QString("[%1-%2]: %3").arg(cap->min())
                         .arg(cap->max()).arg(cap->name()));
        capitem->setFlags(0); /* No selection etc. */
    }
}