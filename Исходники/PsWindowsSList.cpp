	SListEntry* SListImpl::flush()
	{
		return reinterpret_cast<SListEntry*>(InterlockedFlushSList(getDetail(this)));
	}