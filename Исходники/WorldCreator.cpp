MapMgr* WorldCreator::GetInstance(uint32 mapid, Object* obj)
{
	// check inactive instances.
	if(obj->GetInstanceID() > 2)
	{
		InactiveInstance * ia = sInstanceSavingManager.GetInactiveInstance(obj->GetInstanceID());
		if(ia != 0)
		{
			//create that inactive instance.
			//extra, it now checks if the instance should expire.
			MapInfo *pMapInfo = WorldMapInfoStorage.LookupEntry(ia->MapId);
			if(pMapInfo)
			{
				if((uint32)time(NULL) > (ia->Creation) + (pMapInfo ? pMapInfo->cooldown : 604800))
				{
					sInstanceSavingManager.RemoveSavedInstance(ia->MapId,ia->InstanceId,true);
					sInstanceSavingManager.RemoveSavedInstance(ia->InstanceId);
				}
				else
				{
					MapMgr * dm = 0;
                    CreateInstance(NULL, NULL, ia->MapId, ia->InstanceId, ia->Creation, &dm, ia->difficulty);
					obj->SetMapId(ia->MapId);
					delete ia;
					return dm;
				}
			}
			else
			{
				MapMgr * dm = 0;
                CreateInstance(NULL, NULL, ia->MapId, ia->InstanceId, ia->Creation, &dm, ia->difficulty);
				obj->SetMapId(ia->MapId);
				delete ia;
				return dm;
			}
		}
	}

	Map* mp = GetMap(mapid);
	if(!mp) return NULL;
	return mp->GetInstance(obj);
}