void  Idl_tutorial1::OnFormBackRequested (Tizen::Ui::Controls::Form &source)
{
	AppLog("왜안꺼져");
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}