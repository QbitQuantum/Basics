int HIDPI_ImageList_ReplaceIcon(HIMAGELIST himl, int i, HICON hicon)
{
    int iRet;
    int cxIcon, cyIcon;
    HICON hiconStretched;

    ImageList_GetIconSize(himl, &cxIcon, &cyIcon);
    HIDPI_StretchIcon_Internal(hicon, &hiconStretched, cxIcon, cyIcon);
    if (hiconStretched != NULL)
    {
        iRet = ImageList_ReplaceIcon(himl, i, hiconStretched);
        DestroyIcon(hiconStretched);
    }
    else
    {
        iRet = ImageList_ReplaceIcon(himl, i, hicon);
    }

    return iRet;
}