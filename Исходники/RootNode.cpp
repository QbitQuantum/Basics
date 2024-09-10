bool
CRootNode::SetupNode()
{

    // Load the bitmap we'll be using as the root image
    HBITMAP hRootImage;
    hRootImage = LoadBitmapW(g_hThisInstance,
                             MAKEINTRESOURCEW(IDB_ROOT_IMAGE));
    if (hRootImage == NULL) return FALSE;

    // Add this bitmap to the device image list. This is a bit hacky, but it's safe
    m_ClassImage = ImageList_Add(m_ImageListData->ImageList,
                                 hRootImage,
                                 NULL);
    DeleteObject(hRootImage);


    // Get the root instance 
    CONFIGRET cr;
    cr = CM_Locate_DevNodeW(&m_DevInst,
                            NULL,
                            CM_LOCATE_DEVNODE_NORMAL);
    if (cr != CR_SUCCESS)
    {
        return false;
    }

    // The root name is the computer name 
    DWORD Size = DISPLAY_NAME_LEN;
    GetComputerNameW(m_DisplayName, &Size);

    return true;
}