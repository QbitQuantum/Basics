wm_char(TableUI *tui, unsigned wparam) {

    switch (wparam) {
    
    case 'F' - 'A' + 1:
        if (!dlg) {
            tui->find_dialog.hwndOwner = tui->window;
            dlg = FindTextA(&tui->find_dialog);
        }
        break;
    
    case 'L' - 'A' + 1:                         /* Delete Row */
        if (IsShiftDown()) command(tui, CmdDeleteRow);
        else command(tui, CmdClearRow);
        break;
        
    case 'N' - 'A' + 1:                           /* New File */
        command(tui, CmdClearFile);
        break;
        
    case 'O' - 'A' + 1:                          /* Open file */
        if (GetOpenFileName(&tui->open_dialog))        
            command(tui, CmdOpenFile);
        break;
    
    case 'S' - 'A' + 1:                          /* Save File */
        if (tui->filename[0] || GetSaveFileName(&tui->open_dialog))
            command(tui, CmdSaveFile);
        break;
    
    case 'C' - 'A' + 1:                               /* Copy */
        command(tui, CmdCopy);
        break;
    
    case 'X' - 'A' + 1:                                /* Cut */
        command(tui, IsShiftDown()? CmdCutDelete: CmdCutClear);
        break;
    
    case 'V' - 'A' + 1:                              /* Paste */
        command(tui, CmdPaste);
        break;
        
    case VK_RETURN:                                  /* Enter */
        command(tui, IsShiftDown()? CmdUnReturn: CmdReturn);
        break;
        
    case VK_TAB:                                       /* Tab */
        command(tui, IsShiftDown()? CmdUnTab: CmdTab);
        break;
    
    default:                                /* Auto-edit cell */
        /* Don't drop the char; forward it to the editor */
        command(tui, CmdEditCellClear);
        SendMessage(tui->edit, WM_CHAR, wparam, 0); 
        break;
    }
    return 1;
}