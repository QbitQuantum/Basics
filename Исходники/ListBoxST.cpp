// Sets the image list to use in the list box.
//
// Parameters:
//		[IN]	pImageList
//				Pointer to an CImageList object containing the image list
//				to use in the list box. Pass NULL to remove any previous
//				associated image list.
//
void CListBoxST::SetImageList(CImageList* pImageList)
{
	m_pImageList = pImageList;
	// Get icons size
	if (m_pImageList)
		ImageList_GetIconSize(*m_pImageList, (LPINT)&m_szImage.cx, (LPINT)&m_szImage.cy);
	else
		::ZeroMemory(&m_szImage, sizeof(m_szImage));

	Invalidate();
} // End of SetImageList