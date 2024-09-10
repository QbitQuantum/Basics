/*
--------------------------------------------------------------------------
MainWndProc

This is the main procedure which processes each message.

Inputs:
  hwnd     - The handle to the parent window
  message  - Message sent from MainWndProc
  wParam   - Command from MainWndProc
  lParam   - Additional message information

Outputs:
  Used as an boolean for the current message
--------------------------------------------------------------------------
*/
int FAR PASCAL MainWndProc(HWND hwnd, WORD message, WORD wParam, LONG lParam)
{
  WORD           wTabStop;

  switch (message)
  {
    case WM_INITDIALOG:
      hWnd = hwnd;
      hWndPScroll = GetDlgItem(hWnd, IDD_PSCROLL);
      hWndCScroll = GetDlgItem(hWnd, IDD_CSCROLL);
      hWndRList   = GetDlgItem(hWnd, IDD_RLIST);
      of_course.lStructSize       = sizeof(OPENFILENAME);
      of_player.lStructSize       = sizeof(OPENFILENAME);
      of_course.hwndOwner         = hWnd;
      of_player.hwndOwner         = hWnd;
      of_course.lpstrFilter       = "Course(*.GLC)\0*.glc\0";
      of_player.lpstrFilter       = "Player(*.GLP)\0*.glp\0";
      of_course.lpstrCustomFilter = (LPSTR) NULL;
      of_player.lpstrCustomFilter = (LPSTR) NULL;
      of_course.nMaxCustFilter    = 0L;
      of_player.nMaxCustFilter    = 0L;
      of_course.nFilterIndex      = 0L;
      of_player.nFilterIndex      = 0L;
      of_course.lpstrFile         = szFileC;
      of_player.lpstrFile         = szFileP;
      of_course.nMaxFile          = sizeof(szFileC);
      of_player.nMaxFile          = sizeof(szFileP);
      of_course.lpstrFileTitle    = szFileTitleC;
      of_player.lpstrFileTitle    = szFileTitleP;
      of_course.nMaxFileTitle     = sizeof(szFileTitleC);
      of_player.nMaxFileTitle     = sizeof(szFileTitleP);
      of_course.lpstrInitialDir   = NULL;
      of_player.lpstrInitialDir   = NULL;
      of_course.nFileOffset       = 0;
      of_player.nFileOffset       = 0;
      of_course.nFileExtension    = 0;
      of_player.nFileExtension    = 0;
      of_course.lpstrDefExt       = "GLC";
      of_player.lpstrDefExt       = "GLP";
      p_index = r_index = r_last = c_index = 0;
      players.player_numb = courses.course_numb = -1;
      SetClassWord(hWnd, GCW_HICON, LoadIcon(hInst, "GOLFICON"));
      wTabStop = 4 + TAB_PIXEL_SETTING / (LOWORD(GetDialogBaseUnits()) / 4);
      SendMessage(hWndRList, LB_SETTABSTOPS, 1, (LONG) (WORD FAR *) &wTabStop);
      DoCaption(hWnd, szFileTitleP, szFileTitleC);
      return TRUE;

    case WM_INITMENU:  /* Set the menu items */
      DoMenu(wParam, &players, &courses, p_index, hWndRList);
      return TRUE;

    case WM_HSCROLL:  /* move to next or previous record */
      if (HIWORD(lParam) == hWndPScroll)
	move_player(hWnd, hWndRList, wParam, &players, &p_index, &r_index, &r_last);
      else if (HIWORD(lParam) == hWndCScroll)
	move_course(hWnd, wParam, &courses, &c_index);
      return TRUE;

    case WM_COMMAND:
      return CommandHandler(wParam, lParam);

    case WM_QUERYENDSESSION:
      if (bNeedSaveP && IDCANCEL == AskAboutSave(hWnd, szFileTitleP, PLAYER_MARKER))
	return 1;
      if (bNeedSaveC && IDCANCEL == AskAboutSave(hWnd, szFileTitleC, COURSE_MARKER))
	return 1;
      EndDialog(hWnd, NULL);
      return 0;

    case WM_CLOSE:  /* Check if file has been saved and close window */
      if (bNeedSaveP && IDCANCEL == AskAboutSave(hWnd, szFileTitleP, PLAYER_MARKER))
	return 0;
      if (bNeedSaveC && IDCANCEL == AskAboutSave(hWnd, szFileTitleC, COURSE_MARKER))
	return 0;
      EndDialog(hWnd, NULL);
      return 1;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    default:
      return FALSE;
  } /* switch (message) */
} /* MainWndProc */