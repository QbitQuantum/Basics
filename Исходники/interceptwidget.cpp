void InterceptWidget::updateColumns()
{
    QStringList columnList = model->getColumnNames();
    QStandardItemModel *columnModel = new(std::nothrow) QStandardItemModel(columnList.size(), 1);
    if (columnModel == NULL ) {
        qFatal("Cannot allocate memory for QStandardItemModel X{");
        return;
    }

    for (int i = 0; i < columnList.size(); ++i)
    {
        QStandardItem* item = NULL;
        item = new(std::nothrow) QStandardItem(columnList.at(i));
        if (item != NULL) {
            item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            item->setData( (packetsTable->isColumnHidden(i) ? Qt::Unchecked : Qt::Checked), Qt::CheckStateRole);
            columnModel->setItem(i, 0, item);
        } else {
          qFatal("Cannot allocate memory for QStandardItem 2 X{");
        }
    }
    connect(columnModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(onColumnChanged(QModelIndex,QModelIndex)));
    ui->columnListWidget->setModel(columnModel);
}