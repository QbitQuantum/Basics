void CameraWorker::configure(CameraWorker* cw)
{
	cw->session = PXCSession::CreateInstance();
	cw->ver = cw->session->QueryVersion();
	wprintf_s(L"SDK Session startet with version %d.%d\n", cw->ver.major, cw->ver.minor);
	cw->senseManager = PXCSenseManager::CreateInstance();
	cw->senseManager->EnableHand();
	cw->senseManager->Init();
	cw->hand = cw->senseManager->QueryHand();
	//handData = hand->CreateOutput();

	cw->config = cw->hand->CreateActiveConfiguration();
	//config->EnableNormalizedJoints(true);
	//config->EnableSegmentationImage(true);
	// Disable initially all gestures
	//config->DisableAllGestures();
	// enable only the needed ones
	cw->config->EnableGesture(L"spreadfingers", true);
	cw->config->EnableGesture(L"two_fingers_pinch_open", true);
	cw->config->EnableGesture(L"wave", true);
	cw->config->EnableAllAlerts();
	cw->config->ApplyChanges();
	//config->Update();
	
}