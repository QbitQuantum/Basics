void SampleMain()
{
	SfwOpenWindow("Gainput: Gesture sample");

	gainput::TrackingAllocator allocator(gainput::GetDefaultAllocator());

	gainput::InputManager manager(true, allocator);

	const gainput::DeviceId keyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();
	const gainput::DeviceId mouseId = manager.CreateDevice<gainput::InputDeviceMouse>();

	gainput::InputDeviceTouch* touchDevice = manager.CreateAndGetDevice<gainput::InputDeviceTouch>();
	GAINPUT_ASSERT(touchDevice);
	gainput::DeviceId touchId = touchDevice->GetDeviceId();

#if defined(GAINPUT_PLATFORM_LINUX) || defined(GAINPUT_PLATFORM_WIN)
	manager.SetDisplaySize(SfwGetWidth(), SfwGetHeight());
#endif

	SfwSetInputManager(&manager);

	gainput::InputMap map(manager, "testmap", allocator);

	map.MapBool(ButtonConfirm, mouseId, gainput::MouseButtonLeft);

	gainput::DoubleClickGesture* dcg = manager.CreateAndGetDevice<gainput::DoubleClickGesture>();
	GAINPUT_ASSERT(dcg);
	dcg->Initialize(mouseId, gainput::MouseButtonLeft,
			mouseId, gainput::MouseAxisX, 0.01f,
			mouseId, gainput::MouseAxisY, 0.01f,
			500);
	map.MapBool(ButtonConfirmDouble, dcg->GetDeviceId(), gainput::DoubleClickTriggered);

	gainput::SimultaneouslyDownGesture* sdg = manager.CreateAndGetDevice<gainput::SimultaneouslyDownGesture>();
	GAINPUT_ASSERT(sdg);
	sdg->AddButton(mouseId, gainput::MouseButtonLeft);
	sdg->AddButton(keyboardId, gainput::KeyShiftL);
	map.MapBool(ButtonConfirmExtra, sdg->GetDeviceId(), gainput::SimultaneouslyDownTriggered);

	MultiTouchEmulator* mte = manager.CreateAndGetDevice<MultiTouchEmulator>();
	mte->Initialize(sdg->GetDeviceId(), gainput::SimultaneouslyDownTriggered,
			mouseId, gainput::MouseAxisX,
			mouseId, gainput::MouseAxisY,
			mouseId, gainput::MouseButtonLeft,
			mouseId, gainput::MouseAxisX,
			mouseId, gainput::MouseAxisY);

	if (!touchDevice->IsAvailable() || touchDevice->GetVariant() == gainput::InputDevice::DV_NULL)
	{
		touchId = mte->GetDeviceId();
	}

	gainput::HoldGesture* hg = manager.CreateAndGetDevice<gainput::HoldGesture>();
	GAINPUT_ASSERT(hg);
	hg->Initialize(touchId, gainput::Touch0Down,
			touchId, gainput::Touch0X, 0.1f,
			touchId, gainput::Touch0Y, 0.1f,
			true,
			800);
	map.MapBool(ButtonHoldGesture, hg->GetDeviceId(), gainput::HoldTriggered);

	gainput::TapGesture* tg = manager.CreateAndGetDevice<gainput::TapGesture>();
	GAINPUT_ASSERT(tg);
	tg->Initialize(touchId, gainput::Touch0Down,
			500);
	map.MapBool(ButtonTapGesture, tg->GetDeviceId(), gainput::TapTriggered);
	
	gainput::PinchGesture* pg = manager.CreateAndGetDevice<gainput::PinchGesture>();
	GAINPUT_ASSERT(pg);
	pg->Initialize(touchId, gainput::Touch0Down,
			touchId, gainput::Touch0X,
			touchId, gainput::Touch0Y,
			touchId, gainput::Touch1Down,
			touchId, gainput::Touch1X,
			touchId, gainput::Touch1Y);
	map.MapBool(ButtonPinching, pg->GetDeviceId(), gainput::PinchTriggered);
	map.MapFloat(ButtonPinchScale, pg->GetDeviceId(), gainput::PinchScale);

	gainput::RotateGesture* rg = manager.CreateAndGetDevice<gainput::RotateGesture>();
	GAINPUT_ASSERT(rg);
	rg->Initialize(touchId, gainput::Touch0Down,
			touchId, gainput::Touch0X,
			touchId, gainput::Touch0Y,
			touchId, gainput::Touch1Down,
			touchId, gainput::Touch1X,
			touchId, gainput::Touch1Y);
	map.MapBool(ButtonRotating, rg->GetDeviceId(), gainput::RotateTriggered);
	map.MapFloat(ButtonRotateAngle, rg->GetDeviceId(), gainput::RotateAngle);

	bool doExit = false;

	while (!SfwIsDone() && !doExit)
	{
		manager.Update();

#if defined(GAINPUT_PLATFORM_LINUX)
		XEvent event;
		while (XPending(SfwGetXDisplay()))
		{
			XNextEvent(SfwGetXDisplay(), &event);
			manager.HandleEvent(event);
			if (event.type == DestroyNotify || event.type == ClientMessage)
			{
				doExit = true;
			}
		}
#elif defined(GAINPUT_PLATFORM_WIN)
		MSG msg;
		while (PeekMessage(&msg, SfwGetHWnd(),  0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			manager.HandleMessage(msg);
		}
#endif

		SfwUpdate();

		if (map.GetBoolWasDown(ButtonConfirm))
		{
			SFW_LOG("Confirmed!\n");
			SFW_LOG("Memory: %u allocs, %u deallocs, %u used bytes\n", static_cast<unsigned>(allocator.GetAllocateCount()), static_cast<unsigned>(allocator.GetDeallocateCount()), static_cast<unsigned>(allocator.GetAllocatedMemory()));
		}

		if (map.GetBoolWasDown(ButtonConfirmDouble))
		{
			SFW_LOG("Confirmed doubly!\n");
		}

		if (map.GetBoolWasDown(ButtonConfirmExtra))
		{
			SFW_LOG("Confirmed alternatively!\n");
		}

		if (map.GetBool(ButtonHoldGesture))
		{
			SFW_LOG("Hold triggered!\n");
		}

		if (map.GetBoolWasDown(ButtonTapGesture))
		{
			SFW_LOG("Tapped!\n");
		}

		if (map.GetBool(ButtonPinching))
		{
			SFW_LOG("Pinching: %f\n", map.GetFloat(ButtonPinchScale));
		}

		if (map.GetBool(ButtonRotating))
		{
			SFW_LOG("Rotation angle: %f\n", map.GetFloat(ButtonRotateAngle));
		}
	}

	SfwCloseWindow();
}