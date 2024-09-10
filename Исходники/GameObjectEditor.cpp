void CGameObjectEditor::OnUIAddService()
{
	QListWidgetItem* selectedItem = m_ServiceTypeList->selectedItems().first();
	if( selectedItem )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText( 0, selectedItem->text() );
		item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
		m_ServiceNode->addChild( item );
		m_ObjectTree->setColumnWidth( 0, 150 );
		
		m_ObjectTree->resizeColumnToContents( 0 );
	}
}