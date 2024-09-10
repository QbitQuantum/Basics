void QtShaderWindow::addSourcesListItem(const QString& title, bool isChecked, bool isBuiltIn)
{
    QListWidgetItem* item = new QListWidgetItem(title, m_sourcesListWidget);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(isChecked ? Qt::Checked : Qt::Unchecked);
    item->setData(SOURCES_LIST_BUILT_IN_ROLE, isBuiltIn);
    m_sourcesListWidget->addItem(item);
}