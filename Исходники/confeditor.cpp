void AnnoqtConfEditor::slotAddItemAction()
{
  QListWidgetItem* item = new QListWidgetItem("New Type", m_listWidget);
  item->setFlags( item->flags() | Qt::ItemIsEditable );
  item->setCheckState(Qt::Unchecked);
  QColor color = m_colorPicker->color();
  item->setBackgroundColor(color);
  setWindowModified(true);
}