PassRefPtr<Clipboard> Editor::newGeneralClipboard(ClipboardAccessPolicy policy, Frame* frame)
{
    COMPtr<IDataObject> clipboardData;
#if !OS(WINCE)
    if (!SUCCEEDED(OleGetClipboard(&clipboardData)))
        clipboardData = 0;
#endif

    return ClipboardWin::create(Clipboard::CopyAndPaste, clipboardData.get(), policy, frame);
}