	DeviceInfo::DeviceInfo()
	{
#if ALICE_SUPPORT_SSE
		int data[4] = { 0 };

		// Add more code here to extract vendor string or what ever is needed
		__cpuid(data, 0);
		if (data[0] >= 1) {
			__cpuid(data, 1);
			m_CPUIDFeatures = data[3];
		}

		m_IsSSESupported = (m_CPUIDFeatures & CPUID_FEATURES_SSE) != 0;
		m_IsSSE2Supported = (m_CPUIDFeatures & CPUID_FEATURES_SSE2) != 0;
#elif ALICE_ANDROID && ALICE_SUPPORTS_NEON
		m_CPUIDFeatures = android_getCpuFeatures();
		m_IsNEONSupported = (m_CPUIDFeatures & ANDROID_CPU_ARM_FEATURE_NEON) != 0;
#endif
		m_Initialized = true;
	}