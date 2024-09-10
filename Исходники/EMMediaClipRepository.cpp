int64 EMMediaClipRepository::CountClipsForTrack(const EMMediaTrack* p_opTrack, EMMediaType p_eSpecType)
{
	int64 vCount = 0;
	LockContainer();
	try
	{
		Rewind();
		while(Current() != NULL)
		{
			if(Current() -> GetTrack() -> GetID() == p_opTrack -> GetID() &&
				! Current() -> IsObjectDeleted() && (p_eSpecType & Current() -> GetType()) != 0)
				vCount++;

			if(Current() -> GetTrack() == NULL)
				EMDebugger("ERROR! NULL as track owner!");
			Next();
		}
	}
	catch(...)
	{
		EMDebugger("ERROR! Exception in EMMediaClipRepository::CountClipsForTrack");
	}
	UnlockContainer();
	return vCount;
}