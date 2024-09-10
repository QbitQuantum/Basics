/*!
	\details Set the editor values
	\param values The string list to set as values
*/
void StringListEditor::setValues(const QStringList& values) {
	_list->clear();
	foreach ( QString value, values ) {
		QListWidgetItem* it = new QListWidgetItem( value, _list );
		it->setFlags( it->flags() | Qt::ItemIsEditable );
		_list->setCurrentItem( it );
		_list->scrollToItem( it );
	}