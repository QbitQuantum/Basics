QListWidgetItem *TodoProjectSettingsWidget::addToExcludedPatternsList(const QString &pattern)
{
    QListWidgetItem *item = new QListWidgetItem(pattern);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    prepareItem(item);
    ui->excludedPatternsList->addItem(item);
    return item;
}