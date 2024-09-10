bool Platform_Win32_Sound_DSound::Setup()
	{
	dsoundDLL_=LoadLibrary("dsound.dll");

	if (dsoundDLL_)
		{
		typedef HRESULT (WINAPI *DirectSoundCreateDefinition)(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter);
		DirectSoundCreateDefinition DirectSoundCreate=(DirectSoundCreateDefinition)GetProcAddress((HMODULE)dsoundDLL_, "DirectSoundCreate");


		HRESULT hr;
		hr = DirectSoundCreate(NULL, &directSound_, NULL);
		if (!SUCCEEDED(hr))
			{
			Platform::GetPlatform_OS()->OutputDebugText("Couldn't create DirectSound object\n");
			return false;
			}

		hr = directSound_->SetCooperativeLevel(windowHandle_, /* DSSCL_EXCLUSIVE*/ DSSCL_NORMAL);
		if (!SUCCEEDED(hr))
			{
			Platform::GetPlatform_OS()->OutputDebugText("Couldn't set cooperative level for DirectSound object\n");
			return false;
			}

		return true;
		}

	Platform::GetPlatform_OS()->OutputDebugText("Couldn't load dsound.dll\n");
	return false;
	}