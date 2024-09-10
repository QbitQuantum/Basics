uint32 SearchResults::onMessage(uint32 message, uint32 wParam, uint32 lParam)
{
  switch (message)
  {
  case WM_ADDFILE:
    EnterCriticalSection(&lock);
    while (getCount() < items.length())
      addItem(getCount(), true);
    LeaveCriticalSection(&lock);
    return 0;
  case WM_NOTIFY:
    {
      NMHDR* pnm = (NMHDR*) lParam;
      if (pnm->code == LVN_ITEMACTIVATE)
      {
        NMITEMACTIVATE* pia = (NMITEMACTIVATE*) pnm;
        if (pia->iItem >= 0 && pia->iItem < items.length())
        {
          SendMessage(getApp()->getMainWindow(), WM_PUSHVIEW,
            (uint32) new ReplayViewItem(items[pia->iItem].path), 0);
        }
        return 0;
      }
      else if (pnm->code == LVN_BEGINDRAG)
      {
        Array<String> sel;
        getSelList(sel);
        if (sel.length())
        {
          HGLOBAL data = CreateFileDrop(sel);
          if (data)
            DoDragDrop(CF_HDROP, data, DROPEFFECT_MOVE | DROPEFFECT_COPY | DROPEFFECT_LINK);
        }
        return TRUE;
      }
      else if (pnm->code == LVN_COLUMNCLICK)
      {
        NMLISTVIEW* lv = (NMLISTVIEW*) lParam;
        bool colShow[colCount] = {true,
          cfg.selColumns & COL_SAVED,
          cfg.selColumns & COL_SIZE,
          cfg.selColumns & COL_NAME,
          cfg.selColumns & COL_RATIO,
          cfg.selColumns & COL_LENGTH,
          cfg.selColumns & COL_MODE
        };
        int col = lv->iSubItem;
        for (int i = 0; i < col && col < colCount - 1; i++)
          if (!colShow[i])
            col++;
        int pos = 0;
        while (pos < colCount - 1 && cfg.colSort[pos] != col && cfg.colSort[pos] != ~col)
          pos++;
        if (pos == 0)
          cfg.colSort[0] = ~cfg.colSort[0];
        else
        {
          for (int i = pos; i > 0; i--)
            cfg.colSort[i] = cfg.colSort[i - 1];
          cfg.colSort[0] = col;
        }
        rebuild();
      }
      else if (pnm->code == HDN_ENDDRAG)
        PostMessage(hWnd, WM_POSTHEADERDRAG, 0, 0);
      else if (pnm->code == HDN_ENDTRACK)
      {
        NMHEADER* nhdr = (NMHEADER*) pnm;
        bool colShow[colCount] = {true,
          cfg.selColumns & COL_SAVED,
          cfg.selColumns & COL_SIZE,
          cfg.selColumns & COL_NAME,
          cfg.selColumns & COL_RATIO,
          cfg.selColumns & COL_LENGTH,
          cfg.selColumns & COL_MODE
        };
        int count = 0;
        int colUnpos[colCount];
        for (int i = 0; i < colCount; i++)
          if (colShow[i])
            colUnpos[count++] = i;
        if (nhdr->iItem >= 0 && nhdr->iItem < count &&
          nhdr->pitem && nhdr->pitem->mask & HDI_WIDTH)
        {
          int col = colUnpos[nhdr->iItem];
          cfg.colWidth[col] = nhdr->pitem->cxy;
        }
      }
      else if (pnm->code == LVN_KEYDOWN)
      {
        NMLVKEYDOWN* kd = (NMLVKEYDOWN*) lParam;
        bool controlKey = ((GetAsyncKeyState(VK_CONTROL) & 0x8000) || wParam == VK_CONTROL);
        if (kd->wVKey == 'C' && controlKey)
        {
          Array<String> sel;
          getSelList(sel);
          if (sel.length())
          {
            HGLOBAL hDrop = CreateFileDrop(sel);
            SetClipboard(CF_HDROP, hDrop);
          }
        }
        else if (kd->wVKey == VK_DELETE)
        {
          Array<String> sel;
          getSelList(sel);
          if (sel.length())
          {
            char* str = FileListToString(sel);
            SHFILEOPSTRUCT fileop;
            memset(&fileop, 0, sizeof fileop);
            fileop.wFunc = FO_DELETE;
            fileop.pFrom = str;
            SHFileOperationEx(&fileop);
          }
        }
        return 0;
      }
    }
    break;
  case WM_POSTHEADERDRAG:
    {
      bool colShow[colCount] = {true,
        cfg.selColumns & COL_SAVED,
        cfg.selColumns & COL_SIZE,
        cfg.selColumns & COL_NAME,
        cfg.selColumns & COL_RATIO,
        cfg.selColumns & COL_LENGTH,
        cfg.selColumns & COL_MODE
      };
      int count = 0;
      int colUnpos[colCount];
      for (int i = 0; i < colCount; i++)
        if (colShow[i])
          colUnpos[count++] = i;
      int colOrder[colCount];
      ListView_GetColumnOrderArray(hWnd, count, colOrder);
      int pos = 0;
      for (int i = 0; i < colCount; i++)
        if (colShow[cfg.colOrder[i]])
          cfg.colOrder[i] = colUnpos[colOrder[pos++]];
    }
    return 0;
  }
  return ListFrame::onMessage(message, wParam, lParam);
}