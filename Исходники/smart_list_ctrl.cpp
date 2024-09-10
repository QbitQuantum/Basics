void SmartListCtrl::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	if ( !eventHandler_ )
		return;

	LPNMLISTVIEW info = (LPNMLISTVIEW)pNMHDR;
	std::string text;
	int image;
	getData( info->iItem, text, image );

	POINT pt;
	GetCursorPos( &pt );
	if ( dragImgList_ )
	{
		delete dragImgList_;
		dragImgList_ = 0;
	}

	int pos = GetNextItem( -1, LVNI_SELECTED );
	bool isFirst = true;
	int xoff = 0;
	int yoff = 0;
	int xstep = 0;
	int ystep = 0;
	IMAGEINFO imf;
	int maxDragWidth = 400;
	int maxDragHeight = 350;
	while ( pos != -1 ) {
		if ( isFirst ) {
			dragImgList_ = CreateDragImage( pos, &pt );
			dragImgList_->GetImageInfo( 0, &imf );
			xstep = imf.rcImage.right - imf.rcImage.left;
			ystep = imf.rcImage.bottom - imf.rcImage.top;
			yoff = imf.rcImage.bottom;
			isFirst = false;
		}
		else
		{
			if ( yoff + ystep > maxDragHeight && xoff + xstep > maxDragWidth )
				generateDragListEndItem_ = true; // reached the max, so generate a 'more...' item in GetData
			CImageList* oneImgList = CreateDragImage( pos, &pt );
			generateDragListEndItem_ = false;
			CImageList* tempImgList = new CImageList();
			tempImgList->Attach(
				ImageList_Merge( 
					dragImgList_->GetSafeHandle(),
					0, oneImgList->GetSafeHandle(), 0, xoff, yoff ) );
			delete dragImgList_;
			delete oneImgList;
			dragImgList_ = tempImgList;
			dragImgList_->GetImageInfo( 0, &imf );
			yoff += ystep;
			if ( yoff > maxDragHeight )
			{
				xoff += xstep;
				if ( xoff > maxDragWidth )
					break;
				yoff = 0;
			}
		}
		pos = GetNextItem( pos, LVNI_SELECTED );
	}

	if ( dragImgList_ ) 
	{
		CPoint offset( thumbWidthCur_ + 16 , max( 16, thumbHeightCur_ - 14 ) );
		dragImgList_->SetBkColor( GetBkColor() );
		dragImgList_->SetDragCursorImage( 0, offset );
		dragImgList_->BeginDrag( 0, offset );
		dragImgList_->DragEnter( 0, pt );
	}

	if ( delayedSelectionPending_ )
	{
		// if a selection timer is pending, force it
		delayedSelectionNotify();
	}

	dragging_ = true;
	eventHandler_->listStartDrag( info->iItem );

}