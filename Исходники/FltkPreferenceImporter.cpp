	void DeleteFltkPreference() {
		auto path = GetFltkPreferencePath();
		/*
#ifdef WIN32
		DeleteFileW(Utf8ToWString(path.c_str()).c_str());
#else
		unlink(path.c_str());
#endif
		*/
		
		// afraid of removing the pref file completely
		SPLog("Moving %s to %s", path.c_str(), (path + "-old").c_str());
#ifdef WIN32
		auto s = Utf8ToWString(path.c_str());
		MoveFileW(s.c_str(), (s + L"-old").c_str());
#else
		rename(path.c_str(), (path + "-old").c_str());
#endif
	}