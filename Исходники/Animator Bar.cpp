void AnimatorBar::UpdateFilmStrip()
{
	film_strip.SetRedraw(false);
	m_ImageList.DeleteImageList();
	film_strip.DeleteAllItems();

	if(!m_pCurrentAnimation)
		return;
	
	m_ImageList.Create(32, 32, ILC_COLOR24, 3, 3);
	film_strip.SetImageList(&m_ImageList, LVSIL_NORMAL);
	
	for (int i = 0; i < m_pCurrentAnimation->m_Images.size(); i++)
	{
		// Create thumbnail & add to filmstrip
		CImageResource* pImage = application->resources.FindImageResourceFromNumber(m_pCurrentAnimation->m_Images[i]);

		if(pImage)
		{
			HBITMAP Bitmap = pImage->GetHBitmap(true,false);
			ImageList_Add(m_ImageList.m_hImageList, Bitmap, Bitmap);


			CString Name;
			Name.Format("%d", i + 1);
			film_strip.InsertItem(i, Name, i);
		}
	}

	film_strip.SetRedraw(true);
	film_strip.Invalidate();
}