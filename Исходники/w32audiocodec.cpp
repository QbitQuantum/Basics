bool VDAudioCodecW32::Init(const WAVEFORMATEX *pSrcFormat, const WAVEFORMATEX *pDstFormat, bool isCompression, const char *pDriverShortNameHint, bool throwOnError) {
	Shutdown();

	SafeCopyWaveFormat(mSrcFormat, (const VDWaveFormat *)pSrcFormat);

	if (pDstFormat)
		SafeCopyWaveFormat(mDstFormat, (const VDWaveFormat *)pDstFormat);

	// enumerate IDs for all installed codecs
	ACMDriverList driverList(pDriverShortNameHint);

	// try one driver at a time
	MMRESULT res = 0;

	for(ACMDriverList::const_iterator it(driverList.begin()), itEnd(driverList.end());
		it != itEnd;
		++it)
	{
		const HACMDRIVERID driverId = *it;

		// open driver
		HACMDRIVER hDriver = NULL;
		if (acmDriverOpen(&hDriver, *it, 0))
			continue;

		if (!pDstFormat) {
			VDASSERT(!isCompression);
		
			DWORD dwDstFormatSize = 0;

			VDVERIFY(!acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, (LPVOID)&dwDstFormatSize));

			if (dwDstFormatSize < sizeof(WAVEFORMATEX))
				dwDstFormatSize = sizeof(WAVEFORMATEX);

			mDstFormat.resize(dwDstFormatSize);
			memset(mDstFormat.data(), 0, dwDstFormatSize);
			mDstFormat->mTag = WAVE_FORMAT_PCM;

			if (acmFormatSuggest(hDriver, (WAVEFORMATEX *)pSrcFormat, (WAVEFORMATEX *)mDstFormat.data(), dwDstFormatSize, ACM_FORMATSUGGESTF_WFORMATTAG)) {
				acmDriverClose(hDriver, NULL);
				continue;
			}

			// sanitize the destination format a bit

			if (mDstFormat->mSampleBits != 8 && mDstFormat->mSampleBits != 16)
				mDstFormat->mSampleBits = 16;

			if (mDstFormat->mChannels != 1 && mDstFormat->mChannels !=2)
				mDstFormat->mChannels = 2;

			mDstFormat->mBlockSize		= (uint16)((mDstFormat->mSampleBits >> 3) * mDstFormat->mChannels);
			mDstFormat->mDataRate		= mDstFormat->mBlockSize * mDstFormat->mSamplingRate;
			mDstFormat->mExtraSize		= 0;
			mDstFormat.resize(sizeof(WAVEFORMATEX));
		}

		// open conversion stream
		res = acmStreamOpen(&mhStream, hDriver, (WAVEFORMATEX *)pSrcFormat, (WAVEFORMATEX *)mDstFormat.data(), NULL, 0, 0, ACM_STREAMOPENF_NONREALTIME);
		if (!res) {
			mhDriver = hDriver;
			break;
		}

		// Aud-X accepts PCM/6ch but not WAVE_FORMAT_EXTENSIBLE/PCM/6ch. Argh. We attempt to work
		// around this by trying a PCM version if WFE doesn't work.
		if (isCompression) {
			// Need to put this somewhere.
			struct WaveFormatExtensibleW32 {
				WAVEFORMATEX mFormat;
				union {
					uint16 mBitDepth;
					uint16 mSamplesPerBlock;		// may be zero, according to MSDN
				};
				uint32	mChannelMask;
				GUID	mGuid;
			};

			static const GUID local_KSDATAFORMAT_SUBTYPE_PCM={	// so we don't have to bring in ksmedia.h
				WAVE_FORMAT_PCM, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71
			};

			if (pSrcFormat->wFormatTag == WAVE_FORMAT_EXTENSIBLE && pSrcFormat->cbSize >= sizeof(WaveFormatExtensibleW32) - sizeof(WAVEFORMATEX)) {
				const WaveFormatExtensibleW32& wfexex = *(const WaveFormatExtensibleW32 *)pSrcFormat;

				if (wfexex.mGuid == local_KSDATAFORMAT_SUBTYPE_PCM) {
					// Rewrite the format to be straight PCM and try again.
					vdstructex<VDWaveFormat> srcFormat2(mSrcFormat.data(), sizeof(VDWaveFormat));
					srcFormat2->mExtraSize	= 0;
					srcFormat2->mTag		= WAVE_FORMAT_PCM;
					MMRESULT res2 = acmStreamOpen(&mhStream, hDriver, (WAVEFORMATEX *)srcFormat2.data(), (WAVEFORMATEX *)mDstFormat.data(), NULL, 0, 0, ACM_STREAMOPENF_NONREALTIME);

					if (!res2) {
						res = res2;
						mSrcFormat = srcFormat2;
						pSrcFormat = (WAVEFORMATEX *)mSrcFormat.data();

						mhDriver = hDriver;
						break;
					}
				}
			}
		}

		acmDriverClose(hDriver, 0);
	}