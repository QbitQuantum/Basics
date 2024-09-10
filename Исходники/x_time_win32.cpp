		virtual u64			getFileTimeFromSystemTime(u64 inSystemTime)
		{
			u64 systemTime = getSystemTimeLocal();
			u64 fileTime = getSystemTimeAsFileTime();
			return inSystemTime + (fileTime - systemTime);
		}