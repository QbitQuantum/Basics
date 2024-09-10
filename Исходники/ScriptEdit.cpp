void CScriptEdit::OnContextMenu(CWnd* pWnd, CPoint point) 
{
  if(pWnd->GetDlgCtrlID()==IDC_TEXT)
  {
    CMenu *menu;
    CMenu *popupmenu;
    
    menu=GetMenu();    
    popupmenu=menu->GetSubMenu(EDITMENU); //this should be better defined
    popupmenu->TrackPopupMenu(TPM_CENTERALIGN,point.x,point.y,this);   
  }
}