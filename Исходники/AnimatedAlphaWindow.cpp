void CAnimatedAlphaWindow::Initialize()
{
	UUID
		myCLSID_UIAnimationManager,
		myCLSID_UIAnimationTimer,
		myCLSID_UIAnimationTransitionLibrary;
	UuidFromString((RPC_WSTR)L"4C1FC63A-695C-47E8-A339-1A194BE3D0B8", &myCLSID_UIAnimationManager);
	UuidFromString((RPC_WSTR)L"BFCD4A0C-06B6-4384-B768-0DAA792C380E", &myCLSID_UIAnimationTimer);
	UuidFromString((RPC_WSTR)L"1D6322AD-AA85-4EF5-A828-86D71067D145", &myCLSID_UIAnimationTransitionLibrary);

	// Initialize WAM objects
	ASSERT_SUCCEEDED(mAnimMgr.CoCreateInstance(myCLSID_UIAnimationManager));
	ASSERT_SUCCEEDED(mAnimTimer.CoCreateInstance(myCLSID_UIAnimationTimer));
	ASSERT_SUCCEEDED(mTransLib.CoCreateInstance(myCLSID_UIAnimationTransitionLibrary)); 

	// Connect the animation manager to the timer
	// UI_ANIMATION_IDLE_BEHAVIOR_DISABLE tells the timer to shut itself off when there is nothing to
	// animate
	CComQIPtr<IUIAnimationTimerUpdateHandler> spTimerUpdateHandler(mAnimMgr);
	ASSERT_SUCCEEDED(mAnimTimer->SetTimerUpdateHandler(spTimerUpdateHandler,
		UI_ANIMATION_IDLE_BEHAVIOR_DISABLE));

	// Now connect the timer to this window
	CComObject<AnimTimerEventHandler> *evthandler;
	ASSERT_SUCCEEDED( CComObject<AnimTimerEventHandler>::CreateInstance(&evthandler));
	evthandler->Initialize(boost::bind(UpdateCallback, this));
	CComQIPtr<IUIAnimationTimerEventHandler> spTimerEventHandler(evthandler);
	ASSERT_SUCCEEDED(mAnimTimer->SetTimerEventHandler(spTimerEventHandler));
	ASSERT_SUCCEEDED(mAnimTimer->SetFrameRateThreshold(300));

	// Create animation variable(s)
	ASSERT_SUCCEEDED(mAnimMgr->CreateAnimationVariable(LARGE, &mAlphaVar));
	ASSERT_SUCCEEDED(mAnimMgr->CreateAnimationVariable(mCurrentSweep, &mSweepVar));
}