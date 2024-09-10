LRESULT CAppWindow::OnLoginStateChanged(WAVE_CONNECTION_STATE nStatus, WAVE_LOGIN_ERROR nError)
{
	CHECK_ENUM(nStatus, WCS_MAX);
	CHECK_ENUM(nError, WLE_MAX);

	if (!AllowContextMenu())
	{
		EndMenu();
	}

	switch (nStatus)
	{
	case WCS_BEGIN_LOGON:
	case WCS_BEGIN_SIGNOUT:
		StartWorking();
		break;

	case WCS_LOGGED_ON:
		StopWorking();
		ProcessLoggedOn();
		break;

	case WCS_RECONNECTING:
		StartWorking();
		ProcessReconnecting();
		break;

	case WCS_CONNECTED:
		StopWorking();
		ProcessConnected();
		break;

	case WCS_FAILED:
		StopWorking();
		break;

	case WCS_SIGNED_OUT:
		StopWorking();
		ProcessSignedOut();
		break;
	}

	return 0;
}