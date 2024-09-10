BSTR CMUSHclientDoc::Menu(LPCTSTR Items, LPCTSTR Default) 
{
	CString strResult;
  CSendView* pmyView = NULL;


  for(POSITION pos=GetFirstViewPosition();pos!=NULL;)
    {
    CView* pView = GetNextView(pos);

    if (pView->IsKindOf(RUNTIME_CLASS(CSendView)))
      {
      pmyView = (CSendView*)pView;
      break;

      }	  // end of being a CSendView
    }

  if (!pmyView)
    return strResult.AllocSysString();

  CEdit * ctlEdit = & pmyView->GetEditCtrl();

  int nStartChar,
      nEndChar;

  // find the selection range
  ctlEdit->GetSel(nStartChar, nEndChar);

  if (nEndChar < 0)
    nEndChar = nStartChar;

  vector<string> v;

  StringToVector (Items, v, "|");

  int iCount = v.size ();

  // must have at least one item
  if (iCount < 1)
    return strResult.AllocSysString();

  CCompleteWordDlg dlg;
  
  set<string> extraItems;

  for (vector<string>::const_iterator i = v.begin (); i != v.end (); i++)
    extraItems.insert (*i);

  dlg.m_extraItems = &extraItems;
  dlg.m_strDefault = Default;
  dlg.m_bFunctions = false;
  dlg.m_pt = ctlEdit->PosFromChar (nEndChar - 1);  // strangely doesn't work at end of line

  ctlEdit->ClientToScreen(&dlg.m_pt);

  if (dlg.DoModal () == IDOK)
     strResult = dlg.m_strResult;

	return strResult.AllocSysString();
}   // end of CMUSHclientDoc::Menu