		//================================================================
		//================================================================
		DllExport void __cdecl EndSession(IAgent* agent, __int32 sessionId)
		{
			CSessionDataCache::iterator i = sessionDataCache.find(sessionId);

			if (i != sessionDataCache.end())
			{
				sessionDataCache.erase(i);
			}

			CoFreeUnusedLibrariesEx(0, 0);
		}