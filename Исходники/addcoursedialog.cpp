void AddCourseDialog::addSale()
{
	QListWidgetItem *item = new QListWidgetItem( listWidget );
	item->setText( "0.00" );
	item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable );

	listWidget->setCurrentItem( item );
	listWidget->editItem( item );
}