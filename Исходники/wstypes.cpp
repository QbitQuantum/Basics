TBool RWsRegion::Contains(const RWsRegion& aRegion)
	{
	RWsRegion region(aRegion);

	if (iError && aRegion.CheckError())
		return ETrue;
	region.SubRegion(*this);
	return region.IsEmpty();
	}