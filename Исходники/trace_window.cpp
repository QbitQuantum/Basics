void TraceWindow::Draw_JumpLog(HDC p_hdc) {
  SetScrollMax(GetAllLine());

  HDC hdc = m_dlg->getBackDC();

  HBRUSH hbBG = (HBRUSH)CreateSolidBrush(COLOR_BG);
  HBRUSH hbFixedBG = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_3DFACE));
  HBRUSH hbSelect = CreateSolidBrush(COLOR_SELECT);

  SetBkColor(p_hdc, RGB(0, 0, 0));
  SetBkMode(p_hdc, TRANSPARENT);
  g_dbg->setFontToFixed(p_hdc);

  RECT clientrect;
  GetClientRect(m_dlg->getHwnd(), &clientrect);

  DrawListFrame();

  SetTextColor(p_hdc, RGB(255, 255, 255));

  char str[1024];
  for (int i = 0; i < GetPageLine() + 1; i++) {
    int left = 0;
    for (u32 j = 0; j < m_col_array.size(); j++) {
      RECT selrect;
      selrect.top    = i * kFontSize + GetListTop();
      selrect.bottom  = (i + 1) * kFontSize + GetListTop();
      selrect.left  = left + 1;
      selrect.right  = left + m_col_array[j]->width;

      // 最後はウィンドウの端まで
      if (j == m_col_array.size() - 1) selrect.right = clientrect.right;

      if (i + m_head < GetAllLine() && m_sel == i + m_head) FillRect(hdc, &selrect, hbSelect);
      else FillRect(hdc, &selrect, hbBG);

      if (i + m_head < GetAllLine()) {
        switch (j) {
        case 0:
          sprintf(str, "%08x", g_dbg->jumplog(i + m_head)->va());
          TextOut(hdc, left + 4, kFontSize * i + GetListTop(), str, strlen(str));
          break;
        case 1:
          //if (g_dbg->jumplog(i + m_head)->m_repeat.size() > 0) {
          //  int ridx = g_dbg->jumplog(i + m_head)->m_repeat.size() - 1;
          //  sprintf(str, "    cnt=%d len=%d lv=%d",
          //    g_dbg->jumplog(i + m_head)->m_repeat[ridx]->count,
          //    g_dbg->jumplog(i + m_head)->m_repeat[ridx]->len,
          //    g_dbg->getJumpLogNestLevel(i + m_head, ridx) + ridx - 1);
          //  TextOut(hdc, left + 4, kFontSize * i + GetListTop(), str, strlen(str));
          //}
          break;
        }
      }
      left += m_col_array[j]->width;
    }
  }

  // ヘッダ行を上書きしてしまうのでクリッピング
  IntersectClipRect(hdc, clientrect.left, GetListTop(), clientrect.right, clientrect.bottom);
  
  // ネストブロックを図で示す
  HPEN hpPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 64));
  SelectObject(hdc, hpPen);
  SelectObject(p_hdc, m_small_font);
  for (int i = 0; i < g_dbg->jumplog_count(); i++) {
    for (u32 j = 0; j < g_dbg->jumplog(i)->m_repeat.size(); j++) {
      const int kNestIndent = 12;
      int level = g_dbg->getJumpLogNestLevel(i, j) + j;
      int range = g_dbg->jumplog(i)->m_repeat[j]->len - 1;
      int count = g_dbg->jumplog(i)->m_repeat[j]->count;
      int left = m_col_array[0]->width;
      int top  = GetListTop() + kFontSize * (i - m_head);
      
      s8 cnt_str[256];
      if (count > 999) {
        strcpy(cnt_str, "*");
      } else {
        _itoa(count, cnt_str, 10);
      }

      if (g_dbg->jumplog(i)->m_repeat[j]->len == 1) {
        MoveToEx(hdc, left, top + kFontSize / 2, NULL);
        LineTo(hdc,   left + 4, top + kFontSize / 2);

        TextOut(hdc, left + 5, top, cnt_str, strlen(cnt_str));
      } else {
        MoveToEx(hdc, left, top + 2, NULL);
        LineTo(hdc,   left + level * kNestIndent, top + 2);

        MoveToEx(hdc, left, top - 2 + kFontSize * (1 + range), NULL);
        LineTo(hdc,   left + level * kNestIndent, top - 2 + kFontSize * (1 + range));

        MoveToEx(hdc, left + level * kNestIndent, top + 3, NULL);
        LineTo(hdc,   left + level * kNestIndent, top - 2 + kFontSize * (1 + range));

        TextOut(hdc, left + 1 + level * kNestIndent, top + range * kFontSize / 2, cnt_str, strlen(cnt_str));
      }
    }
  }
  DeleteObject(hpPen);

  DeleteObject(hbSelect);
  DeleteObject(hbFixedBG);
  DeleteObject(hbBG);

  m_dlg->update(0, GetListHeaderTop(), clientrect.right, clientrect.bottom);
}