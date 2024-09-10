int CALLBACK
WinMain(HINSTANCE Instance,
		HINSTANCE PrevInstance,
  		LPSTR CommandLine,
  		int ShowCode)
{
	Wind32LoadXInput();

	WNDCLASSA WindowClass = {};

	Win32ResizeDIBSection(&GlobalBackbuffer, 1280, 720);

	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  	WindowClass.lpfnWndProc = Win32MainWindowCallback;
  	WindowClass.hInstance = Instance;
  	// WindowClass.hIcon;
  	WindowClass.lpszClassName = "HandmadeHeroWindowClass";

  	if(RegisterClassA(&WindowClass))
  	{
		HWND Window =
			CreateWindowExA(
				0,
				WindowClass.lpszClassName,
				"Handmade Hero",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				Instance,
				0);

		if(Window)
		{
			// NOTE: Since we specified CS_OWNDC, we can just
			// create it once since we aren't sharing it with anybody
			HDC DeviceContext = GetDC(Window);

			// NOTE: Graphics test
			int XOffset = 0;
			int YOffset = 0;

			// NOTE: Sound test
			int SamplesPerSecond = 48000;
			int ToneHz = 256;
			int16 ToneVolume = 3000;
			uint32 RunningSampleIndex = 0;
			int SquareWavePeriod = SamplesPerSecond / ToneHz;
			int HalfSquareWavePeriod = SquareWavePeriod / 2;
			int BytesPerSample = sizeof(int16) * 2;
			int SecondaryBufferSize = SamplesPerSecond * BytesPerSample;

			Win32InitDSound(Window, SamplesPerSecond, SecondaryBufferSize);
			GlobalSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);

			GlobalRunning = true;

			while(GlobalRunning)
			{
				MSG Message;
				while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					if(Message.message == WM_QUIT)
					{
						GlobalRunning = false;
					}

					TranslateMessage(&Message);
					DispatchMessageA(&Message);
				}

				// TODO: Should we poll this more frequently?
				for(DWORD ControllerIndex = 0;
					ControllerIndex < XUSER_MAX_COUNT;
					++ControllerIndex)
				{
					XINPUT_STATE ControllerState;
					if(XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS)
					{
						// NOTE: This controller is plugged in
						// TODO: See if controllerstate.dwpacketnumber increments too rapidly
						XINPUT_GAMEPAD *Pad = &ControllerState.Gamepad;

						bool Up = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
						bool Down = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
						bool Left = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
						bool Right = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
						bool Start = (Pad->wButtons & XINPUT_GAMEPAD_START);
						bool Back = (Pad->wButtons & XINPUT_GAMEPAD_BACK);
						bool LeftShoulder = (Pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
						bool RightShoulder = (Pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
						bool AButton = (Pad->wButtons & XINPUT_GAMEPAD_A);
						bool BButton = (Pad->wButtons & XINPUT_GAMEPAD_B);
						bool XButton = (Pad->wButtons & XINPUT_GAMEPAD_X);
						bool YButton = (Pad->wButtons & XINPUT_GAMEPAD_Y);

						int16 stickX = Pad->sThumbLX;
						int16 stickY = Pad->sThumbLY;

						XOffset += stickX >> 12;
						YOffset += stickY >> 12;
					}
					else
					{
						// NOTE: The controller is not available
					}
				}

				RenderWeirdGradient(&GlobalBackbuffer, XOffset, YOffset);

				// NOTE DirectSound output test
				DWORD PlayCursor;
				DWORD WriteCursor;
				if(SUCCEEDED(GlobalSecondaryBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor)))
				{
					DWORD ByteToLock = RunningSampleIndex * BytesPerSample % SecondaryBufferSize;
					DWORD BytesToWrite;
					if(ByteToLock == PlayCursor)
					{
						BytesToWrite = SecondaryBufferSize;
					}
					else if(ByteToLock > PlayCursor)
					{
						BytesToWrite = SecondaryBufferSize - ByteToLock;
						BytesToWrite += PlayCursor;
					}
					else
					{
						BytesToWrite = PlayCursor - ByteToLock;
					}

					// TODO: More strenuous test
					VOID *Region1;
					DWORD Region1Size;
					VOID *Region2;
					DWORD Region2Size;

					if(SUCCEEDED(GlobalSecondaryBuffer->Lock(ByteToLock, BytesToWrite,
															 &Region1, &Region1Size,
															 &Region2, &Region2Size,
															 0)))
					{
						// TODO: assert that Region1SizeRegion2Size is valid

						int16 *SampleOut = (int16 *)Region1;
						DWORD Region1SampleCount = Region1Size / BytesPerSample;
						for(DWORD SampleIndex = 0;
							SampleIndex < Region1SampleCount;
							++SampleIndex)
						{
							int16 SampleValue = ((RunningSampleIndex++ / HalfSquareWavePeriod) % 2) ? ToneVolume : -ToneVolume;
							*SampleOut++ = SampleValue;
							*SampleOut++ = SampleValue;
						}


						DWORD Region2SampleCount = Region2Size / BytesPerSample;
						SampleOut = (int16 *)Region2;
						for(DWORD SampleIndex = 0;
								SampleIndex < Region2SampleCount;
								++SampleIndex)
						{
							int16 SampleValue = ((RunningSampleIndex++ / HalfSquareWavePeriod) % 2) ? ToneVolume : -ToneVolume;
							*SampleOut++ = SampleValue;
							*SampleOut++ = SampleValue;
						}

						GlobalSecondaryBuffer->Unlock(Region1, Region1Size, Region2, Region2Size);
					}
				}

				win32_window_dimension Dimension = Win32GetWindowDimension(Window);
				Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext,
										   Dimension.Width, Dimension.Height);
			}