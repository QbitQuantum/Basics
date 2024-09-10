int DrawableDictStoreGetUsageWrap(int dict)
{
	int usage = DrawblDictGetUsage(dict);

	if (usage == 0 && _ReturnAddress() == (void*)0xBCC153)
	{
		bool deferred = false;

		auto pair = m_dependencyDrawableDicts.equal_range(dict);

		for (auto it = pair.first; it != pair.second; it++)
		{
			if (it->second->HasInstance())
			{
				if (!it->second->ShouldRelease())
				{
					//trace("model info for %s (0x%08x) still has %i references!\n", GetStreamName(dict, *(int*)0xF272E4).c_str(), it->second->GetModelHash(), it->second->GetRefCount());

					return 1;
				}

				it->second->RemoveInstance();

				deferred = true;
			}
		}

		//m_dependencyDrawableDicts.erase(dict);

		auto entPair = m_dependencyDictEnts.equal_range(dict);

		for (auto it = entPair.first; it != entPair.second; it++)
		{
			it->second->DestroyModel();

			deferred = true;
		}

		m_dependencyDictEnts.erase(dict);

		if (deferred)
		{
			//trace("pre-deferring drawable destruction for %s\n", GetStreamName(dict, *(int*)0xF272E4).c_str());

			DeferToNextFrame([=] ()
			{
				//trace("executing pre-deferred drawable destruction for %s\n", GetStreamName(dict, *(int*)0xF272E4).c_str());

				//ReleaseDrawblDict(dict);
				ReleaseStreamingObjectNow((void*)0xF21C60, dict + GetTypeStart(*(int*)0xF272E4));
			});

			return 1;
		}
	}

	return usage;
}