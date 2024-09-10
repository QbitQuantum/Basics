void InsertObjectDialog::LoadObjects()
{
	// Create imagelists
	m_LargeImages.Create(32, 32, ILC_COLOR24, 0, 10);
	small_images.Create(16, 16, ILC_COLOR24, 0, 10);

	map<int, CPlugin>::iterator i = g_Plugins.begin();

	for ( ; i != g_Plugins.end(); i++) 
	{
		CString lowerName = i->second.m_Name;
		lowerName.MakeLower();

		if (!i->second.m_bMovement && lowerName != "tag")
		{
			bool bGame = false;
			if (application.runtime != CApplication::rt_application) bGame = true;

			if (!bGame && i->second.m_Category == OT_GAME)
				continue;

			// Extract the icon
			ImageList_Add(m_LargeImages, i->second.m_LargeIcon, NULL);
			ImageList_Add(small_images, i->second.m_SmallIcon, NULL);
		}
	}
}