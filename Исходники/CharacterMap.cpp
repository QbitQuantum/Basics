long WINAPI MyDialog(HANDLE hDlg,int Msg,int Param1,long Param2)
{
  static int POpenFrom;
  static unsigned char *Str;
  static int *Ret;
  static COORD coord;
  static int LastSelectedMenu;
  static struct FarMenuItem *MenuItems;
  static int TotalMenuItems;
  static int TargetTable;
  static struct CharTableSet cts;
  static struct TableStruct newtable;
  static struct FarDialogItem DlgASCII, DlgText, DlgEdit, DlgInfo;
  static CHAR_INFO VBufASCII[256];
  static const unsigned char *InfoFormat;
  static BOOL EditMode;
  static int EditInsertMode;
  static char CharTxt[4];
  static int CharTxtPos;
  static char example[MAX_PATH];
  unsigned char Temp[51];
  static int EditLen;
  static unsigned char EditText[512];
  int tmplen;
  unsigned char tmptext[512];
  char *Cmd;
  static struct EditorInfo ei;
  struct FarList *fl;
  struct EditorConvertText ect;
  struct EditorGetString egs;
  struct EditorSetString ess;
  struct EditorSetPosition esp;
  WORD Color;
  int i;

  switch (Msg)
  {
    case DN_INITDIALOG:
      EditMode = FALSE;
      EditLen = 0;
      POpenFrom = ((struct DialogData *)Param2)->OpenFrom;
      Str = ((struct DialogData *)Param2)->Str;
      Ret = ((struct DialogData *)Param2)->Ret;
      MenuItems = NULL;
      GetRegKey(&reg[REG_LASTCOORDX],(int *)&coord.X,0);
      GetRegKey(&reg[REG_LASTCOORDY],(int *)&coord.Y,0);
      for (i=0; GetCharTable(i,&cts) != -1; i++)
      {
        MenuItems=(struct FarMenuItem *)realloc(MenuItems,(i+1)*sizeof(struct FarMenuItem));
        if (!MenuItems)
        {
          Warning(MMemoryError);
          Info.SendDlgMessage(hDlg,DM_CLOSE,0,0);
          return FALSE;
        }
        lstrcpy(MenuItems[i].Text,cts.TableName);
        MenuItems[i].Checked = MenuItems[i].Selected = MenuItems[i].Separator = 0;
      }
      TotalMenuItems = i;
      MenuItems[LastSelectedMenu=0].Selected = 1;
      Info.SendDlgMessage(hDlg,DM_SETCURSORSIZE,3,MAKELONG(1,99));
      InfoFormat = (const unsigned char *) GetMsg(MInfoFormat);
      Info.SendDlgMessage(hDlg,DM_GETDLGITEM,3,(long)&DlgASCII);
      Info.SendDlgMessage(hDlg,DM_GETDLGITEM,1,(long)&DlgText);
      Info.SendDlgMessage(hDlg,DM_GETDLGITEM,5,(long)&DlgEdit);
      Info.SendDlgMessage(hDlg,DM_GETDLGITEM,6,(long)&DlgInfo);
      Color = Info.AdvControl(Info.ModuleNumber,ACTL_GETCOLOR,(void *)COL_DIALOGTEXT);
      Color |= Info.AdvControl(Info.ModuleNumber,ACTL_GETCOLOR,(void *)COL_DIALOGBOX);
      SetVBufAttrib(VBufASCII,Color,256);
      SetVBufAttrib(DlgInfo.VBuf,Color,32);
      {
        struct FarDialogItem DlgDemo;
        char Demo[19*17+1];
        char Space[18];
        Info.SendDlgMessage(hDlg,DM_GETDLGITEM,11,(long)&DlgDemo);
        SetVBufAttrib(DlgDemo.VBuf,Color,19*17);
        FSF.sprintf(Space,"%17s"," ");
        lstrcpy(Demo,"   0123456789ABCDEF");
        for (i=0; i<256; i+=16)
        {
          char Hex[3];
          FSF.sprintf(Hex,x2,i);
          lstrcat(Demo,Hex);
          lstrcat(Demo,Space);
        }
        Demo[19+3] = 32;
        for (i=1; i<256; i++)
        {
          Demo[19+i/16*19+i%16+3] = i;
        }
        SetVBufChars(DlgDemo.VBuf,(unsigned char *)Demo,19*17);
        Info.SendDlgMessage(hDlg,DM_SETDLGITEM,11,(long)&DlgDemo);
      }
      Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,1,0); //Select DOS
      TargetTable = 0; //DOS
      if (POpenFrom == OPENF_EDITOR)
      {
        Info.EditorControl(ECTL_GETINFO,(void *)&ei);
        switch (ei.TableNum)
        {
          case -1:
            if (ei.AnsiMode == 1)
            {
              TargetTable = 1; //WIN
              Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,1,1); //select WIN
            }
            break;

          default:
            if (ei.TableNum < 0)
              break;
            TargetTable = ei.TableNum+2;
            FSF.sprintf(DlgText.Data,s32,MenuItems[ei.TableNum+2].Text);
            MenuItems[LastSelectedMenu].Selected = 0;
            MenuItems[LastSelectedMenu=(ei.TableNum+2)].Selected = 1;
            Info.CharTable(ei.TableNum,(char *)&cts,sizeof(struct CharTableSet));
            Info.SendDlgMessage(hDlg,DM_SETDLGITEM,1,(long)&DlgText);
        }
        if (EditorAutoPos)
        {
          egs.StringNumber = -1;
          Info.EditorControl(ECTL_GETSTRING,(void *)&egs);
          if (egs.StringLength > 0 && ei.CurPos < egs.StringLength)
          {
            i = egs.StringText[ei.CurPos];
            coord.X = i%32;
            coord.Y = i/32;
          }
        }
      }
      if (CmdAutoPos && POpenFrom == OPENF_COMMANDLINE)
      {
        Info.Control(INVALID_HANDLE_VALUE,FCTL_GETCMDLINEPOS,(void *)&i);
        if (i < 1024)
        {
          Cmd = (char *)malloc(1024*sizeof(char));
          if (!Cmd)
          {
            Warning(MMemoryError);
            Info.SendDlgMessage(hDlg,DM_CLOSE,0,0);
            return FALSE;
          }
          Info.Control(INVALID_HANDLE_VALUE,FCTL_GETCMDLINE,(void *)Cmd);
          i = cts.EncodeTable[Cmd[i]];
          coord.X = i%32;
          coord.Y = i/32;
          free(Cmd);
        }
      }
      if (POpenFrom == OPENF_MANUAL)
      {
        i = cts.EncodeTable[*Str];
        coord.X = i%32;
        coord.Y = i/32;
      }
      Info.SendDlgMessage(hDlg,DMCM_REDRAW,1,1);
      return TRUE;

    case DN_KEY:
    {
      long rParam2 = Param2;
      if (Param1==8)
        if (!(Param2==KEY_ESC || Param2==KEY_F10))
          return FALSE;
      if ((Param2&KEY_CTRL)&&((Param2&0xFFL)>='a')&&((Param2&0xFFL)<='z'))
        rParam2&=~0x20L;

      switch (rParam2)
      {
        case KEY_LEFT: (coord.X>0)?--coord.X:((coord.Y>0)?(coord.X=31,--coord.Y):coord.X); break;

        case KEY_RIGHT: (coord.X<31)?++coord.X:((coord.Y<7)?(coord.X=0,++coord.Y):coord.X); break;

        case KEY_UP: if (coord.Y > 0) --coord.Y; break;

        case KEY_DOWN: if (coord.Y < 7) ++coord.Y; break;

        case KEY_HOME: coord.X = 0; break;

        case KEY_END: coord.X = 31; break;

        case KEY_PGUP: coord.Y = 0; break;

        case KEY_PGDN: coord.Y = 7; break;

        case KEY_CTRLHOME: coord.Y = coord.X = 0; break;

        case KEY_CTRLEND: coord.Y = 7; coord.X = 31; break;

        case KEY_ENTER:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_ENTER,0,0);
          return TRUE;

        case KEY_SHIFTF8:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,0,0);
          return TRUE;

        case KEY_F8:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,2,0); //exchange DOS/WIN
          return TRUE;

        case KEY_SHIFTENTER:
        case KEY_INS:
        case KEY_ADD:
        case KEY_SUBTRACT:
          if (!EditMode && Info.SendDlgMessage(hDlg,DMCM_SETEDIT,0,0))
          {
            switch (Param2)
            {
              case KEY_ADD: (coord.X<31)?++coord.X:((coord.Y<7)?(coord.X=0,++coord.Y):coord.X); break;
              case KEY_SUBTRACT: (coord.X>0)?--coord.X:((coord.Y>0)?(coord.X=31,--coord.Y):coord.X); break;
            }
            break;
          }
          return TRUE;

        case KEY_DEL:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_DEL,0,0);
          return TRUE;
        case KEY_BS:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_BS,0,0);
          return TRUE;

        case KEY_CTRLINS:
        case KEY_CTRLC:
          if (!EditMode)
          {
            tmplen = EditLen;
            if (tmplen==0)
            {
              EditText[0] = coord.X+32*coord.Y;
              tmplen = 1;
            }
            EditText[tmplen] = 0;
            if (EncodeBeforeInsertion)
            {
              memcpy(tmptext,EditText,tmplen+1);
              Encode((char *)tmptext,tmplen,&cts,TargetTable);
              FSF.CopyToClipboard((const char *)tmptext);
            }
            else
              FSF.CopyToClipboard((const char *)EditText);
          }
          return TRUE;

        case KEY_ALTSHIFTF9:
          Info.SendDlgMessage(hDlg,DM_SHOWDIALOG,FALSE,0);
          Config();
          Info.SendDlgMessage(hDlg,DM_SHOWDIALOG,TRUE,0);
          return TRUE;

        case KEY_F9:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,3,1);
          break;
        case KEY_SHIFTF9:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,3,-1);
          break;

        case KEY_CTRLI:
          Info.SendDlgMessage(hDlg,DMCM_SHOWTABLEINFO,0,0);
          return TRUE;

        case KEY_CTRLN:
          if (!EditMode)
            Info.SendDlgMessage(hDlg,DMCM_EDITTABLE,1,0);
          return TRUE;

        case KEY_CTRLE:
          if (!EditMode)
          {
            Info.SendDlgMessage(hDlg,DMCM_EDITTABLE,0,0);
          }
          else
          {
            int xxx;
            const char *XXX;
            EditInsertMode = (EditInsertMode+1)%3;
            xxx=VBufASCII[coord.X+32*coord.Y].Char.AsciiChar;
            switch (EditInsertMode)
            {
              case 0: XXX = x2; break;
              case 1: XXX = d3; break;
              case 2: XXX = c1; break;
            }
            FSF.sprintf(CharTxt,XXX,xxx);
            CharTxtPos = 0;
            Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,7,(long)CharTxt);
            Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,9,(long)GetMsg(MEditModeHex+EditInsertMode));
          }
          return TRUE;

        case KEY_CTRLX:
          if (EditMode)
            Info.SendDlgMessage(hDlg,DMCM_EDITTABLE,0,1);
          return TRUE;

        case KEY_CTRLS:
          if (EditMode)
            Info.SendDlgMessage(hDlg,DMCM_EDITTABLE,1,1);
          return TRUE;

        case KEY_CTRLL:
          if (EditMode)
          {
            static struct InitDialogItem InitItems[]=
            {
              {DI_DOUBLEBOX,3,1,57,4,0,MTitle},
              {DI_TEXT,5,2,0,0,0,MEnterFileName},
              {DI_EDIT,5,3,55,0,0,-1},
              {DI_BUTTON,3,5,0,0,0,MOk},
            };
            struct FarDialogItem DialogItems[4];
            InitDialogItems(InitItems,DialogItems,4);
            DialogItems[3].DefaultButton = 1;
            if (Info.Dialog(Info.ModuleNumber,-1,-1,60,6,NULL,DialogItems,4)!=3)
              break;
            FSF.Unquote(DialogItems[2].Data);
            lstrcpy(example,DialogItems[2].Data);
            LoadFile(example,hDlg,&newtable.cts);
          }
          return TRUE;

        case KEY_CTRLU:
          if (EditMode)
          {
            *example = '\0';
            Info.SendDlgMessage(hDlg,DM_LISTDELETE,8,0);
          }
          return TRUE;

        default:
          if (EditMode)
          {
            BOOL ret=FALSE;
            if (Param2==KEY_ESC||Param2==KEY_F10)
            {
              if (Info.SendDlgMessage(hDlg,DMCM_EDITTABLE,0,1))
              {
                Info.SendDlgMessage(hDlg,DM_CLOSE,0,0);
              }
              return TRUE;
            }
            switch (EditInsertMode)
            {
              case 0: //Hex
                if((Param2>='0' && Param2<='9') || (Param2>='a' && Param2<='f') || (Param2>='A' && Param2<='F'))
                {
                  CharTxt[CharTxtPos++] = Param2;
                  CharTxt[CharTxtPos] = '\0';
                  if (CharTxtPos>1)
                    CharTxtPos=0;
                  FSF.sscanf(CharTxt,"%X",&i);
                  ret=TRUE;
                }
                break;
              case 1: //Decimal
                if((Param2>='0' && Param2<='9'))
                {
                  CharTxt[CharTxtPos++] = Param2;
                  CharTxt[CharTxtPos] = '\0';
                  FSF.sscanf(CharTxt,"%d",&i);
                  if (i>255)
                  {
                    CharTxt[CharTxtPos=0] = Param2;
                    CharTxt[++CharTxtPos] = '\0';
                  }
                  if (CharTxtPos>2)
                    CharTxtPos=0;
                  ret=TRUE;
                }
                break;
              case 2: //Char
                if((Param2>31 && Param2<256))
                {
                  CharTxt[CharTxtPos++] = Param2;
                  CharTxt[CharTxtPos] = '\0';
                  CharTxtPos=0;
                  FSF.sscanf(CharTxt,"%c",&i);
                  ret=TRUE;
                }
            }
            if (ret)
            {
              struct FarListPos lp;
              Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,7,(long)CharTxt);
              VBufASCII[coord.X+32*coord.Y].Char.AsciiChar = i;
              newtable.cts.DecodeTable[coord.X+32*coord.Y] = i;
              Info.SendDlgMessage(hDlg,DM_LISTGETCURPOS,8,(long)&lp);
              LoadFile(example,hDlg,&newtable.cts);
              Info.SendDlgMessage(hDlg,DM_LISTSETCURPOS,8,(long)&lp);
              CopyVBufSmart(DlgASCII.VBuf,VBufASCII,256);
              Info.SendDlgMessage(hDlg,DM_SETDLGITEM,3,(long)&DlgASCII);
              Info.SendDlgMessage(hDlg,DMCM_REDRAW,0,1);
              return TRUE;
            }
            return FALSE;
          }
          else
          {
            if (Param2<256 && Param2>31)
            {
              coord.X = Param2%32;
              coord.Y = Param2/32;
              break;
            }
            return FALSE;
          }
      }
      if (EditMode)
      {
        int xxx;
        const char *XXX;
        xxx=VBufASCII[coord.X+32*coord.Y].Char.AsciiChar;
        switch (EditInsertMode)
        {
          case 0: XXX = x2; break;
          case 1: XXX = d3; break;
          case 2: XXX = c1;
        }
        FSF.sprintf(CharTxt,XXX,xxx);
        CharTxtPos = 0;
        Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,7,(long)CharTxt);
      }
      Info.SendDlgMessage(hDlg,DMCM_REDRAW,0,1);
      return TRUE;
    }

    case DN_MOUSECLICK:
      switch (Param1)
      {
        case 3:
          coord = ((MOUSE_EVENT_RECORD *)Param2)->dwMousePosition;
          Info.SendDlgMessage(hDlg,DMCM_REDRAW,0,1);
          if (((MOUSE_EVENT_RECORD *)Param2)->dwButtonState == RIGHTMOST_BUTTON_PRESSED)
          {
            Info.SendDlgMessage(hDlg,DMCM_SETEDIT,0,0);
          }
          else
          {
            if (((MOUSE_EVENT_RECORD *)Param2)->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
              if (((MOUSE_EVENT_RECORD *)Param2)->dwEventFlags & DOUBLE_CLICK)
                Info.SendDlgMessage(hDlg,DMCM_ENTER,0,0);
          }
          return TRUE;

        case 1:
          if (((MOUSE_EVENT_RECORD *)Param2)->dwButtonState == RIGHTMOST_BUTTON_PRESSED)
          {
            Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,2,0);
          }
          else
          {
            if (((MOUSE_EVENT_RECORD *)Param2)->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
              Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,0,0);
            }
          }
          return TRUE;

        case 5:
          if (((MOUSE_EVENT_RECORD *)Param2)->dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
          {
              Info.SendDlgMessage(hDlg,DMCM_BS,0,0);
          }
          else
          {
            if (((MOUSE_EVENT_RECORD *)Param2)->dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
              Info.SendDlgMessage(hDlg,DMCM_DEL,0,0);
            }
          }
          return TRUE;
      }
      return FALSE;

    case DMCM_REDRAW:
      if (Param1)
      {
        SetVBufChars(VBufASCII,cts.DecodeTable,256);
        CopyVBufSmart(DlgASCII.VBuf,VBufASCII,256);
        Info.SendDlgMessage(hDlg,DM_SETDLGITEM,3,(long)&DlgASCII);
      }
      if (Param1 || Param2)
      {
        i = VBufASCII[coord.X+32*coord.Y].Char.AsciiChar;
        FSF.sprintf((char *)Temp,(const char *)InfoFormat,(unsigned char)(i==0?32:i),(unsigned char)i,(unsigned char)i,(int)(coord.X+32*coord.Y),(int)(coord.X+32*coord.Y));
        SetVBufChars(DlgInfo.VBuf,Temp,32);
        Info.SendDlgMessage(hDlg,DM_SETDLGITEM,6,(long)&DlgInfo);
        Info.SendDlgMessage(hDlg,DM_SETCURSORPOS,3,(long)&coord);
      }
      return TRUE;

    case DMCM_SETEDIT:
      if (EditLen < 511)
      {
        i = VBufASCII[coord.X+32*coord.Y].Char.AsciiChar;
        if (i == 0)
        {
          switch (POpenFrom)
          {
            case OPENF_EDITOR:
            case OPENF_VIEWER:
            case OPENF_MANUAL:
              DlgEdit.Data[EditLen] = 32;
              break;
            default:
              return FALSE;
          }
        }
        else
          DlgEdit.Data[EditLen] = (unsigned char) i;
        EditText[EditLen] = (unsigned char) (coord.X+32*coord.Y);
        DlgEdit.Data[++EditLen] = 0;
        Info.SendDlgMessage(hDlg,DM_SETDLGITEM,5,(long)&DlgEdit);
        return TRUE;
      }
      return FALSE;

    case DMCM_ENTER:
      if (EditLen==0)
      {
        i = VBufASCII[coord.X+32*coord.Y].Char.AsciiChar;
        if (i == 0 && POpenFrom == OPENF_COMMANDLINE)
        {
          //MessageBeep(0);
          return FALSE;
        }
        else
        {
          EditText[0] = (unsigned char) (coord.X+32*coord.Y);
          EditLen = 1;
        }
      }
      EditText[EditLen] = 0;
      if (EncodeBeforeInsertion)
        if (TargetTable != LastSelectedMenu)
          Encode((char *)EditText,EditLen,&cts,TargetTable);
      if (CopyToClipboard)
        FSF.CopyToClipboard((const char *)EditText);
      switch (POpenFrom)
      {
        case OPENF_COMMANDLINE:
          Info.Control(INVALID_HANDLE_VALUE,FCTL_INSERTCMDLINE,(void *)EditText);
          break;
        case OPENF_EDITOR:
          egs.StringNumber = -1;
          Info.EditorControl(ECTL_GETSTRING,(void *)&egs);
          if (ei.CurPos > egs.StringLength)
            ess.StringText = (char *)malloc((egs.StringLength+EditLen+(ei.CurPos-egs.StringLength))*sizeof(char));
          else
            ess.StringText = (char *)malloc((egs.StringLength+EditLen)*sizeof(char));
          if (!ess.StringText)
          {
            Warning(MMemoryError);
            return FALSE;
          }
          if (ei.CurPos > egs.StringLength)
          {
            for (i=egs.StringLength; i<ei.CurPos; i++)
              ess.StringText[i] = cts.EncodeTable[32];
            if (EncodeBeforeInsertion)
              Encode(&ess.StringText[egs.StringLength],ei.CurPos-egs.StringLength,&cts,TargetTable);
            memcpy(ess.StringText,egs.StringText,egs.StringLength);
            memcpy(ess.StringText+ei.CurPos,EditText,EditLen);
            ess.StringLength = EditLen + ei.CurPos;
          }
          else
          {
            memcpy(ess.StringText,egs.StringText,ei.CurPos);
            memcpy(ess.StringText+ei.CurPos,EditText,EditLen);
            memcpy(ess.StringText+ei.CurPos+EditLen,egs.StringText+ei.CurPos,egs.StringLength-ei.CurPos);
            ess.StringLength = EditLen + egs.StringLength;
          }
          ess.StringNumber = -1;
          ess.StringEOL = (char *)egs.StringEOL;
          Info.EditorControl(ECTL_SETSTRING,(void *)&ess);
          esp.CurPos = ei.CurPos + EditLen;
          esp.CurLine = esp.CurTabPos = esp.TopScreenLine = esp.LeftPos = esp.Overtype = -1;
          Info.EditorControl(ECTL_SETPOSITION,(void *)&esp);
          free(ess.StringText);
          break;
        case OPENF_VIEWER:
          break;
        case OPENF_MANUAL:
        {
          memcpy(Str,EditText,EditLen);
          *Ret=EditLen;
        }

      }
      Info.SendDlgMessage(hDlg,DM_CLOSE,0,0);
      return TRUE;

    case DMCM_TABLESELECT:
      if (EditLen > 0)
        return FALSE;
      switch (Param1)
      {
        case 0:
          i = Info.Menu(Info.ModuleNumber,-1,-1,0,FMENU_WRAPMODE|FMENU_AUTOHIGHLIGHT,GetMsg(MTableSelect),NULL,NULL,NULL,NULL,MenuItems,TotalMenuItems);
          break;
        case 1:
          i = Param2;
          break;
        case 2:
          i = (LastSelectedMenu == 1 ? 0 : 1);
          break;
        case 3:
          i = LastSelectedMenu + Param2;
          if (i<0)
            i = TotalMenuItems-1;
          if (i >= TotalMenuItems)
            i = 0;
          break;
      }
      if (i!=-1)
      {
        FSF.sprintf(DlgText.Data,s32,MenuItems[i].Text);
        MenuItems[LastSelectedMenu].Selected = 0;
        MenuItems[LastSelectedMenu=i].Selected = 1;
        GetCharTable(i,&cts);
        Info.SendDlgMessage(hDlg,DM_SETDLGITEM,1,(long)&DlgText);
        Info.SendDlgMessage(hDlg,DMCM_REDRAW,1,0);
        return TRUE;
      }
      return FALSE;

    case DMCM_DEL:
    case DMCM_BS:
      if (EditLen > 0)
      {
        if (Msg == DMCM_DEL)
          EditLen=1;
        DlgEdit.Data[--EditLen] = 0;
        Info.SendDlgMessage(hDlg,DM_SETDLGITEM,5,(long)&DlgEdit);
      }
      return TRUE;

    case DMCM_SHOWTABLEINFO:
      {
        struct InitDialogItem InitItems[]=
        {
          {DI_DOUBLEBOX,3,1,57,8,0,MTitle},
          {DI_TEXT,5,2,0,0,0,MTableName},
          {DI_EDIT,5,3,55,0,0,-1},
          {DI_TEXT,5,4,0,0,0,MStatusTableName},
          {DI_EDIT,5,5,55,0,0,-1},
          {DI_TEXT,5,6,0,0,0,MRFCCharset},
          {DI_EDIT,5,7,55,0,0,-1},
          {DI_BUTTON,3,9,0,0,0,MOk},
        };
        struct FarDialogItem DialogItems[8];
        if (Param1||EditMode)
          InitItems[0].Data=MEnterTableInfo;
        InitDialogItems(InitItems,DialogItems,8);
        DialogItems[7].DefaultButton = 1;
        lstrcpy(DialogItems[2].Data,EditMode?newtable.cts.TableName:(Param1?"":cts.TableName));
        if (!EditMode)
        {
          if (!Param1)
          {
            DialogItems[2].Flags|=DIF_READONLY;
            for (i=4; i<=6; i+=2)
            {
              DialogItems[i].Flags|=DIF_READONLY;
              lstrcpy(DialogItems[i].Data,GetMsg(MUnavailable));
            }
          }
        }
        else
        {
          lstrcpy(DialogItems[4].Data,newtable.ShortName);
          lstrcpy(DialogItems[6].Data,newtable.RFCName);
        }
        if (Info.Dialog(Info.ModuleNumber,-1,-1,60,10,NULL,DialogItems,8)!=7)
          return FALSE;
        if (EditMode||Param1)
        {
          lstrcpyn(newtable.cts.TableName,DialogItems[2].Data,128);
          lstrcpyn(newtable.ShortName,DialogItems[4].Data,128);
          lstrcpyn(newtable.RFCName,DialogItems[6].Data,128);
          FSF.sprintf(DlgText.Data,s32,*(newtable.cts.TableName)?newtable.cts.TableName:newtable.ShortName);
          Info.SendDlgMessage(hDlg,DM_SETDLGITEM,1,(long)&DlgText);
        }
      }
      return TRUE;

    case DMCM_EDITTABLE:
      if (Param2==0)
      {
        SMALL_RECT sr;
        COORD dcoord;
        if (Param1)
        {
          Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,1,0);
          newtable.cts=cts;
          *newtable.ShortName='\0';
          *newtable.RFCName='\0';
          Info.SendDlgMessage(hDlg,DMCM_SHOWTABLEINFO,1,0);
        }
        else
        {
          newtable.cts=cts;
          *newtable.ShortName='\0';
          *newtable.RFCName='\0';
        }
        dcoord.X = 61; dcoord.Y=25;
        Info.SendDlgMessage(hDlg,DM_RESIZEDIALOG,0,(long)&dcoord);
        sr.Left = 3; sr.Top=1; sr.Right=36; sr.Bottom=23;
        Info.SendDlgMessage(hDlg,DM_SETITEMPOSITION,0,(long)&sr);
        Info.SendDlgMessage(hDlg,DM_SHOWITEM,5,0);
        Info.SendDlgMessage(hDlg,DM_SHOWITEM,8,1);
        Info.SendDlgMessage(hDlg,DM_SHOWITEM,7,1);
        Info.SendDlgMessage(hDlg,DM_SHOWITEM,9,1);
        Info.SendDlgMessage(hDlg,DM_SHOWITEM,10,1);
        Info.SendDlgMessage(hDlg,DM_SHOWITEM,11,1);
        *example = '\0';
        Info.SendDlgMessage(hDlg,DM_LISTDELETE,8,0);
        EditInsertMode = 0;
        i=VBufASCII[coord.X+32*coord.Y].Char.AsciiChar;
        FSF.sprintf(CharTxt,x2,i);
        CharTxtPos = 0;
        Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,7,(long)CharTxt);
        Info.SendDlgMessage(hDlg,DM_SETTEXTPTR,9,(long)GetMsg(MEditModeHex+EditInsertMode));
        Info.SendDlgMessage(hDlg,DMCM_REDRAW,1,0);
        EditMode=TRUE;
      }
      else
      {
        if (Param1)
        {
          static struct InitDialogItem InitItems[]=
          {
            {DI_DOUBLEBOX,3,1,57,4,0,MTitle},
            {DI_TEXT,5,2,0,0,0,MSaveToFile},
            {DI_EDIT,5,3,55,0,0,-1},
            {DI_BUTTON,3,5,0,0,0,MOk},
          };
          struct FarDialogItem DialogItems[4];
          InitDialogItems(InitItems,DialogItems,4);
          DialogItems[3].DefaultButton = 1;
          lstrcpy(DialogItems[2].Data,*(newtable.cts.TableName)?newtable.cts.TableName:newtable.ShortName);
          lstrcat(DialogItems[2].Data,".reg");
          if (Info.Dialog(Info.ModuleNumber,-1,-1,60,6,NULL,DialogItems,4)==3)
          {
            HANDLE fp;
            DWORD transfered;
            char buf[256];
            FSF.Unquote(DialogItems[2].Data);
            fp = CreateFile(DialogItems[2].Data,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,0,NULL);
            if (fp==INVALID_HANDLE_VALUE)
            {
              Warning(MFileError);
              return FALSE;
            }
            lstrcpy(buf,"REGEDIT4\r\n[HKEY_CURRENT_USER\\Software\\Far\\CodeTables\\");
            WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            lstrcpy(buf,*(newtable.ShortName)?newtable.ShortName:newtable.cts.TableName);
            WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            lstrcpy(buf,"]\r\n");
            WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            if (*(newtable.cts.TableName)&&*(newtable.ShortName))
            {
              lstrcpy(buf,"\"TableName\"=\"");
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
              lstrcpy(buf,newtable.cts.TableName);
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
              lstrcpy(buf,"\"\r\n");
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            }
            if (*(newtable.RFCName))
            {
              lstrcpy(buf,"\"RFCCharset\"=\"");
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
              lstrcpy(buf,newtable.RFCName);
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
              lstrcpy(buf,"\"\r\n");
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            }
            lstrcpy(buf,"\"Mapping\"=hex:\\\r\n");
            WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            for (i=0; i<16; i++)
            {
              int j;
              *buf = '\0';
              for (j=0; j<16; j++)
              {
                char hex[4];
                FSF.sprintf(hex,"%02X,",newtable.cts.DecodeTable[i*16+j]);
                lstrcat(buf,hex);
              }
              if ((i*16+j)<255)
                lstrcat(buf,"\\");
              else
                buf[lstrlen(buf)-1] = '\0';
              lstrcat(buf,"\r\n");
              WriteFile(fp,buf,lstrlen(buf),&transfered,NULL);
            }
            CloseHandle(fp);
          }
        }
        else
        {
          SMALL_RECT sr;
          COORD coord;
          const char *Msg[2];
          Msg[0] = GetMsg(MTitle);
          Msg[1] = GetMsg(MSureToExit);
          i = Info.Message(Info.ModuleNumber,FMSG_WARNING|FMSG_MB_YESNO,NULL,Msg,2,0);
          if (i==1 || i==-1)
            return FALSE;
          Info.SendDlgMessage(hDlg,DM_LISTDELETE,8,0);
          Info.SendDlgMessage(hDlg,DM_SHOWITEM,8,0);
          Info.SendDlgMessage(hDlg,DM_SHOWITEM,9,0);
          Info.SendDlgMessage(hDlg,DM_SHOWITEM,7,0);
          Info.SendDlgMessage(hDlg,DM_SHOWITEM,10,0);
          Info.SendDlgMessage(hDlg,DM_SHOWITEM,11,0);
          Info.SendDlgMessage(hDlg,DM_SHOWITEM,5,1);
          sr.Left = 3; sr.Top=1; sr.Right=36; sr.Bottom=15;
          Info.SendDlgMessage(hDlg,DM_SETITEMPOSITION,0,(long)&sr);
          coord.X = 40; coord.Y=17;
          Info.SendDlgMessage(hDlg,DM_RESIZEDIALOG,0,(long)&coord);
          Info.SendDlgMessage(hDlg,DMCM_TABLESELECT,1,0);
          Info.SendDlgMessage(hDlg,DMCM_REDRAW,1,0);
          EditMode=FALSE;
        }
      }
      return TRUE;

    case DN_CLOSE:
      if (MenuItems)
        free(MenuItems);
      SetRegKey(&reg[REG_LASTCOORDX],coord.X);
      SetRegKey(&reg[REG_LASTCOORDY],coord.Y);
      return TRUE;

  }
  return Info.DefDlgProc(hDlg,Msg,Param1,Param2);
}