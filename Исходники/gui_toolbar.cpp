void Toolbar::onSysColorChange()
{
	// the following line is used to hack the toolbar background color for tradeshow
	return;
	int iconSize;
	ImageList_GetIconSize( disabledImageList_, &iconSize, &iconSize );
	disabledImageList_ = ImageList_Create( iconSize, iconSize, ILC_COLOR32, 1, 256 );
	hotImageList_ = ImageList_Create( iconSize, iconSize, ILC_COLOR32, 1, 256 );
	normalImageList_ = ImageList_Create( iconSize, iconSize, ILC_COLOR32, 1, 256 );

	// destroy it
	while( sendMessage( TB_BUTTONCOUNT, 0, 0 ) )
		sendMessage( TB_DELETEBUTTON , 0, 0 );

	HIMAGELIST imglist;
	imglist = (HIMAGELIST)sendMessage( TB_SETIMAGELIST, 0, (LPARAM)normalImageList_ );
	if( imglist )
		ImageList_Destroy( imglist );
	imglist = (HIMAGELIST)sendMessage( TB_SETHOTIMAGELIST, 0, (LPARAM)hotImageList_ );
	if( imglist )
		ImageList_Destroy( imglist );
	imglist = (HIMAGELIST)sendMessage( TB_SETDISABLEDIMAGELIST, 0, (LPARAM)disabledImageList_ );
	if( imglist )
		ImageList_Destroy( imglist );

	imageIndices_.clear();
	Manager::instance().bitmaps().clear();

	unsigned int index = 0;
	changed( index, rootItem() );
}