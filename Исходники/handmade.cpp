internal void initDirectSound(HWND windowHandle, int32 samplePerSecond, int32 bufferSize) {
	// Load the library
	HMODULE directSoundLibrary = LoadLibraryA("dsound.dll");
	if ( ! directSoundLibrary ) {
		OutputDebugStringA("Direct sound dll not found ");
		return;
	}

	// Get a direct sound object
	direct_sound_create *directSoundCreate = (direct_sound_create*)GetProcAddress(directSoundLibrary, "DirectSoundCreate");

	HRESULT error;

	LPDIRECTSOUND directSound;
	error = directSoundCreate(0, &directSound, 0);
	if ( directSoundCreate && SUCCEEDED(error) ) {

		DSBUFFERDESC bufferDescription = {};
		bufferDescription.dwSize = sizeof(bufferDescription);
		bufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

		WAVEFORMATEX waveFormat = {};
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nChannels = 2;
		waveFormat.nSamplesPerSec = samplePerSecond;
		waveFormat.wBitsPerSample = 16;
		waveFormat.nBlockAlign = (waveFormat.nChannels*waveFormat.wBitsPerSample) / 8;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign; 
		waveFormat.cbSize = 0;

		

		LPDIRECTSOUNDBUFFER primaryBuffer;
		// create a primary buffer
		
		if ( SUCCEEDED(directSound->SetCooperativeLevel(windowHandle, DSSCL_PRIORITY)) ) {

			if ( SUCCEEDED(error = directSound->CreateSoundBuffer(&bufferDescription, &primaryBuffer, 0)) ) {
				
				if ( !(SUCCEEDED(error = primaryBuffer->SetFormat(&waveFormat))) ) {
					OutputDebugStringA("Primary buffer failed " + error );
				}

			} else {
				OutputDebugStringA("Primary buffer failed " + error);
			}

			DSBUFFERDESC bufferDescription = {};
			bufferDescription.dwSize = sizeof(bufferDescription);
			bufferDescription.dwFlags = 0;
			bufferDescription.dwBufferBytes = bufferSize;
			bufferDescription.lpwfxFormat = &waveFormat;

			
			// create a secondary buffer
			if ( SUCCEEDED(directSound->CreateSoundBuffer(&bufferDescription, &globalSecondaryBuffer, 0)) ) {

			}
		}

		

		// start playing it
	}
	else {
		OutputDebugStringA("Create DSound error " + error);
	}

	

}