void CLegend::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
 SIZE sz;

 if(lpDrawItemStruct->itemData == (DWORD)-1)
    return;

 LegendInfo * li = (LegendInfo *)lpDrawItemStruct->itemData;

 CRect r = lpDrawItemStruct->rcItem;
 CDC * dc = CDC::FromHandle(lpDrawItemStruct->hDC);
 dc->SelectObject(li->pen);
 dc->SelectObject(li->brush);

 sz = dc->GetTextExtent(_T(" "), 1);

 CString s;
 s.LoadString(li->id);

 r.right = r.left + ::GetSystemMetrics(SM_CXVSCROLL);  // random useful value
 dc->Rectangle(&r);

 r.left = r.right + 2 * sz.cx;
 r.right = lpDrawItemStruct->rcItem.right;
 dc->DrawText(s, &r, DT_LEFT);
}