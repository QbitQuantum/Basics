bool ContextHelp::eventFilter( QObject * watched, QEvent * e )
{
// 	kDebug() << k_funcinfo << "watched="<<watched<<endl;
	
	if ( (watched != m_pEditor) && (watched != m_pEditor->editorViewport()) )
		return false;
	
	switch ( e->type() )
	{
		case QEvent::DragEnter:
		{
			QDragEnterEvent * dragEnter = static_cast<QDragEnterEvent*>(e);
			
			if ( !QString( dragEnter->format() ).startsWith("ktechlab/") )
				break;
			
			dragEnter->acceptAction();
			return true;
		}
			
		case QEvent::Drop:
		{
			QDropEvent * dropEvent = static_cast<QDropEvent*>(e);
			
			if ( !QString( dropEvent->format() ).startsWith("ktechlab/") )
				break;
			
			dropEvent->accept();
			
			QString type;
			QDataStream stream( dropEvent->encodedData( dropEvent->format() ) /*, IO_ReadOnly */ );
			stream >> type;
			
			LibraryItem * li = itemLibrary()->libraryItem( type );
			if ( !li )
				return true;
			
			m_pEditor->insertURL( "ktechlab-help:///" + type, li->name() );
			return true;
		}
			
		default:
			break;
	}
	
	return false;
}