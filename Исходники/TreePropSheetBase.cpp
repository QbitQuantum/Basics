void CTreePropSheetBase::RefillPageTree()
{
	if (!IsWindow(m_hWnd))
		return;

  // TreePropSheetEx: OnPageTreeSelChanging does not process message.
  TreePropSheet::CIncrementScope RefillingPageTreeContentGuard( m_nRefillingPageTreeContent );
  // TreePropSheetEx: End OnPageTreeSelChanging does not process message.

	m_pwndPageTree->DeleteAllItems();

	CTabCtrl	*pTabCtrl = GetTabControl();
	if (!IsWindow(pTabCtrl->GetSafeHwnd()))
	{
		ASSERT(FALSE);
		return;
	}

	const int	nPageCount = pTabCtrl->GetItemCount();

	// rebuild image list
	if (m_bTreeImages)
	{
		for (int i = m_Images.GetImageCount()-1; i >= 0; --i)
			m_Images.Remove(i);

		// add page images
		CImageList	*pPageImages = pTabCtrl->GetImageList();
		if (pPageImages)
		{
			for (int nImage = 0; nImage < pPageImages->GetImageCount(); ++nImage)
			{
				HICON	hIcon = pPageImages->ExtractIcon(nImage);
				m_Images.Add(hIcon);
				DestroyIcon(hIcon);
			}
		}

		// add default images
		if (m_DefaultImages.GetSafeHandle())
		{	
			HICON	hIcon;

			// add default images
			hIcon = m_DefaultImages.ExtractIcon(0);
			if (hIcon)
			{
				m_Images.Add(hIcon);
				DestroyIcon(hIcon);
			}
			hIcon = m_DefaultImages.ExtractIcon(1);
			{
				m_Images.Add(hIcon);
				DestroyIcon(hIcon);
			}
		}
	}

	// insert tree items
	for (int nPage = 0; nPage < nPageCount; ++nPage)
	{
		// Get title and image of the page
		CString	strPagePath;

		TCITEM	ti;
		ZeroMemory(&ti, sizeof(ti));
		ti.mask = TCIF_TEXT|TCIF_IMAGE;
		ti.cchTextMax = MAX_PATH;
		ti.pszText = strPagePath.GetBuffer(ti.cchTextMax);
		ASSERT(ti.pszText);
		if (!ti.pszText)
			return;

		pTabCtrl->GetItem(nPage, &ti);
		strPagePath.ReleaseBuffer();

		// Create an item in the tree for the page
		HTREEITEM	hItem = CreatePageTreeItem(ti.pszText);
		ASSERT(hItem);
		if (hItem)
		{
			m_pwndPageTree->SetItemData(hItem, nPage);

			// set image
			if (m_bTreeImages)
			{
				int	nImage = ti.iImage;
				if (nImage < 0 || nImage >= m_Images.GetImageCount())
					nImage = m_DefaultImages.GetSafeHandle()? m_Images.GetImageCount()-1 : -1;

				m_pwndPageTree->SetItemImage(hItem, nImage, nImage);
			}

      // Set font if disabled.
      CPropertyPage* pPage = GetPage( nPage );
      ASSERT( pPage );
      if( NULL != pPage && !IsPageEnabled( pPage ) )
      {
        ::SendMessage( m_pwndPageTree->GetSafeHwnd(), WMU_ENABLETREEITEM, (WPARAM)hItem, (LPARAM)GetSysColor(COLOR_GRAYTEXT) );
      }
		}
	}
}