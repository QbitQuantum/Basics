 void showFunction(HWND hwnd, EDITDATA *p, int ch)
 {
     sqlite3_int64 id, baseid;
     CCFUNCDATA *functionData = NULL;
     char name[2046], *q = name;
     int end = p->selstartcharpos;
     int pos = p->selstartcharpos - 1;
     POINT cpos;
     SIZE size;
     int curArg = 0;
     if (instring(p->cd->text, &p->cd->text[p->selstartcharpos]))
         return;
     p->cd->selecting = FALSE;
     
     if (pos <= 0 || PropGetInt(NULL, "CODE_COMPLETION") == 0)
         return ;
     if (ch == '(' || ch == ',' && !IsWindowVisible(hwndShowFunc))
     {
         char name[512], *p1;
         int pos;
         int i;
         int commaCount = 0;
         DWINFO *info = (DWINFO *)GetWindowLong(GetParent(hwnd), 0);
         int lineno = SendMessage(hwnd, EM_EXLINEFROMCHAR, 0, p->selstartcharpos)+1;
         CCFUNCDATA * functionData = NULL;
         BOOL parsed = FALSE;
         CHARRANGE range;
         if (ch == ',')
         {
             int nesting  =1 ;
             pos = p->selendcharpos-1;
             while (nesting > 0 && pos> 0 && p->cd->text[pos].ch != '{' && p->cd->text[pos].ch != '}')
             {
                 if (p->cd->text[pos].ch == ')')
                     nesting++;
                 else if (p->cd->text[pos].ch == '(')
                     nesting --;
                 else if (p->cd->text[pos].ch == ',' && nesting == 1)
                     commaCount++;
                 pos--;
             }
             if (nesting)
                 return;
             if (!pos || !isalnum(p->cd->text[pos-1].ch) && p->cd->text[pos-1].ch != '_')
                 return;
             range.cpMin = pos;
             range.cpMax = pos;
         }
         else
         {
             range.cpMin = p->selendcharpos-1;
             range.cpMax = p->selendcharpos-1;
         }
         GetWordSpan(p, &range);
         if (range.cpMin == range.cpMax)
             return;
         pos = range.cpMin;
         while (pos && isspace(p->cd->text[pos-1].ch))
         {
             pos--;
         }
         if (pos && p->cd->text[pos-1].ch == ':')
         {
             pos = CPPScanBackward(p, range.cpMax, TRUE);
         }
         else
         {
             pos = range.cpMin;
         }
         for (i=pos; i < range.cpMax; i++)
             name[i-pos] = p->cd->text[i].ch;
         name[i-pos] = 0;
         p1 = name;
         GetQualifiedName(name + i-pos + 1, &p1, FALSE, FALSE);
         strcpy(name, name +i-pos + 1);
         while (pos && isspace(p->cd->text[pos-1].ch))
         {
             pos--;
         }
         if (pos && (p->cd->text[pos-1].ch == '.' || p->cd->text[pos-1].ch == '>'))
         {
             int start = 0;
             start = CPPScanBackward(p, p->selendcharpos, TRUE);
             if (start != pos)
             {
                 char qual[2048];
                 for (i=start; i < pos; i++)
                     qual[i-start] = p->cd->text[i].ch;
                 qual[i-start] = 0;
                 parsed = TRUE;
                 sprintf(qual + strlen(qual), "@%s", name);
                 functionData = ccLookupFunctionList(lineno, info->dwName, qual);
             }
         }
         if (!parsed)
         {
             CCFUNCDATA **scan;
             char funcbase[2048], nsbase[512], abase[512];
             abase[0] = 0;
             GetContainerData(lineno, info->dwName, nsbase, funcbase);
             if (strrchr(name, '@') != name)
             {
                 char *p = strrchr(name, '@');
                 strncpy(abase, name, p - name);
                 abase[p-name] = 0;
                 strcpy(name, p);
                 *p = 0;
             }
             functionData = ccLookupFunctionList(lineno, info->dwName, name);
             if (!functionData)
             {
                 name[0] = '_';
                 functionData = ccLookupFunctionList(lineno, info->dwName, name);
                 name[0] = '@';
             }
             scan = &functionData;
             while (*scan)
             {
                 char nsbase2[2048];
                 if ((*scan)->args->member)
                 {
                     if  (!funcbase[0] || strncmp(funcbase, (*scan)->fullname, strlen(funcbase)))
                     {
                         CCFUNCDATA *remove = *scan;
                         *scan = (*scan)->next;
                         remove->next = NULL;
                         ccFreeFunctionList(remove);
                     }
                     else
                     {
                         scan = &(*scan)->next;
                     }
                 }
                 else
                 {
                     char *last, *p ;
                     int nesting = 0;
                     p = last = (*scan)->fullname;
                     while (*p)
                     {
                         switch(*p)
                         {
                             case '@':
                                 if (!nesting)
                                     last = p;
                                 break;
                             case '#':
                                 nesting++;
                                 break;
                             case '~':
                                 if (nesting)
                                     nesting--;
                                 break;
                         }
                         p++;
                     }
                     if (last != (*scan)->fullname
                         && (strncmp((*scan)->fullname, funcbase, last - (*scan)->fullname)
                           || funcbase[last - (*scan)->fullname] != '@' && funcbase[last - (*scan)->fullname] != 0))
                     {    
                         BOOL found = FALSE;                        
                         char *p = nsbase;
                         while (*p)
                         {
                             char *q = nsbase2;
                             while (*p && *p != ';')
                                 *q++ = *p++;
                             if (*p)
                                 p++;
                             *q = 0;
                              if  (!strncmp((*scan)->fullname, nsbase2, last - (*scan)->fullname)
                                                           &&( nsbase2[last - (*scan)->fullname] == '@' || nsbase2[last - (*scan)->fullname] == 0))
                              {
                                  found = TRUE;
                                  break;
                              }
                         }
                         if (!found)
                         {
                             strcpy(nsbase2, abase);                                
                              if  (!strncmp((*scan)->fullname, nsbase2, last - (*scan)->fullname)
                                                           && nsbase2[last - (*scan)->fullname] == 0)
                              {
                                  found = TRUE;
                              }
                         }
                         if (!found)
                         {
                             CCFUNCDATA *remove = *scan;
                             *scan = (*scan)->next;
                             remove->next = NULL;
                             ccFreeFunctionList(remove);
                         }
                         else
                             scan = &(*scan)->next;
                     }
                     else {
                         BOOL found = abase[0] == '\0';
                                                 
                         strcpy(nsbase2, abase);                                
                          if  (!strncmp((*scan)->fullname, nsbase2, last - (*scan)->fullname)
                                                       && nsbase2[last - (*scan)->fullname] == 0)
                          {
                              found = TRUE;
                          }
                         if (!found)
                         {
                             CCFUNCDATA *remove = *scan;
                             *scan = (*scan)->next;
                             remove->next = NULL;
                             ccFreeFunctionList(remove);
                         }
                         else
                         {
                             scan = &(*scan)->next;
                         }
                     }
                 }
             }
             
         }
         if (functionData)
         {
             if (!hwndShowFunc)
             {
                 hwndShowFunc = CreateWindowEx(0 | /*WS_EX_TOPMOST | WS_EX_LAYERED |*/ WS_EX_NOACTIVATE, "xccfuncclass", "",
                                             (WS_CHILD),
                                             CW_USEDEFAULT, CW_USEDEFAULT,
                                             CW_USEDEFAULT, CW_USEDEFAULT,
                                             hwndFrame, 0, GetModuleHandle(0), 0);
                 // done this way to associate the popup with the application rather than the desktop
                 SetWindowLong(hwndShowFunc, GWL_STYLE, (GetWindowLong(hwndShowFunc, GWL_STYLE) & ~WS_CHILD ) | WS_POPUP);
             }
             SendMessage(hwndShowFunc, WM_USER, 0, (LPARAM)functionData);
             SendMessage(hwndShowFunc, WM_USER+1, (WPARAM)hwnd, (LPARAM)p);
             SendMessage(hwndShowFunc, WM_USER+2, commaCount, 0);
             ShowWindow(hwndShowFunc, SW_SHOW);
             SetFocus(hwnd);
         }
     }
 }