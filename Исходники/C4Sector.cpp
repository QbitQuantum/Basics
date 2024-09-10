void C4LSectors::Remove(C4Object *pObj)
{
	assert(Sectors); assert(pObj);
	// Remove from owning sector
	C4LSector *pSct = SectorAt(pObj->old_x, pObj->old_y);
	if (!pSct->Objects.Remove(pObj))
	{
#ifdef _DEBUG
		LogF("WARNING: Object %d of type %s deleted but not found in pos sector list!", pObj->Number, pObj->id.ToString());
#endif
		// if it was not found in owning sector, it must be somewhere else. yeah...
		bool fFound = false;
		for (pSct = pObj->Area.First(); pSct; pSct = pObj->Area.Next(pSct))
			if (pSct->Objects.Remove(pObj)) { fFound=true; break; }
		// yukh, somewhere else entirely...
		if (!fFound)
		{
			fFound = !!SectorOut.Objects.Remove(pObj);
			if (!fFound)
			{
				pSct = Sectors;
				for (int cnt=0; cnt<Size; cnt++, pSct++)
					if (pSct->Objects.Remove(pObj)) { fFound=true; break; }
			}
			assert(fFound);
		}
	}
	// Remove from all sectors in shape area
	for (pSct = pObj->Area.First(); pSct; pSct = pObj->Area.Next(pSct))
		pSct->ObjectShapes.Remove(pObj);
	if (Config.General.DebugRec)
		pObj->Area.DebugRec(pObj, 'R');
}