LRESULT CSetPgHilight::OnInitDialog(HWND hDlg, bool abInitial)
{
    // Hyperlinks & compiler errors
    checkDlgButton(hDlg, cbFarGotoEditor, gpSet->isFarGotoEditor);
    UINT VkMod = gpSet->GetHotkeyById(vkFarGotoEditorVk);
    CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbFarGotoEditorVk), CSetDlgLists::eKeysAct, VkMod, false);

    LPCWSTR ppszDefEditors[] = {
        HI_GOTO_EDITOR_FAR,    // Far Manager
        HI_GOTO_EDITOR_SCITE,  // SciTE (Scintilla)
        HI_GOTO_EDITOR_NPADP,  // Notepad++
        HI_GOTO_EDITOR_VIMW,   // Vim, official, using Windows paths
        HI_GOTO_EDITOR_SUBLM,  // Sublime text
        HI_GOTO_EDITOR_CMD,    // Just ‘start’ highlighted file via cmd.exe
        HI_GOTO_EDITOR_CMD_NC, // Just ‘start’ highlighted file via cmd.exe, same as prev. but without close confirmation
        NULL
    };
    CSetDlgLists::FillCBList(GetDlgItem(hDlg, lbGotoEditorCmd), abInitial, ppszDefEditors, gpSet->sFarGotoEditor);

    // Highlight full row/column under mouse cursor
    checkDlgButton(hDlg, cbHighlightMouseRow, gpSet->isHighlightMouseRow);
    checkDlgButton(hDlg, cbHighlightMouseCol, gpSet->isHighlightMouseCol);

    // This modifier (lbFarGotoEditorVk) is not checked
    // CheckSelectionModifiers(hDlg);

    return 0;
}