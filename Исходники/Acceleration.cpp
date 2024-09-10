	CCpuAccel()
	{
		int info[4];

		__cpuid(info, 0x00000000);
		int Basic = info[0];
		__cpuid(info, 0x00000001);
		if (info[3] & 0x00800000)
			m_Supported |= ACCEL_MMX;
		if (info[3] & 0x02000000)
			m_Supported |= ACCEL_SSE;
		if (info[3] & 0x04000000)
			m_Supported |= ACCEL_SSE2;
		if (info[2] & 0x00000001)
			m_Supported |= ACCEL_SSE3;
		if (info[2] & 0x00000200)
			m_Supported |= ACCEL_SSSE3;
		if (info[2] & 0x00080000)
			m_Supported |= ACCEL_SSE4_1;
		if (info[2] & 0x00100000)
			m_Supported |= ACCEL_SSE4_2;
		if (info[2] & 0x10000000)
			m_Supported |= ACCEL_AVX;
		if (Basic >= 7) {
			__cpuidex(info, 7, 0);
			if (info[1] & 0x00000020)
				m_Supported |= ACCEL_AVX2;
		}

		bool fAVX = false;
		if (::IsProcessorFeaturePresent(PF_XSAVE_ENABLED)) {
			GetEnabledXStateFeatures_Ptr pGetEnabledXStateFeatures =
				(GetEnabledXStateFeatures_Ptr)
					::GetProcAddress(::GetModuleHandle(TEXT("kernel32.dll")),
									 "GetEnabledXStateFeatures");
			if (pGetEnabledXStateFeatures
					&& (pGetEnabledXStateFeatures() & XSTATE_MASK_AVX)) {
				fAVX = true;
			}
		}
		if (!fAVX)
			m_Supported &= ~(ACCEL_AVX | ACCEL_AVX2);

		m_Enabled = m_Supported;
	}