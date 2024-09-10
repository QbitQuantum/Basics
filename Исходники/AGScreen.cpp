void AGScreen::Paint (CG16bitImage &Dest)

//	Paint
//
//	Paint the whole screen.
//
//	Dest is the entire display area; its origin is 0,0.

	{
	if (!IsRectEmpty(&m_rcInvalid))
		{
		int i;

		//	Convert to Window coordinates

		RECT rcUpdate = m_rcInvalid;
		OffsetRect(&rcUpdate, m_rcRect.left, m_rcRect.top);

		//	Clip appropriately. Note that Dest is always in
		//	window coordinates.

		Dest.SetClipRect(rcUpdate);

		//	Blank the screen

		Dest.Fill(rcUpdate.left, rcUpdate.top, RectWidth(rcUpdate), RectHeight(rcUpdate), CG16bitImage::RGBValue(0,0,0));

		//	Let each area paint

		for (i = 0; i < GetAreaCount(); i++)
			{
			AGArea *pArea = GetArea(i);

			//	m_rcInvalid is in Screen coordinates, and so is the rect
			//	for each area. The intersection is the portion of the
			//	area's rect that is invalid.

			RECT rcIntersect;
			if (pArea->IsVisible()
					&& ::IntersectRect(&rcIntersect, &m_rcInvalid, &pArea->GetRect()))
				{
				//	Calculate the rect of the area relative to the Window

				RECT rcArea = pArea->GetRect();
				OffsetRect(&rcArea, m_rcRect.left, m_rcRect.top);

				//	Clip appropriately

				OffsetRect(&rcIntersect, m_rcRect.left, m_rcRect.top);
				Dest.SetClipRect(rcIntersect);

				//	Paint

				pArea->Paint(Dest, rcArea);
				}
			}

		//	Reset the invalid rect

		memset(&m_rcInvalid, 0, sizeof(m_rcInvalid));
		Dest.ResetClipRect();
		}
	}