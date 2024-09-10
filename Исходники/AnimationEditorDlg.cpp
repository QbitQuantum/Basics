void CAnimationEditorDlg::UpdateList()
{
	m_Frames.SetRedraw(false);
	m_ImageList.DeleteImageList();
	m_Frames.DeleteAllItems();

	if(!m_CurrentAnimation)
		return;
	
	m_ImageList.Create(32, 32, ILC_COLOR24, 3, 3);
	m_Frames.SetImageList(&m_ImageList, LVSIL_NORMAL);
	
	for (int i = 0; i < m_CurrentAnimation->m_Images.size(); i++)
	{
		// Create thumbnail & add to filmstrip
		CImageResource* image = m_pApplication->FindImageResourceFromNumber(m_CurrentAnimation->m_Images[i]);

		if(image)
		{
				
				HBITMAP Bitmap = image->GetHBitmap(true,false);
				ImageList_Add(m_ImageList.m_hImageList, Bitmap, Bitmap);

				CString name;
				name.Format("%d", i+1);
				m_Frames.InsertItem(i, name, i);
		}
	}

	m_Frames.SetRedraw(true);
	m_Frames.Invalidate();
}