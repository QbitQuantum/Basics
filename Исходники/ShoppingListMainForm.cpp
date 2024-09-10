void
ShoppingListMainForm::OnFormBackRequested(Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}