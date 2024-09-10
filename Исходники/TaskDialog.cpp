  int cTaskDialog::Run(cWindow& parent, const cTaskDialogSettings& settings)
  {
    // Create our task dialog
    TASKDIALOGCONFIG tdc = { 0 };
    tdc.cbSize = sizeof(tdc);
    tdc.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION;
    if (settings.bIsCheckBoxTickedInitially) tdc.dwFlags |= TDF_VERIFICATION_FLAG_CHECKED;
    tdc.dwCommonButtons = (settings.bCloseButtonText ? TDCBF_CLOSE_BUTTON : TDCBF_CANCEL_BUTTON);
    tdc.hwndParent = parent.GetWindowHandle();
    tdc.hInstance = GetHInstance();

    //tdc.hMainIcon = hIcon;

    switch (settings.type) {
      case cTaskDialogSettings::TYPE::INFORMATION: {
        tdc.pszMainIcon = TD_INFORMATION_ICON;
        break;
      }
      case cTaskDialogSettings::TYPE::WARNING: {
        tdc.pszMainIcon = TD_ERROR_ICON;
        break;
      }
      case cTaskDialogSettings::TYPE::ERROR: {
        tdc.pszMainIcon = TD_ERROR_ICON;
        break;
      }
    };

    tdc.pszWindowTitle = settings.sCaption.c_str();
    tdc.pszMainInstruction = settings.sInstructions.c_str();
    tdc.pszContent = settings.sContent.c_str();

    // Add our buttons
    TASKDIALOG_BUTTON* pButtons = nullptr;
    const size_t nButtons = settings.items.size();
    if (!settings.items.empty()) {
      tdc.dwFlags |= TDF_USE_COMMAND_LINKS;

      pButtons = new TASKDIALOG_BUTTON[nButtons];
      for (size_t i = 0; i < nButtons; i++) {
        pButtons[i].nButtonID = settings.items[i].iCommandID;
        string_t sText(settings.items[i].sText);
        if (!settings.items[i].sTextDescription.empty()) {
          sText += TEXT("\n");
          sText += settings.items[i].sTextDescription;
        }

        const size_t nSize = sText.length() + 1;
        pButtons[i].pszButtonText = new wchar_t[nSize];
        wcscpy_s((wchar_t*)(pButtons[i].pszButtonText), nSize, sText.c_str());
      }

      tdc.pButtons = pButtons;
      tdc.cButtons = UINT(nButtons);

      tdc.nDefaultButton = settings.iDefaultItemCommandID;
    }

    /*PCWSTR      pszExpandedInformation;
    PCWSTR      pszExpandedControlText;
    PCWSTR      pszCollapsedControlText;*/

    tdc.pfCallback = _TaskDialogCallbackProc;
    tdc.lpCallbackData = LONG_PTR(this);

    if (settings.bIsProgressBarVisible) {
      tdc.dwFlags |= TDF_CALLBACK_TIMER | TDF_SHOW_PROGRESS_BAR;
    }

    // Checkbox
    if (settings.bIsCheckBoxVisible) {
      tdc.dwFlags |= TDF_EXPAND_FOOTER_AREA;
      tdc.pszVerificationText = settings.sCheckBoxTitle.c_str();
    }

    // Run the task dialog
    int iButton = 0;
    //BOOL bResult = FALSE;
    const HRESULT rResult = TaskDialogIndirect(&tdc, &iButton, NULL, nullptr /*&bResult*/);
    assert(rResult == S_OK);

    // Clear our window handle
    hwndWindow = NULL;

    // Destroy our buttons
    if (pButtons != nullptr) {
      for (size_t i = 0; i < nButtons; i++) delete [] pButtons[i].pszButtonText;
      delete [] pButtons;
    }

    // If there was an error then pretend the user cancelled
    if (rResult != S_OK) iButton = IDCANCEL;
    
    // If no valid selection was made then pretend the user cancelled
    if (iButton < 0) iButton = IDCANCEL;

    // Return the button that was selected
    return iButton;
  }