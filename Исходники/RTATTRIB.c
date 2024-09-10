void RTSaveFields(int pieceNumber)
{
  int nI = pieceNumber - 1;

  SendMessage(hCtlMINONTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].minOnTime = cTime(tempString);
  SendMessage(hCtlMAXONTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].maxOnTime = cTime(tempString);
  SendMessage(hCtlMINOFFTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].minOffTime = cTime(tempString);
  SendMessage(hCtlMAXOFFTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].maxOffTime = cTime(tempString);
  SendMessage(hCtlMINPAYTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].minPayTime = thhmm(tempString);
  SendMessage(hCtlMAXPAYTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].maxPayTime = thhmm(tempString);
  SendMessage(hCtlMINPIECESIZE, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].minPieceSize = thhmm(tempString);
  SendMessage(hCtlDESPIECESIZE, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].desPieceSize = thhmm(tempString);
  SendMessage(hCtlMAXPIECESIZE, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].maxPieceSize = thhmm(tempString);
  SendMessage(hCtlMINBREAKTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].minBreakTime = thhmm(tempString);
  SendMessage(hCtlDESBREAKTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].desBreakTime = thhmm(tempString);
  SendMessage(hCtlMAXBREAKTIME, WM_GETTEXT,
        (WPARAM)TEMPSTRING_LENGTH, (LONG)(LPSTR)tempString);
  localRT.PIECE[nI].maxBreakTime = thhmm(tempString);
  localRT.PIECE[nI].flags = 0;
  if(SendMessage(hCtlTRAVELINCLUDEDINMIN, BM_GETCHECK, (WPARAM)0, (LPARAM)0))
    localRT.PIECE[nI].flags |= PIECEFLAGS_TRAVELINCLUDEDINMIN;
  if(SendMessage(hCtlTRAVELINCLUDEDINMAX, BM_GETCHECK, (WPARAM)0, (LPARAM)0))
    localRT.PIECE[nI].flags |= PIECEFLAGS_TRAVELINCLUDEDINMAX;
  if(SendMessage(hCtlPAYONLYAPPLIES, BM_GETCHECK, (WPARAM)0, (LPARAM)0))
    localRT.PIECE[nI].flags |= PIECEFLAGS_PAYONLYAPPLIES;
}