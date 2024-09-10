void DlgEditListParameter::on_add_clicked()
{
  QListWidgetItem *item = new QListWidgetItem();
	item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
	list->addItem(item);
	list->setCurrentItem(item);
	list->editItem(item);
}