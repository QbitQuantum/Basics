//------------------------------------------------------------------
// Displays the native Print Dialog
static nsresult 
ShowNativePrintDialog(HWND              aHWnd,
                      nsIPrintSettings* aPrintSettings)
{
  //NS_ENSURE_ARG_POINTER(aHWnd);
  NS_ENSURE_ARG_POINTER(aPrintSettings);

  gDialogWasExtended  = false;

  // Get the Print Name to be used
  nsXPIDLString printerName;
  aPrintSettings->GetPrinterName(getter_Copies(printerName));

  // If there is no name then use the default printer
  if (printerName.IsEmpty()) {
    GetDefaultPrinterNameFromGlobalPrinters(printerName);
  } else {
    HANDLE hPrinter = nullptr;
    if(!::OpenPrinterW(const_cast<wchar_t*>(static_cast<const wchar_t*>(printerName.get())),
                       &hPrinter, nullptr)) {
      // If the last used printer is not found, we should use default printer.
      GetDefaultPrinterNameFromGlobalPrinters(printerName);
    } else {
      ::ClosePrinter(hPrinter);
    }
  }

  // Now create a DEVNAMES struct so the the dialog is initialized correctly.

  uint32_t len = printerName.Length();
  nsHGLOBAL hDevNames = ::GlobalAlloc(GHND, sizeof(wchar_t) * (len + 1)
                                      + sizeof(DEVNAMES));
  nsAutoGlobalMem autoDevNames(hDevNames);
  if (!hDevNames) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  DEVNAMES* pDevNames = (DEVNAMES*)::GlobalLock(hDevNames);
  if (!pDevNames) {
    return NS_ERROR_FAILURE;
  }
  pDevNames->wDriverOffset = sizeof(DEVNAMES)/sizeof(wchar_t);
  pDevNames->wDeviceOffset = sizeof(DEVNAMES)/sizeof(wchar_t);
  pDevNames->wOutputOffset = sizeof(DEVNAMES)/sizeof(wchar_t)+len;
  pDevNames->wDefault      = 0;

  memcpy(pDevNames+1, printerName, (len + 1) * sizeof(wchar_t));
  ::GlobalUnlock(hDevNames);

  // Create a Moveable Memory Object that holds a new DevMode
  // from the Printer Name
  // The PRINTDLG.hDevMode requires that it be a moveable memory object
  // NOTE: autoDevMode is automatically freed when any error occurred
  nsAutoGlobalMem autoDevMode(CreateGlobalDevModeAndInit(printerName, aPrintSettings));

  // Prepare to Display the Print Dialog
  PRINTDLGW  prntdlg;
  memset(&prntdlg, 0, sizeof(PRINTDLGW));

  prntdlg.lStructSize = sizeof(prntdlg);
  prntdlg.hwndOwner   = aHWnd;
  prntdlg.hDevMode    = autoDevMode.get();
  prntdlg.hDevNames   = hDevNames;
  prntdlg.hDC         = nullptr;
  prntdlg.Flags       = PD_ALLPAGES | PD_RETURNIC | 
                        PD_USEDEVMODECOPIESANDCOLLATE | PD_COLLATE;

  // if there is a current selection then enable the "Selection" radio button
  int16_t howToEnableFrameUI = nsIPrintSettings::kFrameEnableNone;
  bool isOn;
  aPrintSettings->GetPrintOptions(nsIPrintSettings::kEnableSelectionRB, &isOn);
  if (!isOn) {
    prntdlg.Flags |= PD_NOSELECTION;
  }
  aPrintSettings->GetHowToEnableFrameUI(&howToEnableFrameUI);

  int32_t pg = 1;
  aPrintSettings->GetStartPageRange(&pg);
  prntdlg.nFromPage           = pg;
  
  aPrintSettings->GetEndPageRange(&pg);
  prntdlg.nToPage             = pg;

  prntdlg.nMinPage            = 1;
  prntdlg.nMaxPage            = 0xFFFF;
  prntdlg.nCopies             = 1;
  prntdlg.lpfnSetupHook       = nullptr;
  prntdlg.lpSetupTemplateName = nullptr;
  prntdlg.hPrintTemplate      = nullptr;
  prntdlg.hSetupTemplate      = nullptr;

  prntdlg.hInstance           = nullptr;
  prntdlg.lpPrintTemplateName = nullptr;

  if (!ShouldExtendPrintDialog()) {
    prntdlg.lCustData         = 0;
    prntdlg.lpfnPrintHook     = nullptr;
  } else {
    // Set up print dialog "hook" procedure for extending the dialog
    prntdlg.lCustData         = (DWORD)howToEnableFrameUI;
    prntdlg.lpfnPrintHook     = (LPPRINTHOOKPROC)PrintHookProc;
    prntdlg.Flags            |= PD_ENABLEPRINTHOOK;
  }

  BOOL result;
  {
    mozilla::widget::WinUtils::AutoSystemDpiAware dpiAwareness;
    result = ::PrintDlgW(&prntdlg);
  }

  if (TRUE == result) {
    // check to make sure we don't have any nullptr pointers
    NS_ENSURE_TRUE(aPrintSettings && prntdlg.hDevMode, NS_ERROR_FAILURE);

    if (prntdlg.hDevNames == nullptr) {
      return NS_ERROR_FAILURE;
    }
    // Lock the deviceNames and check for nullptr
    DEVNAMES *devnames = (DEVNAMES *)::GlobalLock(prntdlg.hDevNames);
    if (devnames == nullptr) {
      return NS_ERROR_FAILURE;
    }

    char16_t* device = &(((char16_t *)devnames)[devnames->wDeviceOffset]);
    char16_t* driver = &(((char16_t *)devnames)[devnames->wDriverOffset]);

    // Check to see if the "Print To File" control is checked
    // then take the name from devNames and set it in the PrintSettings
    //
    // NOTE:
    // As per Microsoft SDK documentation the returned value offset from
    // devnames->wOutputOffset is either "FILE:" or nullptr
    // if the "Print To File" checkbox is checked it MUST be "FILE:"
    // We assert as an extra safety check.
    if (prntdlg.Flags & PD_PRINTTOFILE) {
      char16ptr_t fileName = &(((wchar_t *)devnames)[devnames->wOutputOffset]);
      NS_ASSERTION(wcscmp(fileName, L"FILE:") == 0, "FileName must be `FILE:`");
      aPrintSettings->SetToFileName(fileName);
      aPrintSettings->SetPrintToFile(true);
    } else {
      // clear "print to file" info
      aPrintSettings->SetPrintToFile(false);
      aPrintSettings->SetToFileName(nullptr);
    }

    nsCOMPtr<nsIPrintSettingsWin> psWin(do_QueryInterface(aPrintSettings));
    if (!psWin) {
      return NS_ERROR_FAILURE;
    }

    // Setup local Data members
    psWin->SetDeviceName(device);
    psWin->SetDriverName(driver);

#if defined(DEBUG_rods) || defined(DEBUG_dcone)
    wprintf(L"printer: driver %s, device %s  flags: %d\n", driver, device, prntdlg.Flags);
#endif
    // fill the print options with the info from the dialog

    aPrintSettings->SetPrinterName(device);

    if (prntdlg.Flags & PD_SELECTION) {
      aPrintSettings->SetPrintRange(nsIPrintSettings::kRangeSelection);

    } else if (prntdlg.Flags & PD_PAGENUMS) {
      aPrintSettings->SetPrintRange(nsIPrintSettings::kRangeSpecifiedPageRange);
      aPrintSettings->SetStartPageRange(prntdlg.nFromPage);
      aPrintSettings->SetEndPageRange(prntdlg.nToPage);

    } else { // (prntdlg.Flags & PD_ALLPAGES)
      aPrintSettings->SetPrintRange(nsIPrintSettings::kRangeAllPages);
    }

    if (howToEnableFrameUI != nsIPrintSettings::kFrameEnableNone) {
      // make sure the dialog got extended
      if (gDialogWasExtended) {
        // check to see about the frame radio buttons
        switch (gFrameSelectedRadioBtn) {
          case rad4: 
            aPrintSettings->SetPrintFrameType(nsIPrintSettings::kFramesAsIs);
            break;
          case rad5: 
            aPrintSettings->SetPrintFrameType(nsIPrintSettings::kSelectedFrame);
            break;
          case rad6: 
            aPrintSettings->SetPrintFrameType(nsIPrintSettings::kEachFrameSep);
            break;
        } // switch
      } else {
        // if it didn't get extended then have it default to printing
        // each frame separately
        aPrintSettings->SetPrintFrameType(nsIPrintSettings::kEachFrameSep);
      }
    } else {
      aPrintSettings->SetPrintFrameType(nsIPrintSettings::kNoFrames);
    }
    // Unlock DeviceNames
    ::GlobalUnlock(prntdlg.hDevNames);

    // Transfer the settings from the native data to the PrintSettings
    LPDEVMODEW devMode = (LPDEVMODEW)::GlobalLock(prntdlg.hDevMode);
    if (!devMode || !prntdlg.hDC) {
      return NS_ERROR_FAILURE;
    }
    psWin->SetDevMode(devMode); // copies DevMode
    psWin->CopyFromNative(prntdlg.hDC, devMode);
    ::GlobalUnlock(prntdlg.hDevMode);
    ::DeleteDC(prntdlg.hDC);

#if defined(DEBUG_rods) || defined(DEBUG_dcone)
    bool    printSelection = prntdlg.Flags & PD_SELECTION;
    bool    printAllPages  = prntdlg.Flags & PD_ALLPAGES;
    bool    printNumPages  = prntdlg.Flags & PD_PAGENUMS;
    int32_t fromPageNum    = 0;
    int32_t toPageNum      = 0;

    if (printNumPages) {
      fromPageNum = prntdlg.nFromPage;
      toPageNum   = prntdlg.nToPage;
    } 
    if (printSelection) {
      printf("Printing the selection\n");

    } else if (printAllPages) {
      printf("Printing all the pages\n");

    } else {
      printf("Printing from page no. %d to %d\n", fromPageNum, toPageNum);
    }
#endif
    
  } else {
    ::SetFocus(aHWnd);
    aPrintSettings->SetIsCancelled(true);
    return NS_ERROR_ABORT;
  }

  return NS_OK;
}