void AnimationView::setSelected(const QList< int >& selected)
{
	QItemSelection selection;
	foreach( int row, selected )
	{
		QModelIndex index = model()->index( row, 0 );
		selection.select( index, index );
	}