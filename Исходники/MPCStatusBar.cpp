void MPCStatusBar::RemovePane(int nPaneID)
{
 SetRedraw(FALSE);
 CWnd * pwnd = NULL;
  int i;
 for( i = 0; i < m_aPans.GetSize(); i++ )
 {
  if( m_aPans[i]->m_nPaneID == nPaneID )
  {
   if( m_aPans[i]->m_bAutodelete )
    pwnd = m_aPans[i]->m_hWnd;
   delete m_aPans[i];
   m_aPans.RemoveAt(i);
   break;
  }
 }
 if( pwnd )
 {
  pwnd->DestroyWindow();
  delete pwnd;
 }

 CArray<MPCStatusBarPane,MPCStatusBarPane> arPanes;
 MPCStatusBarPane statusPane;
 i = 0;
 while( GetStatusPane(i,statusPane) )
 {
  if( statusPane.nID != (UINT)nPaneID )
   arPanes.Add( statusPane );
  i++;
 }
 // Now remove the indicator
 UINT * pIndicators = new UINT[arPanes.GetSize()];
 for(i=0;i<arPanes.GetSize();i++)
  pIndicators[i]=arPanes[i].nID;
 SetIndicators(pIndicators,arPanes.GetSize());

 // Replace infos of indicators ..
 for(i = 0; i < arPanes.GetSize(); i++ )
 {
  SetPaneInfo(i,arPanes[i].nID,arPanes[i].nStyle,arPanes[i].cxText);
  SetPaneText(i,arPanes[i].strText);
 }
 delete pIndicators;
 SetRedraw(TRUE);
 PositionControls();
 Invalidate(TRUE);

}