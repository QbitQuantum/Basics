INT_PTR CALLBACK prg2wav_dialog_proc(HWND hwndDlg,      //handle to dialog box
                                     UINT uMsg, //message
                                     WPARAM wParam,     //first message parameter
                                     LPARAM lParam      // second message parameter
  ){
  switch (uMsg) {
  case WM_INITDIALOG:
    CheckRadioButton(hwndDlg, IDC_FAST, IDC_SLOW, IDC_FAST);
    CheckRadioButton(hwndDlg, IDC_TO_TAP, IDC_TO_SOUND, IDC_TO_TAP);
    if (audiotap_startup_status.audiofile_init_status != LIBRARY_OK
     || audiotap_startup_status.tapdecoder_init_status != LIBRARY_OK)
      EnableWindow(GetDlgItem(hwndDlg, IDC_TO_WAV), FALSE);
    if (audiotap_startup_status.portaudio_init_status != LIBRARY_OK
     || audiotap_startup_status.tapdecoder_init_status != LIBRARY_OK)
      EnableWindow(GetDlgItem(hwndDlg, IDC_TO_SOUND), FALSE);
    SetDlgItemInt(hwndDlg, IDC_FREQ, 44100, FALSE);
    SetDlgItemInt(hwndDlg, IDC_VOL, 254, FALSE);
    SendMessageA(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_ADDSTRING, 0,
      (LPARAM) "C64 PAL");
    SendMessageA(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_ADDSTRING, 0,
      (LPARAM) "C64 NTSC");
    SendMessageA(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_ADDSTRING, 0,
      (LPARAM) "VIC20 PAL");
    SendMessageA(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_ADDSTRING, 0,
      (LPARAM) "VIC20 NTSC");
    SendMessageA(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_ADDSTRING, 0,
      (LPARAM) "C16 PAL");
    SendMessageA(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_ADDSTRING, 0,
      (LPARAM) "C16 NTSC");
    SendMessage(GetDlgItem(hwndDlg, IDC_MACHINE_TO), CB_SETCURSEL, 0, 0);
    SendMessageA(GetDlgItem(hwndDlg, IDC_WAVEFORM), CB_ADDSTRING, 0,
      (LPARAM) "Triangle");
    SendMessageA(GetDlgItem(hwndDlg, IDC_WAVEFORM), CB_ADDSTRING, 0,
      (LPARAM) "Square");
    SendMessageA(GetDlgItem(hwndDlg, IDC_WAVEFORM), CB_ADDSTRING, 0,
      (LPARAM) "Sine");
    SendMessageA(GetDlgItem(hwndDlg, IDC_WAVEFORM), CB_SETCURSEL, 1, 0);
    SendMessageA(GetDlgItem(hwndDlg, IDC_THRESHOLD_SPIN), UDM_SETRANGE, 
      0, MAKELONG(1600, 102));
    SendMessage(GetDlgItem(hwndDlg, IDC_THRESHOLD_SPIN), UDM_SETPOS, 
      0, 263);
    return TRUE;
  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case IDC_FAST:
      EnableWindow(GetDlgItem(hwndDlg, IDC_THRESHOLD), TRUE);
      return TRUE;
    case IDC_SLOW:
      EnableWindow(GetDlgItem(hwndDlg, IDC_THRESHOLD), FALSE);
      return TRUE;
    case IDC_TO_TAP:
      EnableWindow(GetDlgItem(hwndDlg, IDC_INVERTED), FALSE);
      EnableWindow(GetDlgItem(hwndDlg, IDC_FREQ), FALSE);
      EnableWindow(GetDlgItem(hwndDlg, IDC_VOL), FALSE);
      EnableWindow(GetDlgItem(hwndDlg, IDC_WAVEFORM), FALSE);
      return TRUE;
    case IDC_TO_WAV:
    case IDC_TO_SOUND:
      EnableWindow(GetDlgItem(hwndDlg, IDC_INVERTED), TRUE);
      EnableWindow(GetDlgItem(hwndDlg, IDC_FREQ), TRUE);
      EnableWindow(GetDlgItem(hwndDlg, IDC_VOL), TRUE);
      EnableWindow(GetDlgItem(hwndDlg, IDC_WAVEFORM), TRUE);
      return TRUE;
    case IDOK:
      choose_file(hwndDlg);
      return TRUE;
    case IDCANCEL:
      EndDialog(hwndDlg, 0);
      return TRUE;
    default:
      return FALSE;
    }
  case WM_DROPFILES:
    {
      UINT numfiles = DragQueryFileA((HDROP)wParam, 0xFFFFFFFF, NULL, 0);
      UINT i;
      struct prg2wav_params params;
      struct simple_block_list_element **current_block = &params.program;

      params.program = NULL;

      for (i = 0; i < numfiles; i++)
      {
        UINT filenamesize = DragQueryFile((HDROP)wParam, i, NULL, 0);
        LPSTR filename;
        FILE* fd;
        filenamesize++; /* for the null termination */
        filename = (LPSTR)malloc(filenamesize);
        DragQueryFileA((HDROP)wParam, i, filename, filenamesize);
        if ((fd = fopen(filename, "rb")) != NULL){
          struct simple_block_list_element **new_current_block = add_all_entries_from_file(current_block, fd);
          if (detect_type(fd) == prg)
            put_filename_in_entryname(filename, (*current_block)->block.info.name);
          fclose(fd);
          current_block = new_current_block;
        }
        free(filename);
      }
      DragFinish((HDROP)wParam);
      if (params.program != NULL)
        choose_destination_file_and_convert(hwndDlg, &params);
    }
    return TRUE;
#ifdef HAVE_HTMLHELP
  case WM_HELP:
    HtmlHelpA(hwndDlg, "docs\\wavprg.chm::/prg2wav_main.htm",
              HH_DISPLAY_TOPIC, 0);
    return TRUE;
#endif
  default:
    return FALSE;
  }
}