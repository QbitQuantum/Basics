void CPatchPaletteButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
  CDC *pDC = GetDC();
  CMainFrame* pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
  
  CModelerView *pModelerView = CModelerView::GetActiveMappingNormalView();
  if( pModelerView == NULL)
  {
    pDC->FillSolidRect( &lpDrawItemStruct->rcItem, 0x00aaaaaa);
    pDC->DrawEdge( &lpDrawItemStruct->rcItem, EDGE_RAISED, BF_RECT);
  }
  else
  {
    INDEX iButtonNo = lpDrawItemStruct->CtlID - IDC_PATCH_BUTTON_BASE;
    ULONG ulCurrentMask = pModelerView->m_ModelObject.GetPatchesMask();
    CModelerDoc* pDoc = pModelerView->GetDocument();
    ULONG ulExistingMask = pDoc->m_emEditModel.GetExistingPatchesMask();
    pDC->FillSolidRect( &lpDrawItemStruct->rcItem, 0x00aaaaaa);
    // If this patch doesn't exist
    if( (ulExistingMask & (1UL << iButtonNo)) == 0)
    {
      pDC->DrawEdge( &lpDrawItemStruct->rcItem, EDGE_RAISED, BF_RECT);
    }
    // If this patch exists but it is not turned on
    else if( (ulCurrentMask & (1UL << iButtonNo)) == 0)
    {
      // If this is active patch
      if( iButtonNo == pModelerView->m_iActivePatchBitIndex)
        pDC->DrawIcon( 2, 2, pMainFrame->m_dlgPatchesPalette->m_PatchActiveIcon);
      else
        pDC->DrawIcon( 2, 2, pMainFrame->m_dlgPatchesPalette->m_PatchExistIcon);
      pDC->DrawEdge( &lpDrawItemStruct->rcItem, EDGE_RAISED, BF_RECT);
    }
    // If this patch is turned on and it is active patch
    else if( iButtonNo == pModelerView->m_iActivePatchBitIndex)
    {
      pDC->DrawIcon( 2, 2, pMainFrame->m_dlgPatchesPalette->m_PatchActiveIcon);
      pDC->DrawEdge( &lpDrawItemStruct->rcItem, EDGE_SUNKEN, BF_RECT);
    }
    // If this patch is turned on and it is not active patch
    else
    {
      pDC->DrawIcon( 2 ,2, pMainFrame->m_dlgPatchesPalette->m_PatchInactiveIcon);
      pDC->DrawEdge( &lpDrawItemStruct->rcItem, EDGE_SUNKEN, BF_RECT);
    }
  }
  ReleaseDC( pDC);
}          