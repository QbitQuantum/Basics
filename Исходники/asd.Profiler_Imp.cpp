	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	void Profiler_Imp::Start(int id)
	{
		Profile::Ptr profile = nullptr;
		for (auto& x : m_profiles)
		{
			if (x->GetID() == id)
			{
				profile = x;
			}
		}

		if (profile == nullptr)
		{
			profile = make_shared<Profile>(id);
			m_profiles.push_back(profile);
		}

		profile->GetCurrent()->SetStartTime(asd::GetTime());

#if _WIN32
		profile->GetCurrent()->SetProcessorNumber(GetCurrentProcessorNumber());
#elif defined(__APPLE__)
		// sched_getcpuがないようなので代用。よりよいものがあれば差し替えてください。
		profile->GetCurrent()->SetProcessorNumber(
			std::hash<std::thread::id>()(std::this_thread::get_id()));
#else
		profile->GetCurrent()->SetProcessorNumber(sched_getcpu());
#endif
	}