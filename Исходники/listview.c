static BOOL InitListViewImageLists(HWND hwndLV)
{
    HIMAGELIST himl;  /* handle to image list  */
    HICON hico;       /* handle to icon  */

    /* Create the image list.  */
    if ((himl = ImageList_Create(CX_ICON, CY_ICON,
                                 ILC_MASK, 0, NUM_ICONS)) == NULL)
    {
        return FALSE;
    }

    hico = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_BIN));
    Image_Bin = ImageList_AddIcon(himl, hico);

    hico = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_STRING));
    Image_String = ImageList_AddIcon(himl, hico);

    /* Fail if not all of the images were added.  */
    if (ImageList_GetImageCount(himl) < NUM_ICONS)
    {
        return FALSE;
    }

    /* Associate the image list with the tree view control.  */
    (void)ListView_SetImageList(hwndLV, himl, LVSIL_SMALL);

    return TRUE;
}