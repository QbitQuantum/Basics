DWORD WINAPI DialogThreadEntry(LPVOID lpParam)
{
	int buttonPressed = 0;
	EXTERNAL_INFO *externalInfo = (PEXTERNAL_INFO)lpParam;
	TASKDIALOGCONFIG config = {0};

	config.cbSize = sizeof(config);
	config.hInstance = GetModuleHandle(NULL);
	config.dwCommonButtons = TDCBF_CANCEL_BUTTON;
	config.pszMainIcon = TD_INFORMATION_ICON;
	
	if(externalInfo->langId == 0x0419)
		config.pszMainInstruction = L"PIN Pad считыватель";
	else if(externalInfo->langId == 0x0425)
		//config.pszMainInstruction = L"Autentige PINPADˇiga";
		config.pszMainInstruction = L"PIN Pad kaardilugeja";
	else
		config.pszMainInstruction = L"PIN Pad Reader";

	if(externalInfo->pinType == 1)
	{
		if(externalInfo->langId == 0x0419)
			config.pszContent = L"Введите код PIN для идентификации (PIN 1)";
		else if(externalInfo->langId == 0x0425)
			config.pszContent = L"Palun sisestage autoriseerimise PIN (PIN1)";
		else
			config.pszContent = L"Enter PIN for authentication (PIN 1)";
	}
	else if(externalInfo->pinType == 3)
	{
		if(externalInfo->langId == 0x0419)
			config.pszContent = L"Введите код PIN для подписи (PIN 2)";
		else if(externalInfo->langId == 0x0425)
			config.pszContent = L"Palun sisestage digiallkirjastamise PIN (PIN2)";
		else
			config.pszContent = L"Enter PIN for digital signature (PIN 2)";
	}
	else
	{
		config.pszContent = L"Enter PIN";
		if(externalInfo->langId == 0x0419)
			config.pszContent = L"Введите PIN код";
		else if(externalInfo->langId == 0x0425)
			config.pszContent = L"Sisestage PIN";
		else
			config.pszContent = L"Enter PIN code";
	}

	config.dwFlags = TDF_EXPAND_FOOTER_AREA  | TDF_SHOW_PROGRESS_BAR | TDF_CALLBACK_TIMER | TDF_ENABLE_HYPERLINKS;
	if(externalInfo->langId == 0x0419)
	{
		if(externalInfo->pinType == 1)
		{
			config.pszExpandedInformation = L"Данная операция требует сертификат идентификации. Для использования сертификата идентификации введите PIN1 с клавиатуры считывателя.";
		}
		else if(externalInfo->pinType == 3)
		{
			config.pszExpandedInformation = L"Для данной операцин необходим сертификат подписи. Для использования сертификата подписи введите PIN2 с клавиатуры считывателя.";
		}
	}
	else if(externalInfo->langId == 0x0425)
	{
		if(externalInfo->pinType == 1)
		{
			config.pszExpandedInformation = L"Valitud tegevuse jaoks on vaja kasutada isikutuvastuse sertifikaati. Sertifikaadi kasutamiseks sisesta PIN1 kaardilugeja sõrmistikult.";
		}
		else if(externalInfo->pinType == 3)
		{
			config.pszExpandedInformation = L"Valitud tegevuse jaoks on vaja kasutada allkirjastamise sertifikaati. Sertifikaadi kasutamiseks sisesta PIN2 kaardilugeja sõrmistikult.";
		}
	}
	else
	{
		if(externalInfo->pinType == 1)
		{
			config.pszExpandedInformation = L"Selected action requires authentication certificate. For using authentication certificate enter PIN1 at the reader.";
		}
		else if(externalInfo->pinType == 3)
		{
			config.pszExpandedInformation = L"Selected action requires digital signature certificate. For using signature certificate enter PIN2 at the reader.";
		}
	}
	config.pfCallback = TaskDialogCallbackProcPinEntry;
	BOOL bVerification = false;
	HRESULT res = TaskDialogIndirect(&config, &buttonPressed, NULL, NULL);
	
	return 0;
}