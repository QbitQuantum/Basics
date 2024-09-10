jobject COMFileChooser_Show(HWND owner, LPCTSTR folder, LPCTSTR filename, LPCTSTR title, jint type,
                                 jboolean multipleMode, jobjectArray jFilters, jint defaultFilterIndex)
{
    OLEHolder _ole_;
    IFileDialogPtr pDialog;

    OLE_TRY

    switch(type) {
        case com_sun_glass_ui_CommonDialogs_Type_OPEN:
            OLE_HRT( ::CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                                        IID_IFileOpenDialog, (void**)&pDialog) );

            if (multipleMode == TRUE) {
                DWORD dwOptions = 0;
                OLE_HRT( pDialog->GetOptions(&dwOptions) );
                dwOptions |= FOS_ALLOWMULTISELECT;
                OLE_HRT( pDialog->SetOptions(dwOptions) );
            }

            break;
        case com_sun_glass_ui_CommonDialogs_Type_SAVE:
            OLE_HRT( ::CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
                                        IID_IFileSaveDialog, (void**)&pDialog) );
            break;
    }

    if (folder) {
        IShellItemPtr pItem;
        OLE_HRT( SHCreateItemFromParsingName((PCWSTR)folder, NULL,
                                             IID_IShellItem, (void **)&pItem) );
        if (pItem) {
            OLE_HRT( pDialog->SetFolder( pItem ) );
        }
    }

    if (type == com_sun_glass_ui_CommonDialogs_Type_SAVE && filename && *filename) {
        OLE_HRT( pDialog->SetFileName(filename); );