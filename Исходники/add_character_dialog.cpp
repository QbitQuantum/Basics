void AddCharacterDialog::addState(const QString& state, const QString& imagePath)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(mUi.statusTreeWidget);
    item->setText(0, state);
    item->setIcon(0, QIcon(imagePath));
    item->setData(0, Qt::UserRole, imagePath);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    QPushButton *removeBtn = new QPushButton(QIcon(":/media/delete.png"), "", mUi.statusTreeWidget);
    removeBtn->setFlat(true);
    connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeState()));
    mUi.statusTreeWidget->setItemWidget(item, 1, removeBtn);
    for(int i=0; i < mUi.statusTreeWidget->columnCount(); i++)
        mUi.statusTreeWidget->resizeColumnToContents(i);
}