void TABLE::CreateEditControl()

  {
  if(hEdit || TABLE_ATTRIBUTES::AutoFill() || !TABLE_ATTRIBUTES::CanActivate())
    return;

  long  activeRow = TABLE_ATTRIBUTES::ActiveRow();
  if(activeRow<0)
    return;

  if((activeRow<firstRow) || (activeRow>(firstRow+numVisRows-1)))
    return;

  int   activeCol = TABLE_ATTRIBUTES::ActiveColumn();
  if(!COLUMN::CanEdit(activeCol))
    return;

  RUNTIMEINFO*  rtime = (RUNTIMEINFO*)AObjGetRuntimeInfo(theObject);
  ROW*          row = rtime->GetRow();
  if(!row->IsSelected(activeRow))
    return;

  int width = COLUMN::ColumnWidth(activeCol);
  if(width==0)
    return;

  int height = TABLE_ATTRIBUTES::CellHeight();
  if(TABLE_ATTRIBUTES::RowLines())
    height++;
  int cellY = tblRect.top + ((int)(activeRow - firstRow))*height;
  if(TABLE_ATTRIBUTES::ShowTitles())
    {
    cellY += (TABLE_ATTRIBUTES::TitleHeight()+1);
    if(TABLE_ATTRIBUTES::RowLines())
      cellY++;
    }

  if(TABLE_ATTRIBUTES::RowLines())
    height--;

  int cellX = tblRect.left;
  for(int i=0; i<activeCol; i++)
    {
    if((i>=TABLE_ATTRIBUTES::NumFixedColumns()) && (i<firstColumn))
      continue;

    if(COLUMN::ColumnWidth(i)==0)
      {
      if((i==(TABLE_ATTRIBUTES::NumFixedColumns()-1))
          &&
        (cellX!=tblRect.left))
        cellX++;
      continue;
      }

    cellX += COLUMN::ColumnWidth(i);
    if(TABLE_ATTRIBUTES::ColumnLines())
      cellX++;
    if(i==(TABLE_ATTRIBUTES::NumFixedColumns()-1))
      cellX++;
    }

  HDC       hDC = GetDC(hTable);
  HPEN      hPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
  LOGBRUSH  lb = {BS_SOLID, GetSysColor(COLOR_WINDOW), 0};
  HPEN      oldPen = (HPEN)SelectObject(hDC, hPen);
  HBRUSH    hBrush = CreateBrushIndirect(&lb);
  HBRUSH    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
  int       right = cellX+width;
  if(right>tblRect.right)
    right = tblRect.right;

  Rectangle(hDC, cellX, cellY, right, cellY+height);
  SelectObject(hDC, oldPen);
  DeleteObject(hPen);
  SelectObject(hDC, oldBrush);
  DeleteObject(hBrush);
  ReleaseDC(hParentWnd, hDC);

  cellX += COLUMN::CellCharWidth(activeCol);
  width -= 2*COLUMN::CellCharWidth(activeCol);
  if((cellX+width)>tblRect.right)
    width = tblRect.right - cellX;

  int offset = 2*TABLE_ATTRIBUTES::CellLeading()/3 + TABLE_ATTRIBUTES::CellAscent() - COLUMN::CellAscent(activeCol);
  cellY = cellY + offset;
  height = TABLE_ATTRIBUTES::CellHeight() - offset;

  editRow = activeRow;
  editCol = activeCol;

  char huge*  cellPtr = row->GetCell(activeRow, activeCol, FALSE, NULL);
  UINT  length = (UINT)hstrlen(cellPtr) + 1;
  char* cellStr = new char[length];
  hmemcpy(cellStr, cellPtr, length);
  hEdit = CreateWindow("EDIT", cellStr,
            WS_CHILD | ES_AUTOHSCROLL,
            cellX, cellY,
            width, height,
            hTable, (HMENU)3, G.hInstance, NULL);
  delete cellStr;

  // subclass the edit control
  SetProp(hEdit, "loPtr", (HANDLE)LOWORD((DWORD)this));
  SetProp(hEdit, "hiPtr", (HANDLE)HIWORD((DWORD)this));
  SetProp(hEdit, "number", (HANDLE)AObjCheckType(COLUMN::GetObjectID(activeCol), OTYPE_NUMBER));
  oldEditControlProc = (WNDPROC)GetWindowLong(hEdit, GWL_WNDPROC);
  SetWindowLong(hEdit, GWL_WNDPROC, (long)EditControlProc);
  ShowWindow(hEdit, SW_SHOW);

  hEditFont =CreateFontIndirect(COLUMN::CellLogFont(activeCol));
  SendMessage(hEdit, WM_SETFONT, (WPARAM)hEditFont, MAKELPARAM(TRUE, 0));
  SetFocus(hEdit);
  SendMessage(hEdit, EM_SETSEL, (WPARAM)FALSE, MAKELPARAM(0, -1));

  // wipPreventThieves(ParentID, TRUE); SKJ --> need replacement
  AEvtPostSignalAtMark(theObject, SIGNAL_STARTEDITING);
  }