bool
EventListForm::Initialize(void)
{
	result r = E_SUCCESS;

	r = Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(!IsFailed(r), false, "[%s] Failed to construct the form.", GetErrorMessage(r));

	__pCalendarbook = new (std::nothrow) Calendarbook();
	TryReturn(__pCalendarbook != null, false, "Failed to instantiate calendarbook.");

	r = __pCalendarbook->Construct(*this);
	if(IsFailed(r))
	{
		__pCalendarbook->Construct();
		__pCalendarbook->GetLatestVersion();
		r = GetLastResult();

		MessageBox messageBox;

		if(r == E_USER_NOT_CONSENTED)
		{
			messageBox.Construct(L"Error", L"The calendar privacy should be enabled.", MSGBOX_STYLE_OK);
		}
		else
		{
			messageBox.Construct(L"Error", L"Failed to construct the calendarbook.", MSGBOX_STYLE_OK);
		}

		int doModal;
		messageBox.ShowAndWait(doModal);

		UiApp* pApp = UiApp::GetInstance();
		AppAssert(pApp);
		pApp->Terminate();
	}

	return true;
}