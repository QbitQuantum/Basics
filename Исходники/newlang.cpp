void LANG_LOAD(char* limit_to) {
  CWaitCursor wait;
  //
  extern int NewLangStrSz;
  extern coucal NewLangStr;
  extern int NewLangStrKeysSz;
  extern coucal NewLangStrKeys;
  //
  int selected_lang=LANG_T(-1);
  //
  if (!limit_to) {
    LANG_DELETE();
    NewLangStr=coucal_new(NewLangStrSz);
    NewLangStrKeys=coucal_new(NewLangStrKeysSz);
    if ((NewLangStr==NULL) || (NewLangStrKeys==NULL)) {
      AfxMessageBox("Error in lang.h: not enough memory");
    } else {
      coucal_value_is_malloc(NewLangStr,1);
      coucal_value_is_malloc(NewLangStrKeys,1);
    }
  }

  TCHAR ModulePath[MAX_PATH + 1];
  ModulePath[0] = '\0';
  ::GetModuleFileName(NULL, ModulePath, sizeof(ModulePath)/sizeof(TCHAR) - 1);
  TCHAR* pos = _tcsrchr(ModulePath, '\\');
  if (pos != NULL)
  {
    * ( pos + 1) = '\0';
  } else {
    ModulePath[0] = '\0';
  }

  /* Load master file (list of keys and internal keys) */
  CString app = ModulePath;
  if (!limit_to) {
    CString mname=app+"lang.def";
    if (!fexist((char*)LPCTSTR(mname)))
      mname="lang.def";
    FILE* fp=fopen(mname,"rb");
    if (fp) {
      char intkey[8192];
      char key[8192];
      while(!feof(fp)) {
        linput_cpp(fp,intkey,8000);
        linput_cpp(fp,key,8000);
        if (strnotempty(intkey) && strnotempty(key)) {
          char* test=LANGINTKEY(key);

          /* Increment for multiple definitions */
          if (strnotempty(test)) {
            int increment=0;
            size_t pos = strlen(key);
            do {
              increment++;
              sprintf(key+pos,"%d",increment);
              test=LANGINTKEY(key);
            }  while (strnotempty(test));
          }

          if (!strnotempty(test)) {         // éviter doublons
            // conv_printf(key,key);
            size_t len;
            char* buff;
            len=strlen(intkey);
            buff=(char*)malloc(len+2);
            if (buff) {
              strcpybuff(buff,intkey);
              coucal_add(NewLangStrKeys,key,(intptr_t)buff);
            }
          }
        } // if
      }  // while
      fclose(fp);
    } else {
      AfxMessageBox("FATAL ERROR\r\n'lang.def' file NOT FOUND!\r\nEnsure that the installation was complete!");
      exit(0);
    }
  }
  
  /* Language Name? */
  char* hashname;
  {
    char name[256];
    sprintf(name,"LANGUAGE_%d",selected_lang+1);
    hashname=LANGINTKEY(name);
  }

  /* Get only language name */
  if (limit_to) {
    if (hashname)
      strcpybuff(limit_to,hashname);
    else
      strcpybuff(limit_to,"???");
    return;
  }

  /* Error */
  if (!hashname)
    return;

  // xxc TEST
  /*
  setlocale( LC_ALL, "Japanese");
  _setmbcp(932);    // shift-jis
  setlocale( LC_ALL, ".932" );
  setlocale( LC_ALL, "[.932]" );
  CString st="";
  int lid=SetThreadLocale(MAKELCID(MAKELANGID(LANG_JAPANESE,SUBLANG_NEUTRAL),SORT_DEFAULT ));
  */

  /* Load specific language file */
  {
    int loops;
    CString err_msg="";
    // 2nd loop: load undefined strings
    for(loops=0;loops<2;loops++) {
      CString lbasename;
      
      {
        char name[256];
        sprintf(name,"LANGUAGE_%d",(loops==0)?(selected_lang+1):1);
        hashname=LANGINTKEY(name);
      }
      lbasename.Format("lang/%s.txt",hashname);
      CString lname=app+lbasename;
      if (!fexist((char*)LPCTSTR(lname)))
        lname=lbasename;
      FILE* fp=fopen(lname,"rb");
      if (fp) {
        char extkey[8192];
        TCHAR value[8192];
        while(!feof(fp)) {
          //int ssz;
          linput_cpp(fp,extkey,8000);
          linput_cpp(fp,value,8000);
          /*
          ssz=linput_cpp(fp,value,8000);
          CString st=value;
          AfxMessageBox(st);
          if (ssz>0) {
            int tst=0;
            int test=IsTextUnicode(value,ssz,&tst);
            unsigned short st2[1024];
            int ret=MultiByteToWideChar(CP_UTF8,0,(char*)value,ssz,st2,1024);
            if (ret>0) {
              char st3[1024]="";
              int ret2=WideCharToMultiByte(CP_THREAD_ACP,0,st2,ret,(char*)st3,1024,NULL,FALSE);
              if (ret2>0) {
                AfxMessageBox(st3);
              }
            }
          }
          */

          if (strnotempty(extkey) && strnotempty(value)) {
            int len;
            char* buff;
            char* intkey;
            
            intkey=LANGINTKEY(extkey);
            
            if (strnotempty(intkey)) {
              
              /* Increment for multiple definitions */
              {
                char* test=LANGSEL(intkey);
                if (strnotempty(test)) {
                  if (loops == 0) {
                    int increment=0;
                    size_t pos=strlen(extkey);
                    do {
                      increment++;
                      sprintf(extkey+pos,"%d",increment);
                      intkey=LANGINTKEY(extkey);
                      if (strnotempty(intkey))
                        test=LANGSEL(intkey);
                      else
                        test="";
                    }  while (strnotempty(test));
                  } else
                    intkey="";
                } else {
                  if (loops > 0) {
                    err_msg += intkey;
                    err_msg += " ";
                  }
                }
              }
              
              /* Add key */
              if (strnotempty(intkey)) {
                len = (int) strlen(value);
                buff = (char*)malloc(len+2);
                if (buff) {
                  conv_printf(value,buff);
                  coucal_add(NewLangStr,intkey,(intptr_t)buff);
                }
              }
              
            }
          } // if
        }  // while
        fclose(fp);
      } else {
        AfxMessageBox("FATAL ERROR\r\n'lang.def' file NOT FOUND!\r\nEnsure that the installation was complete!");
        exit(0);
      }
    }
    if (err_msg.GetLength()>0) {
      // AfxMessageBox("Error: undefined strings follows:\r\n"+err_msg);
    }
  }



#if 0
  app=app+"lang.h";
  if (!fexist((char*)LPCTSTR(app)))
    app="lang.h";
  
  FILE* fp=fopen(app,"rb");
  if (fp) {
    char s[8192];
    while(!feof(fp)) {
      linput_cpp(fp,s,8000);
      if (!strncmp(s,"#define ",8)) {
        char* a;
        char* name=s+8;
        a=name;
        while((*a!=' ') && (*a)) a++;
        if ((*a) && (strlen(name)>0) && (((int) a - (int) name)<64)) {
          *a++='\0';
          if (limit_to) {
            if (strcmp(name,limit_to))
              a=NULL;
          }
          if (a) {
            char* data;
            data=a;
            int toggle=0;
            char* start_str=NULL;
            int count=0;
            while(*a) {
              if (*a=='\"') {
                toggle++;
                if ((toggle%2)==1) {
                  if (count==selected_lang) {
                    start_str=a+1;
                  }
                  count++;
                } else {
                  if (start_str) {
                    char* buff;
                    int len;
                    len=(int) a - (int) start_str;
                    if (len) {
                      buff=(char*)malloc(len+2);
                      if (buff) {
                        int i=0,j=0;
                        buff[0]='\0';
                        //strncatbuff(buff,start_str,len);
                        while(i<len) {
                          switch(start_str[i]) {
                          case '\\': 
                            i++;
                            switch(start_str[i]) {
                            case 'a': buff[j]='\a'; break;
                            case 'b': buff[j]='\b'; break;
                            case 'f': buff[j]='\f'; break;
                            case 'n': buff[j]='\n'; break;
                            case 'r': buff[j]='\r'; break;
                            case 't': buff[j]='\t'; break;
                            case 'v': buff[j]='\v'; break;
                            case '\'': buff[j]='\''; break;
                            case '\"': buff[j]='\"'; break;
                            case '\\': buff[j]='\\'; break;
                            case '?': buff[j]='\?'; break;
                            default: buff[j]=start_str[i]; break;
                            }
                            break;
                            default: 
                              buff[j]=start_str[i]; 
                              break;
                          }
                          i++;
                          j++;
                        }
                        buff[j++]='\0';
                        if (!limit_to)
                          coucal_add(NewLangStr,name,(intptr_t)buff);
                        else {
                          strcpybuff(limit_to,buff);
                          free(buff);
                          return;
                        }
                      }
                    }
                    start_str=NULL;
                  }
                }
              }
              a++;
            }
          }
          
          //NewLangStr.SetAt(sname,st);
          /*
          } else {
          CString info;
          info.Format("Error in lang.h: %s",name);
          AfxMessageBox(info);
        */
        }
      }
    }


    fclose(fp);

  } else {
    AfxMessageBox("FATAL ERROR\r\n'lang.h' file NOT FOUND!\r\nEnsure that the installation was complete!");
    exit(0);
  }
#endif

  // Control limit_to
  if (limit_to)
    limit_to[0]='\0';

  // Set locale
  if (!limit_to) {
    CString charset = LANGUAGE_CHARSET;
    charset.TrimLeft();
    charset.TrimRight();
    charset.MakeLower();
    NewLangCP = CP_THREAD_ACP;
    NewLangFileCP = CP_THREAD_ACP;
#if 0
    if (charset.GetLength() > 0) {
      if (charset.Left(9) == "iso-8859-") {
        int iso = 0;
        int isoCP[] = {0, /* 0 */
          1252, /* ISO-8859-1 */
          1250, /* ISO-8859-2 */
          0, /* ISO-8859-3 */
          0, /* ISO-8859-4 */
          1251, /* ISO-8859-5 */
          1256, /* ISO-8859-6 */
          1253, /* ISO-8859-7 */
          1255, /* ISO-8859-8 */
          1254, /* ISO-8859-9 */
        };
        if (sscanf(charset.GetBuffer(0) + 9, "%d", &iso) == 1) {
          if (iso < sizeof(isoCP)/sizeof(isoCP[0])) {
            if (isoCP[iso] != 0) {
              NewLangFileCP = isoCP[iso];
            }
          }
        }
      } else if (charset.Left(8) == "windows-") {
        int windows = 0;
        if (sscanf(charset.GetBuffer(0) + 8, "%d", &windows) == 1) {
          NewLangFileCP = windows;
        }
      } else if (charset == "shift-jis") {
        NewLangFileCP = 932;
      } else if (charset == "big5") {
        NewLangFileCP = 950;
      } else if (charset == "gb2312") {
        NewLangFileCP = 936;
      } else {
        NewLangFileCP = CP_THREAD_ACP;
      }
    }
    WORD acp = GetACP();
    if (NewLangFileCP != CP_THREAD_ACP && NewLangFileCP != acp) {
      char* currName = LANGUAGE_WINDOWSID;
      LCID thl = GetThreadLocale();
      WORD sid = SORTIDFROMLCID(thl);
      WORD lid = 0;
      WinLangid* lids;
      if (currName[0]) {
        for( lids = (WinLangid*)&WINDOWS_LANGID ; lids->name != NULL ; lids++ ) {
          if (strcmp(currName, lids->name) == 0) {
            lid = lids->langId;
            break;
          }
        }
        if (lid != 0) {
          SetThreadLocale(MAKELCID(lid, sid));
        }
      }
    }
#endif

  }

}