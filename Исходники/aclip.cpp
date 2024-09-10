Exec_stat MCAudioClip::getprop(uint4 parid, Properties which, MCExecPoint &ep, Boolean effective)
{
	switch (which)
	{
#ifdef /* MCAudioClip::getprop */ LEGACY_EXEC
	case P_SIZE:
		ep.setint(size);
		break;
	case P_PLAY_DESTINATION:
	case P_PLAY_LOUDNESS:
		if (this == MCtemplateaudio)
		{
			extern bool MCSystemGetPlayLoudness(uint2& r_loudness);
#ifdef _MOBILE
			if (MCSystemGetPlayLoudness(loudness))
#else
			if (false)
#endif
				;
			else if (!supported)
				loudness = 0;
			else
			{
#if defined _WINDOWS
				if (hwaveout == NULL)
				{
					WAVEFORMATEX pwfx;
					pwfx.wFormatTag = WAVE_FORMAT_PCM;
					pwfx.nChannels = 1;
					pwfx.nSamplesPerSec = 22050;
					pwfx.nAvgBytesPerSec = 22050;
					pwfx.nBlockAlign = 1;
					pwfx.wBitsPerSample = 8;
					pwfx.cbSize = 0;
					if (waveOutOpen(&hwaveout, WAVE_MAPPER, &pwfx, 0, 0, CALLBACK_NULL
					                | WAVE_ALLOWSYNC) == MMSYSERR_NOERROR)
					{
						DWORD v;
						waveOutGetVolume(hwaveout, &v);
						loudness = MCU_min((uint2)((v & 0xFFFF) * 100 / 0xFFFF) + 1, 100);
						waveOutClose(hwaveout);
						hwaveout = NULL;
					}
				}
#elif defined _MACOSX
				long volume;
				GetDefaultOutputVolume(&volume);
				loudness = (HiWord(volume) + LoWord(volume)) * 50 / 255;
#elif defined TARGET_PLATFORM_LINUX
				if ( x11audio != NULL)
					loudness = x11audio -> getloudness();
#endif
			}
		}
		if (which == P_PLAY_DESTINATION)
		{
			if (flags & F_EXTERNAL)
				ep.setstaticcstring("external");
			else
				ep.setstaticcstring("internal");
		}
		else
			ep.setint(loudness);
		break;
#endif /* MCAudioClip::getprop */ 
	default:
		return MCObject::getprop(parid, which, ep, effective);
	}
	return ES_NORMAL;
}