HWND CreateStackWindow(void)
{
    if (hwndStack)
    {
        SendMessage(hwndStack, WM_SETFOCUS, 0, 0);
    }
    else
    {
        HBITMAP bitmap;
        bitmap = LoadBitmap(hInstance, "ID_TAG");
        ChangeBitmapColor(bitmap, 0xc0c0c0, RetrieveSysColor(COLOR_WINDOW));
        tagImageList = ImageList_Create(16, 16, ILC_COLOR24, ILEDIT_IMAGECOUNT, 0);
        ImageList_Add(tagImageList, bitmap, NULL);
        DeleteObject(bitmap);
        hwndStack = CreateDockableWindow(DID_STACKWND, szStackClassName, szStackTitle, hInstance, 30 * 8, 19 * 8);
    }
    return hwndStack;
}