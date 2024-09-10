static intptr_t WINAPI MainDialogProc(HANDLE hDlg,intptr_t Msg,intptr_t Param1,void* Param2)
{
  BoardParams* DlgParams=(BoardParams*)Info.SendDlgMessage(hDlg,DM_GETDLGDATA,0,0);
  //if(Msg==DN_KEY&&Param2==KEY_ENTER) return TRUE;
  switch(Msg)
  {
    case DN_INITDIALOG:
      Info.SendDlgMessage(hDlg,DM_RESETBOARD,0,0);
      SetFocus(true);
      break;
    case DN_CONTROLINPUT:
      {
        const INPUT_RECORD* record=(const INPUT_RECORD*)Param2;
        if(record->EventType==KEY_EVENT&&record->Event.KeyEvent.bKeyDown)
        {
          KillFocus();
          if(IsNone(record))
          {
            switch(record->Event.KeyEvent.wVirtualKeyCode)
            {
              case VK_UP:
                DlgParams->curr_col--;
                break;
              case VK_DOWN:
                DlgParams->curr_col++;
                break;
              case VK_LEFT:
                DlgParams->curr_row--;
                break;
              case VK_RIGHT:
                DlgParams->curr_row++;
                break;
              case VK_HOME:
                DlgParams->curr_row=0;
                break;
              case VK_END:
                DlgParams->curr_row=DlgParams->width-1;
                break;
              case VK_PRIOR:
                DlgParams->curr_col=0;
                break;
              case VK_NEXT:
                DlgParams->curr_col=DlgParams->height-1;
                break;
              case L' ':
                {
                  Info.SendDlgMessage(hDlg,DM_ENABLEREDRAW,FALSE,0);
                  if(!DlgParams->finished)
                  {
                    if(!DlgParams->started) Info.SendDlgMessage(hDlg,DM_START_GAME,0,0);
                    OpenPlace(hDlg,DlgParams,DlgParams->curr_row,DlgParams->curr_col,COP_CHECK_ALL);
                  }
                  Info.SendDlgMessage(hDlg,DM_ENABLEREDRAW,TRUE,0);
                }
                break;
              case VK_DELETE:
                {
                  Info.SendDlgMessage(hDlg,DM_ENABLEREDRAW,FALSE,0);
                  if(!DlgParams->finished)
                  {
                    FarDialogItem DialogItem;
                    Info.SendDlgMessage(hDlg,DM_GETDLGITEMSHORT,DlgParams->width*DlgParams->curr_col+DlgParams->curr_row,&DialogItem);
                    switch(GET_DATA_1(DialogItem))
                    {
                      case STATE_CLOSE:
                        SET_DATA_1(DialogItem,STATE_MARKED);
                        DlgParams->curr_mines++;
                        break;
                      case STATE_OPEN:
                        break;
                      case STATE_MARKED:
                        SET_DATA_1(DialogItem,STATE_CLOSE);
                        DlgParams->curr_mines--;
                        break;
                    }
                    Info.SendDlgMessage(hDlg,DM_SETDLGITEMSHORT,DlgParams->width*DlgParams->curr_col+DlgParams->curr_row,&DialogItem);
                    Info.SendDlgMessage(hDlg,DM_SHOWTIME,0,0);
                  }
                  Info.SendDlgMessage(hDlg,DM_ENABLEREDRAW,TRUE,0);
                }
                break;
              case VK_F2:
                DlgParams->started=false;
                DlgParams->finished=FINISH_NO;
                Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,DlgParams->width*DlgParams->height,const_cast<wchar_t*>(GetMsg(mStart)));
                Info.SendDlgMessage(hDlg,DM_RESETBOARD,0,0);
                break;
              case VK_F3:
                {
                  wchar_t ScoreKeyName[1024],PlayerKeyName[1024];
                  FSF.sprintf(ScoreKeyName,L"Score_%d_%d_%d",DlgParams->width,DlgParams->height,DlgParams->mines);
                  FSF.sprintf(PlayerKeyName,L"Player_%d_%d_%d",DlgParams->width,DlgParams->height,DlgParams->mines);
                  CFarSettings settings(MainGuid);
                  __int64 Score; wchar_t Name[512];
                  Score=settings.Get(ScoreKeyName,-1);
                  if(!settings.Get(PlayerKeyName,Name,sizeofa(Name))) Name[0]=0;
                  if(Score>=0&&Name[0])
                  {
                    wchar_t buffer[1024];
                    FSF.sprintf(buffer,GetMsg(mHighscoreFormat),Name,(long)Score);
                    const wchar_t* MsgItems[]={GetMsg(mHighscoreTitle),buffer,GetMsg(mOk)};
                    Info.Message(&MainGuid,&HiscoreGuid,0,NULL,MsgItems,sizeofa(MsgItems),1);
                  }
                }
                break;
            }
          }
          if(DlgParams->curr_row>=DlgParams->width) DlgParams->curr_row=0;
          if(DlgParams->curr_row<0) DlgParams->curr_row=DlgParams->width-1;
          if(DlgParams->curr_col>=DlgParams->height) DlgParams->curr_col=0;
          if(DlgParams->curr_col<0) DlgParams->curr_col=DlgParams->height-1;
          SetFocus(true);
          Info.SendDlgMessage(hDlg,DM_REDRAW,0,0);
        }
        else if(record->EventType==MOUSE_EVENT)
        {
          DWORD Buttons=record->Event.MouseEvent.dwButtonState;
          if(Buttons&FROM_LEFT_1ST_BUTTON_PRESSED) RunKey(L"Keys([[Space]])");
          else if(Buttons&RIGHTMOST_BUTTON_PRESSED) RunKey(L"Keys([[Del]])");
        }
      }
      break;
    case DN_GOTFOCUS:
      SetFocus(false);
      break;
    case DN_KILLFOCUS:
      KillFocus();
      break;
    case DM_RESETBOARD:
      {
        int curr_mines=DlgParams->mines,color;
        FarDialogItem DialogItem;
        Info.SendDlgMessage(hDlg,DM_ENABLEREDRAW,FALSE,0);
        for(int i=0;i<DlgParams->height;i++)
          for(int j=0;j<DlgParams->width;j++)
          {
            int k=i*DlgParams->width+j;
            Info.SendDlgMessage(hDlg,DM_GETDLGITEMSHORT,k,&DialogItem);
            SET_DATA_0(DialogItem,0);
            SET_DATA_1(DialogItem,0);
            color=0;
            DialogItem.VBuf[1].Char=GetChar(GET_DATA_0(DialogItem),GET_DATA_1(DialogItem),&color);
            int bgcolor=GetBG(i,j,STATE_CLOSE);
            DialogItem.VBuf[0].Attributes.ForegroundColor=DialogItem.VBuf[1].Attributes.ForegroundColor=DialogItem.VBuf[2].Attributes.ForegroundColor=color;
            DialogItem.VBuf[0].Attributes.BackgroundColor=DialogItem.VBuf[1].Attributes.BackgroundColor=DialogItem.VBuf[2].Attributes.BackgroundColor=bgcolor;
            Info.SendDlgMessage(hDlg,DM_SETDLGITEMSHORT,k,&DialogItem);
          }
        //set mines
        while(curr_mines)
          for(int i=0;i<DlgParams->height;i++)
            for(int j=0;j<DlgParams->width;j++)
            {
              int k=i*DlgParams->width+j;
              Info.SendDlgMessage(hDlg,DM_GETDLGITEMSHORT,k,&DialogItem);
              if(curr_mines&&(!GET_DATA_0(DialogItem)))
              {
                if(rand()<=(RAND_MAX*DlgParams->mines/(DlgParams->width*DlgParams->height)))
                {
                  curr_mines--;
                  SET_DATA_0(DialogItem,9);
                  Info.SendDlgMessage(hDlg,DM_SETDLGITEMSHORT,k,&DialogItem);
                }
              }
            }
        //set places
        for(int i=0;i<DlgParams->height;i++)
          for(int j=0;j<DlgParams->width;j++)
          {
            int k=i*DlgParams->width+j;
            Info.SendDlgMessage(hDlg,DM_GETDLGITEMSHORT,k,&DialogItem);
            if(GET_DATA_0(DialogItem)==0)
            {
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j-1,i-1,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j-1,i,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j-1,i+1,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j,i-1,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j,i+1,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j+1,i-1,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j+1,i,hDlg,DlgParams,false));
              SET_DATA_0(DialogItem,GET_DATA_0(DialogItem)+GetMine(j+1,i+1,hDlg,DlgParams,false));
              Info.SendDlgMessage(hDlg,DM_SETDLGITEMSHORT,k,&DialogItem);
            }
          }
        DlgParams->curr_mines=0;
        Info.SendDlgMessage(hDlg,DM_SHOWTIME,0,0);
        Info.SendDlgMessage(hDlg,DM_ENABLEREDRAW,TRUE,0);
      }
      break;
    case DN_ENTERIDLE:
      Info.SendDlgMessage(hDlg,DM_SHOWTIME,0,0);
      break;
    case DM_SHOWTIME:
      {
        wchar_t buffer[1024]; DWORD diff_time=DlgParams->started?((DlgParams->finished?DlgParams->end_time:GetTickCount())-DlgParams->start_time)/1000:0;
        FSF.sprintf(buffer,GetMsg(mTime),diff_time,DlgParams->curr_mines);
        Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,DlgParams->width*DlgParams->height+1,buffer);
      }
      break;
    case DM_START_GAME:
      Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,DlgParams->width*DlgParams->height,const_cast<wchar_t*>(GetMsg(mGame)));
      DlgParams->started=true;
      DlgParams->start_time=GetTickCount();
      break;
  }
  return Info.DefDlgProc(hDlg,Msg,Param1,Param2);
}