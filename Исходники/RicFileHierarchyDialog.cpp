//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void RicFileHierarchyDialog::appendToFileList(const QString& fileName)
{
    QString itemText = fileName;
    itemText.remove(0, rootDir().size());
    QListWidgetItem* item = new QListWidgetItem(itemText, m_fileList);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
}