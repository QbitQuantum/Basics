void CTreeListColumnDragWnd::DrawGrid( CDC* pDC, CRect rcItem )
{
  // draw all grids
  CTreeListColumnInfo* pColumnInfo;
  int nColPos = 0;
  for( int iShow = 0; iShow < m_pTreeListCtrl->m_arShows.GetSize(); iShow++, nColPos += pColumnInfo->m_nWidth )
  {
    int iCol;

    // do NOT draw zero column;
    iCol = m_pTreeListCtrl->m_arShows[ iShow ];
    pColumnInfo = (CTreeListColumnInfo*)m_pTreeListCtrl->m_arColumns[iCol];
    if( pColumnInfo->m_nWidth == 0 )
      continue;

    CRect rcColumn;
    rcColumn.SetRect( 0, 0, pColumnInfo->m_nWidth, rcItem.Height() );
    rcColumn.OffsetRect( nColPos, 0 );
    rcColumn.OffsetRect( rcItem.left, rcItem.top );

    if( iCol == 0 )
    {
      // draw vertical grid line of tree
      if( m_pTreeListCtrl->m_dwStyle&TLC_HGRID_EXT && m_pTreeListCtrl->m_dwStyle&TLC_TGRID )
      {
        pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
        pDC->LineTo( rcColumn.right-1, rcColumn.bottom - 1);
      }

      if( m_pTreeListCtrl->m_dwStyle&TLC_VGRID_EXT )
      {
        pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
        pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
      }
    }
    else
    {
      // draw vertical grid line and horizonal grid lin
      if( m_pTreeListCtrl->m_dwStyle&TLC_HGRID_EXT )
      {
        pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
        pDC->LineTo( rcColumn.right, rcColumn.bottom - 1);
      }

      if( m_pTreeListCtrl->m_dwStyle&TLC_VGRID_EXT )
      {
        pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
        pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
      }
    }
  }
}