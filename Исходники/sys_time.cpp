		PerformanceFreqHolder()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			value = freq.QuadPart;
		}