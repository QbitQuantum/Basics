VOID ClipboardSample(
    __in HWND hWindow)
{    
    //
    // Call GetUpdatedClipboardFormats to get the number of clipboard formats,
    // without getting the clipboard formats themselves
    //
    UINT numberOfClipboardFormats = 0;
    GetUpdatedClipboardFormats(NULL, 0, &numberOfClipboardFormats);
    _tprintf(_T("GetUpdatedClipboardFormats: initial number of clipboard formats: %d\n\n"), 
        numberOfClipboardFormats);
    
    //
    // Add the sample window to the list of clipboard format listeners
    //
    if (AddClipboardFormatListener(hWindow))
    {
        _tprintf(_T("AddClipboardFormatListener: Sample window added to list of clipboard format listeners\n\n"));
    }

    //
    // Add bitmap data to the clipboard, which will generate a WM_CLIPBOARDUPDATE message
    //
    AddBitmapDataToClipboard(hWindow);
    
    //
    // Peek for a WM_CLIPBOARDUPDATE message
    //
    MSG message = {0};
    PeekMessage(&message, hWindow, WM_CLIPBOARDUPDATE, WM_CLIPBOARDUPDATE, PM_REMOVE);
    if (message.message == WM_CLIPBOARDUPDATE)
    {
        _tprintf(_T("Sample window received WM_CLIPBOARDUPDATE message\n\n"));
    }

    //
    // Call GetUpdatedClipboardFormats, getting the list of formats
    //
    UINT* clipboardFormats = new UINT[numberOfClipboardFormats + 10];
    if (GetUpdatedClipboardFormats(
        clipboardFormats, 
        numberOfClipboardFormats + 10, 
        &numberOfClipboardFormats))
    {
        _tprintf(_T("GetUpdatedClipboardFormats: number of clipboard formats written: %d\n\n"),
            numberOfClipboardFormats);
    }

    //
    // Remove the sample window from the list of clipboard format listeners
    //
    if (RemoveClipboardFormatListener(hWindow))
    {
        _tprintf(_T("RemoveClipboardFormatListener: sample window removed from list of clipboard format change listeners\n\n"));
    }

    //
    // Add bitmap data to the clipboard, which will generate a WM_CLIPBOARDUPDATE message
    //
    AddBitmapDataToClipboard(hWindow);

    //
    // Peek for a WM_CLIPBOARDUPDATE message
    //
    message.message = 0;
    PeekMessage(&message, hWindow, WM_CLIPBOARDUPDATE, WM_CLIPBOARDUPDATE, PM_REMOVE);
    if (message.message != WM_CLIPBOARDUPDATE)
    {
        _tprintf(_T("Sample window did NOT receive the WM_CLIPBOARDUPDATE message\n\n"));
    }

    DestroyWindow(hWindow);
	delete [] clipboardFormats;
}