bool EMMediaTransitionTrackRepository::SaveData(EMProjectDataSaver* p_opSaver)
{
	p_opSaver -> SaveString("EMMediaTransitionTrackRepository - Begin");
	
	LockContainer();
	uint32 vCount = 0;
	Rewind();
	while(Current() != NULL)
	{
		if(! Current() -> IsObjectDeleted())
			vCount++;
		Next();
	}
	p_opSaver -> SaveUInt32(vCount);

	Rewind();
	while(Current() != NULL)
	{
		if(! Current() -> IsObjectDeleted())
			Current() -> SaveData(p_opSaver);
		Next();
	}
	UnlockContainer();

	p_opSaver -> SaveString("EMMediaTransitionTrackRepository - End");

	return true;
}