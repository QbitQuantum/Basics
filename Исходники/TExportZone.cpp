void TExportZone::Draw(BRect updateRect)
{
	BPoint startPt, endPt;

	const BRect bounds = Bounds();
	
	// Save environment
	PushState();
			
	//
	//	Draw zone and Start and End indicators
	//
	
	// Draw export zone
	SetHighColor(kTaupe);
	FillRect(updateRect);
	
	//	Draw top highlight
	SetHighColor(kLightTaupe);
	startPt.Set(updateRect.left, bounds.top);
	endPt.Set(updateRect.right, bounds.top);
	StrokeLine(startPt, endPt);		
	
	//	Draw top shadow
	SetHighColor(kDarkTaupe);
	startPt.Set(updateRect.left, bounds.top-1);
	endPt.Set(updateRect.right, bounds.top-1);
	StrokeLine(startPt, endPt);		
	
	//	Draw bottom highlight
	SetHighColor(kLightTaupe);
	startPt.Set(updateRect.left, bounds.bottom-1);
	endPt.Set(updateRect.right, bounds.bottom-1);
	StrokeLine(startPt, endPt);		

	//	Draw bottom border line
	SetHighColor(kBlack);
	startPt.Set(updateRect.left, bounds.bottom);
	endPt.Set(updateRect.right, bounds.bottom);
	StrokeLine(startPt, endPt);		

	//	Crop 1 pixel from bottom of channel height
	BRect channelRect = m_ExportChannel;
	channelRect.bottom--;

	// Draw export channel
	if (updateRect.Intersects(channelRect) )
	{		
		BRect fillRect = updateRect & channelRect;
		
		//	Fill
		SetHighColor(kKhaki);
		FillRect(fillRect);
		
		//	Highlight
		BPoint startPt, endPt;
		SetHighColor(kLightKhaki);
		startPt.Set(fillRect.left, m_ExportChannel.top);
		endPt.Set(fillRect.right, m_ExportChannel.top);
		StrokeLine(startPt, endPt);
		
		//	Shadow
		SetHighColor(kDarkKhaki);
		startPt.Set(fillRect.left, m_ExportChannel.bottom);
		endPt.Set(fillRect.right, m_ExportChannel.bottom);
		StrokeLine(startPt, endPt);
	}
				
	// Draw ExportStart and ExportEnd markers
	DrawInMarker(updateRect);
	DrawOutMarker(updateRect);
	
	// Restore environment
	PopState();	
}