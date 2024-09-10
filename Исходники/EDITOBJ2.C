int ExitObjectClassEditor(HWND hWndDlg, WORD wType, GLOBALHANDLE hObj)
{
    LPOBJECT lpTempObj;
    LISTID idRenamedNewNames, idRenamedOldNames, idDeletedSlots;

    /* See if item need to be saved */
    if (!QueryEditorSaveItem(hWndDlg, wType, hObj, EXIT))
        return FALSE;

    /* Clean up left over items on the temporary object */
    lpTempObj = (LPOBJECT) GLOBALLOCK(hObj);
    Kpp__ResetCO(wType, (LPCLASS) lpTempObj);
    GLOBALUNLOCK(hObj);
    GLOBALFREE(hObj);

    /* Take care of deleteslots and renamed ones */
    if (idDeletedSlots = GetProp(hWndDlg, (LPSTR) pDeletedSlots))
    {
        KppDeleteList(idDeletedSlots);
        SetProp(hWndDlg, (LPSTR) pDeletedSlots, NULLID);
    }

    if (idRenamedOldNames = GetProp(hWndDlg, (LPSTR) pRenamedOldNames))
    {
        KppDeleteList(idRenamedOldNames);
        SetProp(hWndDlg, (LPSTR) pRenamedOldNames, NULLID);
    }

    if (idRenamedNewNames = GetProp(hWndDlg, (LPSTR) pRenamedNewNames))
    {
        KppDeleteList(idRenamedNewNames);
        SetProp(hWndDlg, (LPSTR) pRenamedNewNames, NULLID);
    }

    /* Update the list of currently open object/class editors */
    if (wType == OBJECT && idObjectEditors)
    {
        KppDeleteElem(idObjectEditors, hWndDlg, 0);
        if (!KppListLen(idObjectEditors))
        {
            KppDeleteList(idObjectEditors);
            idObjectEditors = NULLID;
        }
    }
    else if (idClassEditors)
    {
        KppDeleteElem(idClassEditors, hWndDlg, 0);
        if (!KppListLen(idClassEditors))
        {
            KppDeleteList(idClassEditors);
            idClassEditors = NULLID;
        }
    }

    KppRemoveFromWindowMenuCB(hWndDlg);

    /* Remove all properties */
    if (wType == OBJECT)
        RemoveProp(hWndDlg, (LPSTR) "hObj");
    else
        RemoveProp(hWndDlg, (LPSTR) "hClass");
    RemoveProp(hWndDlg, (LPSTR) pActualItem);
    RemoveProp(hWndDlg, (LPSTR) pModified);
    RemoveProp(hWndDlg, (LPSTR) pSlotEditors);
    RemoveProp(hWndDlg, (LPSTR) pMethodEditors);
    RemoveProp(hWndDlg, (LPSTR) pDeletedSlots);
    RemoveProp(hWndDlg, (LPSTR) pRenamedOldNames);
    RemoveProp(hWndDlg, (LPSTR) pRenamedNewNames);

    return TRUE;
}