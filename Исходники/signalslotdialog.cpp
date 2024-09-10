static  QStandardItem *createEditableItem(const QString &text)
{
    QStandardItem *rc = new QStandardItem(text);
    rc->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
    return rc;
}