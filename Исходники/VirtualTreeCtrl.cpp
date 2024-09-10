void CVirtualTreeCtrl::OnDropFiles(HDROP hDropInfo) 
{
	CMainFrame* pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
  INDEX ctFiles = DragQueryFile( hDropInfo, 0xFFFFFFFF, NULL, 0);

  // get dropped coordinates
  CPoint point;
  DragQueryPoint( hDropInfo, &point);
  
  CVirtualTreeNode *pVTNDst = ItemForCoordinate(point);
  if( pVTNDst!=NULL)
  {
    for( INDEX i=0; i<ctFiles; i++)
    {
	    char chrFile[ 256];
      DragQueryFile( hDropInfo, i, chrFile, 256);
      CTString strAddr = CTString(chrFile);
      if( strAddr != "")
      {
        CVirtualTreeNode *pVTNSrc;
        strAddr.ScanF("VTN%d", &pVTNSrc);
        if(pVTNSrc==pVTNDst) return;
        pVTNSrc->MoveToDirectory( pVTNDst);
        // delete all items
        DeleteAllItems();
        m_pBrowser->AddDirectoryRecursiv( &m_pBrowser->m_VirtualTree, TVI_ROOT);   // Fill CTreeCtrl using recursion
        SortChildren( NULL);
        SelectItem( (HTREEITEM) pVTNSrc->vtn_Handle);
        m_pBrowser->m_bVirtualTreeChanged = TRUE;
        m_pBrowser->OpenSelectedDirectory();
      }
    }
  }

	CTreeCtrl::OnDropFiles(hDropInfo);
}