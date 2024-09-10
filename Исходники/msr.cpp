	ThreadGroupTempAffinity(uint32 core_id)
	{
		GROUP_AFFINITY NewGroupAffinity;
		memset(&NewGroupAffinity, 0, sizeof(GROUP_AFFINITY));
		memset(&PreviousGroupAffinity, 0, sizeof(GROUP_AFFINITY));
		uint32 currentGroupSize = 0;

		while (core_id >= (currentGroupSize = GetMaximumProcessorCount(NewGroupAffinity.Group)))
		{
			core_id -= currentGroupSize;
			++NewGroupAffinity.Group;
		}
		NewGroupAffinity.Mask = 1ULL << core_id;
		SetThreadGroupAffinity(GetCurrentThread(),&NewGroupAffinity,&PreviousGroupAffinity);
	}