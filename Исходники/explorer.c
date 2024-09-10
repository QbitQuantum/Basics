static LRESULT explorer_on_notify(explorer_info* info,NMHDR* notification)
{
    WINE_TRACE("code=%i\n",notification->code);
    switch(notification->code)
    {
    case CBEN_BEGINEDIT:
        {
            WCHAR path[MAX_PATH];
            HWND edit_ctrl = (HWND)SendMessageW(notification->hwndFrom,
                                                CBEM_GETEDITCONTROL,0,0);
            SHGetPathFromIDListW(info->pidl,path);
            SetWindowTextW(edit_ctrl,path);
            break;
        }
    case CBEN_ENDEDITA:
        {
            NMCBEENDEDITA *edit_info_a = (NMCBEENDEDITA*)notification;
            NMCBEENDEDITW edit_info_w;
            edit_info_w.hdr = edit_info_a->hdr;
            edit_info_w.fChanged = edit_info_a->fChanged;
            edit_info_w.iNewSelection = edit_info_a->iNewSelection;
            MultiByteToWideChar(CP_ACP,0,edit_info_a->szText,-1,
                                edit_info_w.szText,CBEMAXSTRLEN);
            edit_info_w.iWhy = edit_info_a->iWhy;
            return explorer_on_end_edit(info,&edit_info_w);
        }
    case CBEN_ENDEDITW:
        return explorer_on_end_edit(info,(NMCBEENDEDITW*)notification);
    case CBEN_DELETEITEM:
        {
            NMCOMBOBOXEXW *entry = (NMCOMBOBOXEXW*)notification;
            if(entry->ceItem.lParam)
                ILFree((LPITEMIDLIST)entry->ceItem.lParam);
            break;
        }
    case RBN_AUTOSIZE:
        return update_rebar_size(info,(NMRBAUTOSIZE*)notification);
    default:
        break;
    }
    return 0;
}