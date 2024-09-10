void ListFileProvider::getThumbnail( ThumbnailManager& manager,
									int index, CImage& img, int w, int h,
									ThumbnailUpdater* updater )
{
	if ( index < 0 || getNumItems() <= index )
		return;

	mutex_.grab();
	std::string item;
	if ( isFiltering() )
		item = searchResults_[ index ]->fileName;
	else
		item = items_[ index ]->fileName;
	mutex_.give();

	// find thumbnail

	HICON extIcon = getExtensionIcons( item );
	if ( extIcon )
	{
		CBrush back;
		back.CreateSolidBrush( GetSysColor( COLOR_WINDOW ) );
		img.Create( w, h, 32 );
		CDC* pDC = CDC::FromHandle( img.GetDC() );
		DrawIconEx( pDC->m_hDC, 0, 0, extIcon, w, h, 0, (HBRUSH)back, DI_NORMAL );
		img.ReleaseDC();
	}

	manager.create( item, img, w, h, updater );
}