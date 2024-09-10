// new items go on top
TQString KonqSidebarHistoryGroupItem::key( int column, bool ascending ) const
{
    if ( !m_lastVisited.isValid() || MYMODULE->sortsByName() )
	return KonqSidebarTreeItem::key( column, ascending );

    TQString tmp;
    tmp.sprintf( "%08x", m_lastVisited.secsTo( MYMODULE->currentTime() ));
    return tmp;
}