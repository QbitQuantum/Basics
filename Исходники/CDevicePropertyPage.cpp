//------------------------------------------------------------------------------
// CDevicePropertyPage::GetIconFromItem [STATIC FUNC]
//
//      Gets a handle to the icon of the shell item. phIcon needs to be cleaned
//      up with DestroyIcon() when done. 
//------------------------------------------------------------------------------
HRESULT CDevicePropertyPage::GetIconFromItem(
    __in IShellItem* pShellItem, 
    __in int iImageList, 
    __out HICON* phIcon
    )
{
    HRESULT         hr              = S_OK;
    int             iIcon           = 0;
    PITEMID_CHILD   pidl            = NULL;
    IImageList*     pImageList      = NULL;
    IParentAndItem* pParentAndItem  = NULL;
    IShellFolder*   pShellFolder    = NULL;

    *phIcon = NULL;

    hr = pShellItem->QueryInterface( &pParentAndItem );

    if( S_OK == hr )
    {
        hr = pParentAndItem->GetParentAndItem( NULL, &pShellFolder, &pidl );
    }

    if( S_OK == hr )
    {
        hr = SHGetImageList(
            iImageList,
            __uuidof(IImageList),
            reinterpret_cast<void**>(&pImageList)
            );
    }

    if( S_OK == hr )
    {
        iIcon = SHMapPIDLToSystemImageListIndex( pShellFolder, pidl, NULL );
        hr = pImageList->GetIcon( iIcon, 0, phIcon );
    }

    //
    // Cleanup
    //
    if( NULL != pImageList )
    {
        pImageList->Release();
    }
    if( NULL != pidl )
    {
        ILFree( pidl );
    }
    if( NULL != pShellFolder )
    {
        pShellFolder->Release();
    }
    if( NULL != pParentAndItem )
    {
        pParentAndItem->Release();
    }

    return hr;
}// CDevicePropertyPage::GetIconFromItem