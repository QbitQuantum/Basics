static void test_removeimage(void)
{
    static const BYTE bits[32];
    HWND hwTab;
    INT i;
    TCITEM item;
    HICON hicon;
    HIMAGELIST himl = ImageList_Create(16, 16, ILC_COLOR, 3, 4);

    hicon = CreateIcon(NULL, 16, 16, 1, 1, bits, bits);
    ImageList_AddIcon(himl, hicon);
    ImageList_AddIcon(himl, hicon);
    ImageList_AddIcon(himl, hicon);

    hwTab = create_tabcontrol(TCS_FIXEDWIDTH, TCIF_TEXT|TCIF_IMAGE);
    SendMessage(hwTab, TCM_SETIMAGELIST, 0, (LPARAM)himl);

    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_IMAGE;

    for(i = 0; i < 3; i++) {
        SendMessage(hwTab, TCM_GETITEM, i, (LPARAM)&item);
        expect(i, item.iImage);
    }

    /* remove image middle image */
    SendMessage(hwTab, TCM_REMOVEIMAGE, 1, 0);
    expect(2, ImageList_GetImageCount(himl));
    item.iImage = -1;
    SendMessage(hwTab, TCM_GETITEM, 0, (LPARAM)&item);
    expect(0, item.iImage);
    item.iImage = 0;
    SendMessage(hwTab, TCM_GETITEM, 1, (LPARAM)&item);
    expect(-1, item.iImage);
    item.iImage = 0;
    SendMessage(hwTab, TCM_GETITEM, 2, (LPARAM)&item);
    expect(1, item.iImage);
    /* remove first image */
    SendMessage(hwTab, TCM_REMOVEIMAGE, 0, 0);
    expect(1, ImageList_GetImageCount(himl));
    item.iImage = 0;
    SendMessage(hwTab, TCM_GETITEM, 0, (LPARAM)&item);
    expect(-1, item.iImage);
    item.iImage = 0;
    SendMessage(hwTab, TCM_GETITEM, 1, (LPARAM)&item);
    expect(-1, item.iImage);
    item.iImage = -1;
    SendMessage(hwTab, TCM_GETITEM, 2, (LPARAM)&item);
    expect(0, item.iImage);
    /* remove the last one */
    SendMessage(hwTab, TCM_REMOVEIMAGE, 0, 0);
    expect(0, ImageList_GetImageCount(himl));
    for(i = 0; i < 3; i++) {
        item.iImage = 0;
        SendMessage(hwTab, TCM_GETITEM, i, (LPARAM)&item);
        expect(-1, item.iImage);
    }

    DestroyWindow(hwTab);
    ImageList_Destroy(himl);
    DestroyIcon(hicon);
}