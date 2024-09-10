void SetObjectLPoint (ObjectRecHdl ObjectHdl, LongPoint *objectLPointPtr)
{
	OSType	thisObjectType;
		
	(**ObjectHdl).objectLPoint = *objectLPointPtr;
	GetObjectType (ObjectHdl, &thisObjectType);
	if (thisObjectType == kSymbolType)
	{
		LongRect	thisObjectLRect;
		
		SetLRect (&thisObjectLRect, objectLPointPtr -> h, objectLPointPtr -> v,
									objectLPointPtr -> h, objectLPointPtr -> v);
									
		SetObjectLRect (ObjectHdl, &thisObjectLRect);
	}
	
	return;
}