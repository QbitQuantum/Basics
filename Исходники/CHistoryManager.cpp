bool CHistoryManager::doCreate(	SAction* action, bool redo )
{
	IDoc *pDoc = getIView()->getDocument();

	CSerializable *pObject = &action->object1;
	pObject->setCursorRecord(0);
		
	if ( redo == false )
	{
		SSerializableRec *pObjectID	= pObject->getProperty("objectID");

		if ( pObjectID == NULL )
			return false;

		long objID = -1;
		sscanf( pObjectID->data, "%ld", &objID );	

		CGameObject* pObj =	pDoc->searchObject( objID );
		if ( pObj == NULL )
			return false;

		CZone *pZone = (CZone*) pObj->getParent();
		pZone->removeObject( pObj );
	}
	else
	{
		SSerializableRec *pParentID			= pObject->getProperty("parentID");
		SSerializableRec *pObjectTemplate	= pObject->getProperty("objectTemplate");
		SSerializableRec *pObjectType		= pObject->getProperty("objectType");

		if ( pParentID == NULL )
			return false;

		long parentID = -1;
		sscanf( pParentID->data, "%ld", &parentID );

		CGameObject* pParent =	pDoc->searchObject( parentID );
		if ( pParent == NULL )
			return false;

		if ( pParent->getObjectType() != CGameObject::ZoneObject )
			return false;

		CZone *pZone = (CZone*) pParent;
		wchar_t objTemplate[1024];
		uiString::convertUTF8ToUnicode(pObjectTemplate->data, objTemplate);

		CGameObject *pObj = NULL;

		if ( strcmp( pObjectType->data, strOfObjType( CGameObject::GameObject ) ) == 0 )
			pObj = pZone->createObject( objTemplate );			
		else if ( strcmp( pObjectType->data, strOfObjType( CGameObject::CameraObject ) ) == 0 )		
			pObj = pZone->createCamera();			
		else if ( strcmp( pObjectType->data, strOfObjType( CGameObject::WaypointObject ) ) == 0 )
			pObj = pZone->createWaypoint();		
		else if ( strcmp( pObjectType->data, strOfObjType( CGameObject::TriggerObject ) ) == 0 )
			pObj = pZone->createTrigger();
		else if ( strcmp( pObjectType->data, strOfObjType( CGameObject::LightObject ) ) == 0 )
			pObj = pZone->createLight();

		if ( pObj )
		{
			pObj->updateData( pObject );
			pZone->setSortObject( true );
		}
	}

	return true;	
}