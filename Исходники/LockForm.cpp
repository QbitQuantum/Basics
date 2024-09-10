void
LockForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	// TODO:
	// To unlock the screen, terminate the lock application.
	AppLog("OnActionPerformed called!");
	if (actionId == IDA_UNLOCK_BUTTON)
	{
		AppLog("actionId == IDA_UNLOCK_BUTTON, destroy myself");

		AppLog("isLocked = false"); //exit app normally
		isLocked = false;

		UiApp* pApp = UiApp::GetInstance();
		AppAssert(pApp);
		pApp->Terminate();
	}
}