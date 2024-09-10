void CommandData::ProcessSwitch(char *Switch)
{

  switch(etoupper(Switch[0]))
  {
    case 'I':
      if (strnicomp(&Switch[1],"LOG",3)==0)
      {
        strncpyz(LogName,Switch[4] ? Switch+4:DefLogName,ASIZE(LogName));
        break;
      }
      if (stricomp(&Switch[1],"SND")==0)
      {
        Sound=true;
        break;
      }
      if (stricomp(&Switch[1],"ERR")==0)
      {
        MsgStream=MSG_STDERR;
        break;
      }
      if (strnicomp(&Switch[1],"EML",3)==0)
      {
        strncpyz(EmailTo,Switch[4] ? Switch+4:"@",ASIZE(EmailTo));
        EmailTo[sizeof(EmailTo)-1]=0;
        break;
      }
      if (stricomp(&Switch[1],"NUL")==0)
      {
        MsgStream=MSG_NULL;
        break;
      }
      if (etoupper(Switch[1])=='D')
      {
        for (int I=2;Switch[I]!=0;I++)
          switch(etoupper(Switch[I]))
          {
            case 'Q':
              MsgStream=MSG_ERRONLY;
              break;
            case 'C':
              DisableCopyright=true;
              break;
            case 'D':
              DisableDone=true;
              break;
            case 'P':
              DisablePercentage=true;
              break;
          }
        break;
      }
      if (stricomp(&Switch[1],"OFF")==0)
      {
        Shutdown=true;
        break;
      }
      break;
    case 'T':
      switch(etoupper(Switch[1]))
      {
        case 'K':
          ArcTime=ARCTIME_KEEP;
          break;
        case 'L':
          ArcTime=ARCTIME_LATEST;
          break;
        case 'O':
          FileTimeBefore.SetAgeText(Switch+2);
          break;
        case 'N':
          FileTimeAfter.SetAgeText(Switch+2);
          break;
        case 'B':
          FileTimeBefore.SetIsoText(Switch+2);
          break;
        case 'A':
          FileTimeAfter.SetIsoText(Switch+2);
          break;
        case 'S':
          {
            EXTTIME_MODE Mode=EXTTIME_HIGH3;
            bool CommonMode=Switch[2]>='0' && Switch[2]<='4';
            if (CommonMode)
              Mode=(EXTTIME_MODE)(Switch[2]-'0');
            if (Switch[2]=='-')
              Mode=EXTTIME_NONE;
            if (CommonMode || Switch[2]=='-' || Switch[2]=='+' || Switch[2]==0)
              xmtime=xctime=xatime=Mode;
            else
            {
              if (Switch[3]>='0' && Switch[3]<='4')
                Mode=(EXTTIME_MODE)(Switch[3]-'0');
              if (Switch[3]=='-')
                Mode=EXTTIME_NONE;
              switch(etoupper(Switch[2]))
              {
                case 'M':
                  xmtime=Mode;
                  break;
                case 'C':
                  xctime=Mode;
                  break;
                case 'A':
                  xatime=Mode;
                  break;
                case 'R':
                  xarctime=Mode;
                  break;
              }
            }
          }
          break;
        case '-':
          Test=false;
          break;
        case 0:
          Test=true;
          break;
        default:
          BadSwitch(Switch);
          break;
      }
      break;
    case 'A':
      switch(etoupper(Switch[1]))
      {
        case 'C':
          ClearArc=true;
          break;
        case 'D':
          AppendArcNameToPath=true;
          break;
        case 'G':
          if (Switch[2]=='-' && Switch[3]==0)
            GenerateArcName=0;
          else
          {
            GenerateArcName=true;
            strncpyz(GenerateMask,Switch+2,ASIZE(GenerateMask));
          }
          break;
        case 'N': //reserved for archive name
          break;
        case 'O':
          AddArcOnly=true;
          break;
        case 'P':
          strcpy(ArcPath,Switch+2);
          break;
        case 'S':
          SyncFiles=true;
          break;
        default:
          BadSwitch(Switch);
          break;
      }
      break;
    case 'D':
      if (Switch[2]==0)
        switch(etoupper(Switch[1]))
        {
          case 'S':
            DisableSortSolid=true;
            break;
          case 'H':
            OpenShared=true;
            break;
          case 'F':
            DeleteFiles=true;
            break;
        }
      break;
    case 'O':
      switch(etoupper(Switch[1]))
      {
        case '+':
          Overwrite=OVERWRITE_ALL;
          break;
        case '-':
          Overwrite=OVERWRITE_NONE;
          break;
        case 'R':
          Overwrite=OVERWRITE_AUTORENAME;
          break;
        case 'W':
          ProcessOwners=true;
          break;
#ifdef SAVE_LINKS
        case 'L':
          SaveLinks=true;
          break;
#endif
#ifdef _WIN_32
        case 'S':
          SaveStreams=true;
          break;
        case 'C':
          SetCompressedAttr=true;
          break;
#endif
        default :
          BadSwitch(Switch);
          break;
      }
      break;
    case 'R':
      switch(etoupper(Switch[1]))
      {
        case 0:
          Recurse=RECURSE_ALWAYS;
          break;
        case '-':
          Recurse=0;
          break;
        case '0':
          Recurse=RECURSE_WILDCARDS;
          break;
#ifndef _WIN_CE
        case 'I':
          {
            Priority=atoi(Switch+2);
            char *ChPtr=strchr(Switch+2,':');
            if (ChPtr!=NULL)
            {
              SleepTime=atoi(ChPtr+1);
              InitSystemOptions(SleepTime);
            }
            SetPriority(Priority);
          }
          break;
#endif
      }
      break;
    case 'Y':
      AllYes=true;
      break;
    case 'N':
    case 'X':
      if (Switch[1]!=0)
      {
        StringList *Args=etoupper(Switch[0])=='N' ? InclArgs:ExclArgs;
        if (Switch[1]=='@' && !IsWildcard(Switch))
        {
          RAR_CHARSET Charset=FilelistCharset;

#if defined(_WIN_32) && !defined(GUI)
          // for compatibility reasons we use OEM encoding
          // in Win32 console version by default

          if (Charset==RCH_DEFAULT)
            Charset=RCH_OEM;
#endif

          ReadTextFile(Switch+2,Args,false,true,Charset,true,true);
        }
        else
          Args->AddString(Switch+1);
      }
      break;
    case 'E':
      switch(etoupper(Switch[1]))
      {
        case 'P':
          switch(Switch[2])
          {
            case 0:
              ExclPath=EXCL_SKIPWHOLEPATH;
              break;
            case '1':
              ExclPath=EXCL_BASEPATH;
              break;
            case '2':
              ExclPath=EXCL_SAVEFULLPATH;
              break;
            case '3':
              ExclPath=EXCL_ABSPATH;
              break;
          }
          break;
        case 'D':
          ExclEmptyDir=true;
          break;
        case 'E':
          ProcessEA=false;
          break;
        case 'N':
          NoEndBlock=true;
          break;
        default:
          if (Switch[1]=='+')
          {
            InclFileAttr=GetExclAttr(&Switch[2]);
            InclAttrSet=true;
          }
          else
            ExclFileAttr=GetExclAttr(&Switch[1]);
          break;
      }
      break;
    case 'P':
      if (Switch[1]==0)
      {
        GetPassword(PASSWORD_GLOBAL,NULL,Password,sizeof(Password));
        eprintf("\n");
      }
      else
        strncpyz(Password,Switch+1,ASIZE(Password));
      break;
    case 'H':
      if (etoupper(Switch[1])=='P')
      {
        EncryptHeaders=true;
        if (Switch[2]!=0)
          strncpyz(Password,Switch+2,ASIZE(Password));
        else
          if (*Password==0)
          {
            GetPassword(PASSWORD_GLOBAL,NULL,Password,sizeof(Password));
            eprintf("\n");
          }
      }
      break;
    case 'Z':
      strncpyz(CommentFile,Switch[1]!=0 ? Switch+1:"stdin",ASIZE(CommentFile));
      break;
    case 'M':
      switch(etoupper(Switch[1]))
      {
        case 'C':
          {
            char *Str=Switch+2;
            if (*Str=='-')
              for (int I=0;I<sizeof(FilterModes)/sizeof(FilterModes[0]);I++)
                FilterModes[I].State=FILTER_DISABLE;
            else
              while (*Str)
              {
                int Param1=0,Param2=0;
                FilterState State=FILTER_AUTO;
                FilterType Type=FILTER_NONE;
                if (isdigit(*Str))
                {
                  Param1=atoi(Str);
                  while (isdigit(*Str))
                    Str++;
                }
                if (*Str==':' && isdigit(Str[1]))
                {
                  Param2=atoi(++Str);
                  while (isdigit(*Str))
                    Str++;
                }
                switch(etoupper(*(Str++)))
                {
                  case 'T': Type=FILTER_PPM;         break;
                  case 'E': Type=FILTER_E8;          break;
                  case 'D': Type=FILTER_DELTA;       break;
                  case 'A': Type=FILTER_AUDIO;       break;
                  case 'C': Type=FILTER_RGB;         break;
                  case 'I': Type=FILTER_ITANIUM;     break;
                  case 'L': Type=FILTER_UPCASETOLOW; break;
                }
                if (*Str=='+' || *Str=='-')
                  State=*(Str++)=='+' ? FILTER_FORCE:FILTER_DISABLE;
                FilterModes[Type].State=State;
                FilterModes[Type].Param1=Param1;
                FilterModes[Type].Param2=Param2;
              }
            }
          break;
        case 'M':
          break;
        case 'D':
          {
            if ((WinSize=atoi(&Switch[2]))==0)
              WinSize=0x10000<<(etoupper(Switch[2])-'A');
            else
              WinSize*=1024;
            if (!CheckWinSize())
              BadSwitch(Switch);
          }
          break;
        case 'S':
          {
            char *Names=Switch+2,DefNames[512];
            if (*Names==0)
            {
              strcpy(DefNames,DefaultStoreList);
              Names=DefNames;
            }
            while (*Names!=0)
            {
              char *End=strchr(Names,';');
              if (End!=NULL)
                *End=0;
              if (*Names=='.')
                Names++;
              char Mask[NM];
              if (strpbrk(Names,"*?.")==NULL)
                sprintf(Mask,"*.%s",Names);
              else
                strcpy(Mask,Names);
              StoreArgs->AddString(Mask);
              if (End==NULL)
                break;
              Names=End+1;
            }
          }
          break;
#ifdef PACK_SMP
        case 'T':
          Threads=atoi(Switch+2);
          if (Threads>MaxSearchThreads)
            BadSwitch(Switch);
          else
          {
          }
          break;
#endif
        default:
          Method=Switch[1]-'0';
          if (Method>5 || Method<0)
            BadSwitch(Switch);
          break;
      }
      break;
    case 'V':
      switch(etoupper(Switch[1]))
      {
#ifdef _WIN_32
        case 'D':
          EraseDisk=true;
          break;
#endif
        case 'N':
          OldNumbering=true;
          break;
        case 'P':
          VolumePause=true;
          break;
        case 'E':
          if (etoupper(Switch[2])=='R')
            VersionControl=atoi(Switch+3)+1;
          break;
        case '-':
          VolSize=0;
          break;
        default:
          {
            Int64 NewVolSize=atoil(&Switch[1]);

            if (NewVolSize==0)
              NewVolSize=INT64ERR;
            else
              switch (Switch[strlen(Switch)-1])
              {
                case 'f':
                case 'F':
                  switch(int64to32(NewVolSize))
                  {
                    case 360:
                      NewVolSize=362496;
                      break;
                    case 720:
                      NewVolSize=730112;
                      break;
                    case 1200:
                      NewVolSize=1213952;
                      break;
                    case 1440:
                      NewVolSize=1457664;
                      break;
                    case 2880:
                      NewVolSize=2915328;
                      break;
                  }
                  break;
                case 'k':
                  NewVolSize*=1024;
                  break;
                case 'm':
                  NewVolSize*=1024*1024;
                  break;
                case 'M':
                  NewVolSize*=1000*1000;
                  break;
                case 'g':
                  NewVolSize*=1024*1024;
                  NewVolSize*=1024;
                  break;
                case 'G':
                  NewVolSize*=1000*1000;
                  NewVolSize*=1000;
                  break;
                case 'b':
                case 'B':
                  break;
                default:
                  NewVolSize*=1000;
                  break;
              }
            if (VolSize==0)
              VolSize=NewVolSize;
            else
              NextVolSizes.Push(NewVolSize);
          }
          break;
      }
      break;
    case 'F':
      if (Switch[1]==0)
        FreshFiles=true;
      else
        BadSwitch(Switch);
      break;
    case 'U':
      if (Switch[1]==0)
        UpdateFiles=true;
      else
        BadSwitch(Switch);
      break;
    case 'W':
      strncpyz(TempPath,&Switch[1],ASIZE(TempPath));
      AddEndSlash(TempPath);
      break;
    case 'S':
      if (strnicomp(Switch,"SFX",3)==0)
      {
        const char *SFXName=Switch[3] ? Switch+3:DefSFXName;
        if (PointToName(SFXName)!=SFXName || FileExist(SFXName))
          strcpy(SFXModule,SFXName);
        else
          GetConfigName(SFXName,SFXModule,true);
      }
      if (isdigit(Switch[1]))
      {
        Solid|=SOLID_COUNT;
        SolidCount=atoi(&Switch[1]);
      }
      else
        switch(etoupper(Switch[1]))
        {
          case 0:
            Solid|=SOLID_NORMAL;
            break;
          case '-':
            Solid=SOLID_NONE;
            break;
          case 'E':
            Solid|=SOLID_FILEEXT;
            break;
          case 'V':
            Solid|=Switch[2]=='-' ? SOLID_VOLUME_DEPENDENT:SOLID_VOLUME_INDEPENDENT;
            break;
          case 'D':
            Solid|=SOLID_VOLUME_DEPENDENT;
            break;
          case 'L':
            if (isdigit(Switch[2]))
              FileSizeLess=atoil(Switch+2);
            break;
          case 'M':
            if (isdigit(Switch[2]))
              FileSizeMore=atoil(Switch+2);
            break;
          case 'C':
            {
              RAR_CHARSET rch;
              switch(etoupper(Switch[2]))
              {
                case 'A':
                  rch=RCH_ANSI;
                  break;
                case 'O':
                  rch=RCH_OEM;
                  break;
                case 'U':
                  rch=RCH_UNICODE;
                  break;
                default :
                  BadSwitch(Switch);
                  break;
              };
              if (Switch[3]==0)
                CommentCharset=FilelistCharset=rch;
              else
                for (int I=3;Switch[I]!=0;I++)
                  switch(etoupper(Switch[I]))
                  {
                    case 'C':
                      CommentCharset=rch;
                      break;
                    case 'L':
                      FilelistCharset=rch;
                      break;
                    default:
                      BadSwitch(Switch);
                      break;
                  }
            }
            break;

        }
      break;
    case 'C':
      if (Switch[2]==0)
        switch(etoupper(Switch[1]))
        {
          case '-':
            DisableComment=true;
            break;
          case 'U':
            ConvertNames=NAMES_UPPERCASE;
            break;
          case 'L':
            ConvertNames=NAMES_LOWERCASE;
            break;
        }
      break;
    case 'K':
      switch(etoupper(Switch[1]))
      {
        case 'B':
          KeepBroken=true;
          break;
        case 0:
          Lock=true;
          break;
      }
      break;
#ifndef GUI
    case '?' :
      OutHelp();
      break;
#endif
    default :
      BadSwitch(Switch);
      break;
  }
}