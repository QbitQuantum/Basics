int WDL_CursesEditor::onChar(int c)
{
  if (m_state == -3 || m_state == -4)
  {
    switch (c)
    {
       case '\r': case '\n':
         m_state=0;
         runSearch();
       break;
       case 27: 
         m_state=0; 
         draw();
         draw_message("Find cancelled.");
         setCursor();
       break;
       case KEY_BACKSPACE: if (s_search_string[0]) s_search_string[strlen(s_search_string)-1]=0; m_state=-4; break;
       default: 
         if (VALIDATE_TEXT_CHAR(c)) 
         { 
           int l=m_state == -3 ? 0 : strlen(s_search_string); 
           m_state = -4;
           if (l < (int)sizeof(s_search_string)-1) { s_search_string[l]=c; s_search_string[l+1]=0; } 
         } 
        break;
     }
     if (m_state)
     {
       attrset(m_color_message);
       bkgdset(m_color_message);
       mvaddstr(LINES-1,29,s_search_string);
       clrtoeol(); 
       attrset(0);
       bkgdset(0);
     }
     return 0;
  }
  if (c==KEY_DOWN || c==KEY_UP || c==KEY_PPAGE||c==KEY_NPAGE || c==KEY_RIGHT||c==KEY_LEFT||c==KEY_HOME||c==KEY_END)
  {
    if (GetAsyncKeyState(VK_SHIFT)&0x8000)      
    {
      if (!m_selecting)
      {
        m_select_x2=m_select_x1=m_curs_x; m_select_y2=m_select_y1=m_curs_y;
        m_selecting=1;
      }
    }
    else if (m_selecting) { m_selecting=0; draw(); }
  }

  switch(c)
  {
    case 407:
    case 'Z'-'A'+1:
      if (!(GetAsyncKeyState(VK_SHIFT)&0x8000))
      {
        if (m_undoStack_pos > 0)
        {
           m_undoStack_pos--;
           loadUndoState(m_undoStack.Get(m_undoStack_pos));
           draw();
           char buf[512];
           snprintf(buf,sizeof(buf),"Undid action -- %d items in undo buffer",m_undoStack_pos);
           draw_message(buf);
           setCursor();
        }
        else draw_message("Can't Undo");

        break;
      }
      // fall through
    case 'Y'-'A'+1:
      if (m_undoStack_pos < m_undoStack.GetSize()-1)
      {
        m_undoStack_pos++;
        loadUndoState(m_undoStack.Get(m_undoStack_pos));
        draw();
        char buf[512];
        snprintf(buf,sizeof(buf),"Redid action -- %d items in redo buffer",m_undoStack.GetSize()-m_undoStack_pos-1);
        draw_message(buf);
        setCursor();
      }
      else draw_message("Can't Redo");  
    break;
    case KEY_IC:
      if (!(GetAsyncKeyState(VK_SHIFT)&0x8000))
      {
        s_overwrite=!s_overwrite;
        setCursor();
        break;
      }
      // fqll through
    case 'V'-'A'+1:
      {
        // generate a m_clipboard using win32 clipboard data
        WDL_PtrList<const char> lines;
        WDL_String buf;
#ifdef WDL_IS_FAKE_CURSES
        if (CURSES_INSTANCE)
        {
          OpenClipboard(CURSES_INSTANCE->m_hwnd);
          HANDLE h=GetClipboardData(CF_TEXT);
          if (h)
          {
            char *t=(char *)GlobalLock(h);
            int s=GlobalSize(h);
            buf.Set(t,s);
            GlobalUnlock(t);        
          }
          CloseClipboard();
        }
        else
#endif
        {
          buf.Set(s_fake_clipboard.Get());
        }

        if (buf.Get() && buf.Get()[0])
        {
          char *src=buf.Get();
          while (*src)
          {
            char *seek=src;
            while (*seek && *seek != '\r' && *seek != '\n') seek++;
            char hadclr=*seek;
            if (*seek) *seek++=0;
            lines.Add(src);

            if (hadclr == '\r' && *seek == '\n') seek++;

            if (hadclr && !*seek)
            {
              lines.Add("");
            }
            src=seek;
          }
        }
        if (lines.GetSize())
        {
          removeSelect();
          // insert lines at m_curs_y,m_curs_x
          if (m_curs_y >= m_text.GetSize()) m_curs_y=m_text.GetSize()-1;
          if (m_curs_y < 0) m_curs_y=0;

          preSaveUndoState();
          WDL_FastString poststr;
          int x;
          int indent_to_pos = -1;
          for (x = 0; x < lines.GetSize(); x ++)
          {
            WDL_FastString *str=m_text.Get(m_curs_y);
            const char *tstr=lines.Get(x);
            if (!tstr) tstr="";
            if (!x)
            {
              if (str)
              {
                if (m_curs_x < 0) m_curs_x=0;
                int tmp=str->GetLength();
                if (m_curs_x > tmp) m_curs_x=tmp;
  
                poststr.Set(str->Get()+m_curs_x);
                str->SetLen(m_curs_x);

                const char *p = str->Get();
                while (*p == ' ' || *p == '\t') p++;
                if (!*p && p > str->Get())
                {
                  if (lines.GetSize()>1)
                  {
                    while (*tstr == ' ' || *tstr == '\t') tstr++;
                  }
                  indent_to_pos = m_curs_x;
                }

                str->Append(tstr);
              }
              else
              {
                m_text.Insert(m_curs_y,(str=new WDL_FastString(tstr)));
              }
              if (lines.GetSize() > 1)
              {
                m_curs_y++;
              }
              else
              {
                m_curs_x = str->GetLength();
                str->Append(poststr.Get());
              }
           }
           else if (x == lines.GetSize()-1)
           {
             WDL_FastString *s=newIndentedFastString(tstr,indent_to_pos);
             m_curs_x = s->GetLength();
             s->Append(poststr.Get());
             m_text.Insert(m_curs_y,s);
           }
           else
           {
             m_text.Insert(m_curs_y,newIndentedFastString(tstr,indent_to_pos));
             m_curs_y++;
           }
         }
         draw();
         draw_message("Pasted");
         saveUndoState();
         setCursor();
       }
       else 
       {
         draw_message("Clipboard empty");
         setCursor();
       }
     }
  break;

  case KEY_DC:
    if (!(GetAsyncKeyState(VK_SHIFT)&0x8000))
    {
      WDL_FastString *s;
      if (m_selecting)
      {
        preSaveUndoState();
        removeSelect();
        draw();
        saveUndoState();
        setCursor();
      }
      else if ((s=m_text.Get(m_curs_y)))
      {
        if (m_curs_x < s->GetLength())
        {
          preSaveUndoState();

          bool hadCom = LineCanAffectOtherLines(s->Get(),m_curs_x,1); 
          s->DeleteSub(m_curs_x,1);
          if (!hadCom) hadCom = LineCanAffectOtherLines(s->Get(),-1,-1);
          draw(hadCom ? -1 : m_curs_y);
          saveUndoState();
          setCursor();
        }
        else // append next line to us
        {
          if (m_curs_y < m_text.GetSize()-1)
          {
            preSaveUndoState();

            WDL_FastString *nl=m_text.Get(m_curs_y+1);
            if (nl)
            {
              s->Append(nl->Get());
            }
            m_text.Delete(m_curs_y+1,true);

            draw();
            saveUndoState();
            setCursor();
          }
        }
      }
      break;
    }
  case 'C'-'A'+1:
  case 'X'-'A'+1:
    if (m_selecting)
    {
      if (c!= 'C'-'A'+1) m_selecting=0;
      int miny,maxy,minx,maxx;
      int x;
      getselectregion(minx,miny,maxx,maxy);
      const char *status="";
      char statusbuf[512];

      if (minx != maxx|| miny != maxy) 
      {
        int bytescopied=0;
        s_fake_clipboard.Set("");

        int lht=0,fht=0;
        if (c != 'C'-'A'+1) preSaveUndoState();

        for (x = miny; x <= maxy; x ++)
        {
          WDL_FastString *s=m_text.Get(x);
          if (s) 
          {
            const char *str=s->Get();
            int sx,ex;
            if (x == miny) sx=max(minx,0);
            else sx=0;
            int tmp=s->GetLength();
            if (sx > tmp) sx=tmp;
      
            if (x == maxy) ex=min(maxx,tmp);
            else ex=tmp;
      
            bytescopied += ex-sx + (x!=maxy);
            if (s_fake_clipboard.Get() && s_fake_clipboard.Get()[0]) s_fake_clipboard.Append("\r\n");
            s_fake_clipboard.Append(ex-sx?str+sx:"",ex-sx);

            if (c != 'C'-'A'+1)
            {
              if (sx == 0 && ex == tmp) // remove entire line
              {
                m_text.Delete(x,true);
                if (x==miny) miny--;
                x--;
                maxy--;
              }
              else { if (x==miny) fht=1; if (x == maxy) lht=1; s->DeleteSub(sx,ex-sx); }
            }
          }
        }
        if (fht && lht && miny+1 == maxy)
        {
          m_text.Get(miny)->Append(m_text.Get(maxy)->Get());
          m_text.Delete(maxy,true);
        }
        if (c != 'C'-'A'+1)
        {
          m_curs_y=miny;
          if (m_curs_y < 0) m_curs_y=0;
          m_curs_x=minx;
          saveUndoState();
          snprintf(statusbuf,sizeof(statusbuf),"Cut %d bytes",bytescopied);
        }
        else
          snprintf(statusbuf,sizeof(statusbuf),"Copied %d bytes",bytescopied);

#ifdef WDL_IS_FAKE_CURSES
        if (CURSES_INSTANCE)
        {
          int l=s_fake_clipboard.GetLength()+1;
          HANDLE h=GlobalAlloc(GMEM_MOVEABLE,l);
          void *t=GlobalLock(h);
          memcpy(t,s_fake_clipboard.Get(),l);
          GlobalUnlock(h);
          OpenClipboard(CURSES_INSTANCE->m_hwnd);
          EmptyClipboard();
          SetClipboardData(CF_TEXT,h);
          CloseClipboard();
        }
#endif

        status=statusbuf;
      }
      else status="No selection";

      draw();
      draw_message(status);
      setCursor();
    }
  break;
  case 'A'-'A'+1:
    m_selecting=1;
    m_select_x1=0;
    m_select_y1=0;
    m_select_y2=m_text.GetSize()-1;
    m_select_x2=0;
    if (m_text.Get(m_select_y2))
      m_select_x2=m_text.Get(m_select_y2)->GetLength();
    draw();
    setCursor();
  break;
  case 27:
    if (m_selecting)
    {
      m_selecting=0;
      draw();
      setCursor();
      break;
    }
  return 0;
  case KEY_F3:
  case 'G'-'A'+1:
    if (s_search_string[0])
    {
      runSearch();
      return 0;
    }
  case 'F'-'A'+1:
    draw_message("");
    attrset(m_color_message);
    bkgdset(m_color_message);
    mvaddstr(LINES-1,0,"Find string (ESC to cancel): ");
    addstr(s_search_string);
    clrtoeol();
    attrset(0);
    bkgdset(0);
    m_state=-3; // find, initial (m_state=4 when we've typed something)
  return 0;
  case KEY_DOWN:
    {
      if (GetAsyncKeyState(VK_CONTROL)&0x8000)      
      {
        if (m_offs_y < m_text.GetSize() - 4) 
        {
          m_offs_y++;
          if (m_curs_y < m_offs_y) m_curs_y = m_offs_y;
          draw();
        }
      }
      else
      {
        m_curs_y++;
        if(m_curs_y>=m_text.GetSize()) m_curs_y=m_text.GetSize()-1;
        if(m_curs_y < 0) m_curs_y=0;
      }
      if (m_selecting) { setCursor(1); m_select_x2=m_curs_x; m_select_y2=m_curs_y; draw(); }
      setCursor(1);
    }
  break;
  case KEY_UP:
    {
      if (GetAsyncKeyState(VK_CONTROL)&0x8000)      
      {
        if (m_offs_y>0) 
        {
          m_offs_y--;
          if (m_curs_y>m_offs_y + getVisibleLines() - 1) m_curs_y = m_offs_y + getVisibleLines() - 1;
          if (m_curs_y < 0) m_curs_y=0;
          draw();
        }
      }
      else
      {
        if(m_curs_y>0) m_curs_y--;
      }
      if (m_selecting) { setCursor(1); m_select_x2=m_curs_x; m_select_y2=m_curs_y; draw(); }
      setCursor(1);
    }
  break;
  case KEY_PPAGE:
    {
      if (m_curs_y > m_offs_y) 
      {
        m_curs_y=m_offs_y;
        if (m_curs_y < 0) m_curs_y=0;
      }
      else 
      {
        m_curs_y -= getVisibleLines();
        if (m_curs_y < 0) m_curs_y=0;
        m_offs_y=m_curs_y;
      }
      if (m_selecting) { setCursor(1); m_select_x2=m_curs_x; m_select_y2=m_curs_y; }
      draw();
      setCursor(1);
    }
  break;
  case KEY_NPAGE:
    {
      if (m_curs_y >= m_offs_y+getVisibleLines() - 1) m_offs_y=m_curs_y+1;
      m_curs_y = m_offs_y+getVisibleLines() - 1;
      if (m_curs_y >= m_text.GetSize()) m_curs_y=m_text.GetSize()-1;
      if (m_curs_y < 0) m_curs_y=0;
      if (m_selecting) { setCursor(1); m_select_x2=m_curs_x; m_select_y2=m_curs_y; }
      draw();
      setCursor(1);
    }
  break;
  case KEY_RIGHT:
    {
      if (1) // wrap across lines
      {
        WDL_FastString *s = m_text.Get(m_curs_y);
        if (s && m_curs_x >= s->GetLength() && m_curs_y < m_text.GetSize()) { m_curs_y++; m_curs_x = -1; }
      }

      if(m_curs_x<0) 
      {
        m_curs_x=0;
      }
      else
      {
        if (GetAsyncKeyState(VK_CONTROL)&0x8000)      
        {
          WDL_FastString *s = m_text.Get(m_curs_y);
          if (!s||m_curs_x >= s->GetLength()) break;
          int lastType = categorizeCharForWordNess(s->Get()[m_curs_x++]);
          while (m_curs_x < s->GetLength())
          {
            int thisType = categorizeCharForWordNess(s->Get()[m_curs_x]);
            if (thisType != lastType && thisType != 0) break;
            lastType=thisType;
            m_curs_x++;
          }
        }
        else 
        {
          m_curs_x++;
        }
      }
      if (m_selecting) { setCursor(); m_select_x2=m_curs_x; m_select_y2=m_curs_y; draw(); }
      setCursor();
    }
  break;
  case KEY_LEFT:
    {
      bool doMove=true;
      if (1) // wrap across lines
      {
        WDL_FastString *s = m_text.Get(m_curs_y);
        if (s && m_curs_y>0 && m_curs_x == 0) 
        { 
          s = m_text.Get(--m_curs_y);
          if (s) 
          {
            m_curs_x = s->GetLength(); 
            doMove=false;
          }
        }
      }

      if(m_curs_x>0 && doMove) 
      {
        if (GetAsyncKeyState(VK_CONTROL)&0x8000)      
        {
          WDL_FastString *s = m_text.Get(m_curs_y);
          if (!s) break;
          if (m_curs_x > s->GetLength()) m_curs_x = s->GetLength();
          m_curs_x--;

          int lastType = categorizeCharForWordNess(s->Get()[m_curs_x--]);
          while (m_curs_x >= 0)
          {
            int thisType = categorizeCharForWordNess(s->Get()[m_curs_x]);
            if (thisType != lastType && lastType != 0) break;
            lastType=thisType;
            m_curs_x--;
          }
          m_curs_x++;
        }
        else 
        {
          m_curs_x--;
        }
      }
      if (m_selecting) { setCursor(); m_select_x2=m_curs_x; m_select_y2=m_curs_y; draw(); }
      setCursor();
    }
  break;
  case KEY_HOME:
    {
      m_curs_x=0;
      if (m_selecting) { setCursor(); m_select_x2=m_curs_x; m_select_y2=m_curs_y; draw(); }
      setCursor();
    }
  break;
  case KEY_END:
    {
      if (m_text.Get(m_curs_y)) m_curs_x=m_text.Get(m_curs_y)->GetLength();
      if (m_selecting) { setCursor(); m_select_x2=m_curs_x; m_select_y2=m_curs_y; draw(); }
      setCursor();
    }
  break;
  case KEY_BACKSPACE: // backspace, baby
    if (m_selecting)
    {
      preSaveUndoState();
      removeSelect();
      draw();
      saveUndoState();
      setCursor();
    }
    else if (m_curs_x > 0)
    {
      WDL_FastString *tl=m_text.Get(m_curs_y);
      if (tl)
      {
        preSaveUndoState();

        bool hadCom = LineCanAffectOtherLines(tl->Get(), m_curs_x-1,1);
        tl->DeleteSub(--m_curs_x,1);
        if (!hadCom) hadCom = LineCanAffectOtherLines(tl->Get(),-1,-1);
        draw(hadCom?-1:m_curs_y);
        saveUndoState();
        setCursor();
      }
    }
    else // append current line to previous line
    {
      WDL_FastString *fl=m_text.Get(m_curs_y-1), *tl=m_text.Get(m_curs_y);
      if (!tl) 
      {
        m_curs_y--;
        if (fl) m_curs_x=fl->GetLength();
        draw();
        saveUndoState();
        setCursor();
      }
      else if (fl)
      {
        preSaveUndoState();
        m_curs_x=fl->GetLength();
        fl->Append(tl->Get());

        m_text.Delete(m_curs_y--,true);
        draw();
        saveUndoState();
        setCursor();
      }
    }
  break;
  case 'L'-'A'+1:
    draw();
    setCursor();
  break;
  case 13: //KEY_ENTER:
    //insert newline
    preSaveUndoState();

    if (m_selecting) { removeSelect(); draw(); setCursor(); }
    if (m_curs_y >= m_text.GetSize())
    {
      m_curs_y=m_text.GetSize();
      m_text.Add(new WDL_FastString);
    }
    if (s_overwrite)
    {
      WDL_FastString *s = m_text.Get(m_curs_y);
      int plen=0;
      const char *pb=NULL;
      if (s)
      {
        pb = s->Get();
        while (plen < m_curs_x && (pb[plen]== ' ' || pb[plen] == '\t')) plen++;
      }
      if (++m_curs_y >= m_text.GetSize())
      {
        m_curs_y = m_text.GetSize();
        WDL_FastString *ns=new WDL_FastString;
        if (plen>0) ns->Set(pb,plen);
        m_text.Insert(m_curs_y,ns);
      }
      s = m_text.Get(m_curs_y);
      if (s && plen > s->GetLength()) plen=s->GetLength();
      m_curs_x=plen;
    }
    else 
    {
      WDL_FastString *s = m_text.Get(m_curs_y);
      if (s)
      {
        if (m_curs_x > s->GetLength()) m_curs_x = s->GetLength();
        WDL_FastString *nl = new WDL_FastString();
        int plen=0;
        const char *pb = s->Get();
        while (plen < m_curs_x && (pb[plen]== ' ' || pb[plen] == '\t')) plen++;

        if (plen>0) nl->Set(pb,plen);

        nl->Append(pb+m_curs_x);
        m_text.Insert(++m_curs_y,nl);
        s->SetLen(m_curs_x);
        m_curs_x=plen;
      }
    }
    m_offs_x=0;

    draw();
    saveUndoState();
    setCursor();
  break;
  case '\t':
    if (m_selecting)
    {
      preSaveUndoState();

      bool isRev = !!(GetAsyncKeyState(VK_SHIFT)&0x8000);
      indentSelect(isRev?-m_indent_size:m_indent_size);
      // indent selection:
      draw();
      setCursor();
      saveUndoState();
      break;
    }
  default:
    //insert char
    if(VALIDATE_TEXT_CHAR(c))
    { 
      preSaveUndoState();

      if (m_selecting) { removeSelect(); draw(); setCursor(); }
      if (!m_text.Get(m_curs_y)) m_text.Insert(m_curs_y,new WDL_FastString);

      WDL_FastString *ss;
      if ((ss=m_text.Get(m_curs_y)))
      {
        char str[64];
        int slen ;
        if (c == '\t') 
        {
          slen = min(m_indent_size,64);
          if (slen<1) slen=1;
          int x; 
          for(x=0;x<slen;x++) str[x]=' ';
        }
        else
        {
          str[0]=c;
          slen = 1;
        }


        bool hadCom = LineCanAffectOtherLines(ss->Get(),-1,-1);
        if (s_overwrite)
        {
          if (!hadCom) hadCom = LineCanAffectOtherLines(ss->Get(),m_curs_x,slen);
          ss->DeleteSub(m_curs_x,slen);
        }
        ss->Insert(str,m_curs_x,slen);
        if (!hadCom) hadCom = LineCanAffectOtherLines(ss->Get(),m_curs_x,slen);

        m_curs_x += slen;
        draw(hadCom ? -1 : m_curs_y);
      }
      saveUndoState();
      setCursor();
    }
    break;
  }
  return 0;
}