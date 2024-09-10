static VOID
SetImageList(HWND hwnd)
{
    HIMAGELIST hImageList;

    hImageList = ImageList_Create(16, 16, ILC_MASK | ILC_COLOR24, 1, 1);

    if (!hImageList)
    {
        MessageBox(hwnd, _T("ImageList it is not created!"), NULL, MB_OK);
        return;
    }

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_PLAYICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_STOPICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_EJECTICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_BACKWARDICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_SEEKBACKICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_SEEKFORWICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_AddMasked(hImageList,
                        LoadImage(hInstance, MAKEINTRESOURCE(IDB_FORWARDICON), IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR),
                        RGB(255, 255, 255));

    ImageList_Destroy((HIMAGELIST)SendMessage(hToolBar,
                                              TB_SETIMAGELIST,
                                              0,
                                              (LPARAM)hImageList));
}