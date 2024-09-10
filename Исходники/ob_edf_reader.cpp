LRESULT CALLBACK EdfReaderDlgHandler( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    EDF_READEROBJ * st;
    int x;
    static int actchn;
    char strfloat[21];


    st = (EDF_READEROBJ *) actobject;
    if ((st==NULL)||(st->type!=OB_EDF_READER)) return(FALSE);


    switch( message )
    {
    case WM_INITDIALOG:
        actchn=0;
        update_header(hDlg,&st->header);
        update_channelcombo(hDlg, st->channel, st->header.channels);
        update_channel(hDlg,st->channel,actchn);
        update_state(hDlg,st->state);

        sprintf(strfloat,"%.2f",(float)st->offset/(float)PACKETSPERSECOND);
        SetDlgItemText(hDlg,IDC_OFFSET,strfloat);

        if (st->edffile!=INVALID_HANDLE_VALUE)
            SetDlgItemText(hDlg, IDC_EDFFILE, st->filename);
        else
            SetDlgItemText(hDlg, IDC_EDFFILE, "none");


        return TRUE;

    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {

        case IDC_SELECT:

            st->filename[0]=0;
            if ((st->edffile=open_edf_file(&st->header,st->channel,st->filename))==INVALID_HANDLE_VALUE) st->state=0;
            else if (st->header.channels==0)
            {
                SendMessage(hDlg,WM_COMMAND,IDC_CLOSE,0);
                report("EDF-File contained no channel inforamtion, file closed.");
                st->state=0;
            }
            else st->state=1;

            update_state(hDlg,st->state);
            if (!st->state) break;
            st->calc_session_length();
            get_session_length();
            //set_session_pos(0);
            st->session_pos(0);
            st->packetcount=0;
            st->sampos=0;

            if (st->outports!=st->header.channels)
            {
                for (x=0; x<MAX_CONNECTS; x++)
                {
                    st->out[x].from_port=-1;
                    st->out[x].to_port=-1;
                    st->out[x].to_object=-1;
                }
                for (x=0; x<MAX_PORTS; x++)
                    st->out_ports[x].out_name[0]=0;
            }
            st->outports=st->header.channels;
            st->height=CON_START+st->outports*CON_HEIGHT+5;

            update_header(hDlg,&st->header);
            update_channelcombo(hDlg, st->channel, st->header.channels);
            update_channel(hDlg,st->channel,actchn);
            st->get_captions();
            update_dimensions();
            SetDlgItemText(hDlg, IDC_EDFFILE, st->filename);
            EnableWindow(GetDlgItem(hDlg, IDC_CLOSE), TRUE);
            EnableWindow(GetDlgItem(hDlg, IDC_SELECT), FALSE);
            InvalidateRect(ghWndDesign,NULL,TRUE);

            break;

        case IDC_CLOSE:
            st->state=0;
            update_state(hDlg,st->state);
            SetDlgItemText(hDlg, IDC_EDFFILE, "none");
            add_to_listbox(hDlg,IDC_LIST, "file closed.");
            strcpy(st->filename,"none");
            if (st->edffile==INVALID_HANDLE_VALUE) break;
            CloseHandle(st->edffile);
            st->edffile=INVALID_HANDLE_VALUE;
            get_session_length();
            InvalidateRect(ghWndDesign,NULL,TRUE);

            break;
        case IDC_APPLYOFFSET:
            GetDlgItemText(hDlg, IDC_OFFSET, strfloat, 20);
            st->offset = (int)((float)atof(strfloat) * (float) PACKETSPERSECOND);
            st->calc_session_length();
            get_session_length();
            break;
        case IDC_CHANNELCOMBO:
            if (HIWORD(wParam)==CBN_SELCHANGE)
            {
                get_channel(hDlg, st->channel, actchn);
                actchn=SendMessage(GetDlgItem(hDlg, IDC_CHANNELCOMBO), CB_GETCURSEL , 0, 0);
                update_channel(hDlg, st->channel,actchn);
            }
            break;

        }
        return TRUE;
    case WM_SIZE:
    case WM_MOVE:
        update_toolbox_position(hDlg);
        break;
        return TRUE;
    }
    return FALSE;
}