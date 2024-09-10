void VolumeControl::deinit()
{
	//deinitialize audio mixer interface
#if defined (__APPLE__)
	#warning TODO: Not implemented for MacOS yet!!!
#elif defined(__linux__)
	if (mixerHandle != nullptr) {
		snd_mixer_detach(mixerHandle, mixerCard);
		snd_mixer_free(mixerHandle);
		snd_mixer_close(mixerHandle);
		mixerHandle = nullptr;
		mixerElem = nullptr;
	}
#elif defined(WIN32) || defined(_WIN32)
	if (mixerHandle != nullptr) {
		mixerClose(mixerHandle);
		mixerHandle = nullptr;
	}
	else if (endpointVolume != nullptr) {
		endpointVolume->Release();
		endpointVolume = nullptr;
		CoUninitialize();
	}
#endif
}