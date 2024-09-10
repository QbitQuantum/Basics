// updateData
// update data
void CWayPoint::updateData( CSerializable* pObj )
{
	pObj->nextRecord();
	
	CZone* pZone = (CZone*) getParent();

	// next waypoint
	long id = pObj->readLong();	
	CGameObject *p = pZone->searchObject( id );

	if ( id != -1 && p )
	{		
		if ( p && p->getObjectType() == CGameObject::WaypointObject )
		{
			((CWayPoint*)p)->setBack( this );
			setNext( (CWayPoint*)p );
		}
	}
	else
	{
		if ( m_next )
			m_next->setBack( NULL );
		setNext(NULL);
	}

	// prev waypoint
	id = pObj->readLong();
	p = pZone->searchObject( id );

	if ( id != -1 && p )
	{
		if ( p && p->getObjectType() == CGameObject::WaypointObject )
		{
			((CWayPoint*)p)->setNext( this );
			setBack( (CWayPoint*)p );
		}
	}
	else
	{
		if ( m_back )
			m_back->setNext( NULL );
		setBack(NULL);
	}

	// wait time
	m_timeWait = pObj->readLong();

	CGameObject::updateData( pObj );
}