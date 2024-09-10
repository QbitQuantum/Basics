void TreeWidgetEditor::on_newColumnButton_clicked()
{
    m_updating = true;
    QListWidgetItem *currentColumn = ui.listWidget->currentItem();
    int idx = ui.listWidget->count();
    if (currentColumn)
        idx = ui.listWidget->currentRow() + 1;

    QString newColumnString = tr("New Column");

    int columnCount = ui.treeWidget->columnCount();
    ui.treeWidget->setColumnCount(columnCount + 1);

    ui.treeWidget->headerItem()->setText(columnCount, newColumnString);
    moveColumnsLeft(idx, columnCount);

    QListWidgetItem *item = new QListWidgetItem();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setText(newColumnString);
    ui.listWidget->insertItem(idx, item);
    ui.listWidget->setCurrentItem(item);

    ui.treeWidget->setCurrentItem(ui.treeWidget->currentItem(), ui.listWidget->currentRow());

    m_updating = false;
    updateEditor();

    ui.listWidget->editItem(item);
}