//---------------------------------------------------------------------------
void TColCombo::DrawItem(DRAWITEMSTRUCT *di)
{
	if (VHandle==NULL)return;

  HANDLE br;
  int oldtextcol=GetTextColor(di->hDC),oldmode=GetBkMode(di->hDC);

  if (di->itemState & ODS_SELECTED){
    br=CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
    SetTextColor(di->hDC,GetSysColor(COLOR_HIGHLIGHTTEXT));
  }else{
    br=CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    SetTextColor(di->hDC,GetSysColor(COLOR_WINDOWTEXT));
  }

  SetBkMode(di->hDC,TRANSPARENT);
  FillRect(di->hDC,&(di->rcItem),br);
  DeleteObject(br);
  if ((di->itemID)<(UINT)NumItems){
    br=CreateSolidBrush(VItem[di->itemID]->Col);
    HANDLE pen=CreatePen(PS_SOLID,1,0);
    HANDLE oldpen=SelectObject(di->hDC,pen),oldbr=SelectObject(di->hDC,br);

    Rectangle(di->hDC,
              di->rcItem.left+BoxSurround,di->rcItem.top+BoxSurround,
              di->rcItem.left+(BoxWidth-BoxSurround),di->rcItem.bottom-BoxSurround);

    SelectObject(di->hDC,oldpen);SelectObject(di->hDC,oldbr);
    DeleteObject(pen);DeleteObject(br);

    RECT shiftrect=di->rcItem;shiftrect.left+=BoxWidth+BoxGap;
    DrawText(di->hDC,VItem[di->itemID]->Text,strlen(VItem[di->itemID]->Text),
              &shiftrect,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
  }
  SetTextColor(di->hDC,oldtextcol);
  SetBkMode(di->hDC,oldmode);
  if (di->itemState & ODS_FOCUS)
    DrawFocusRect(di->hDC,&(di->rcItem));
}