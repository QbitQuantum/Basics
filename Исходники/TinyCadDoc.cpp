// Save as a PNG file
void CTinyCadDoc::SavePNG( const TCHAR *file_name, CDC &ref_dc, int scaling, bool bw, bool rotate )
{
	// Calculate the boundries
	CDRect rect = CDRect(0,0,0,0);

	if (IsSelected())
	{
		BOOL first = TRUE;

		selectIterator it = GetSelectBegin();
		while ( it != GetSelectEnd() ) 
		{
			CDrawingObject *pointer=*it;

			if (first) 
			{
				rect.top = pointer->m_point_a.y;
				rect.bottom = pointer->m_point_a.y;
				rect.left = pointer->m_point_a.x;
				rect.right = pointer->m_point_a.x;
				first = FALSE;
			}

			rect.top 	 = min(rect.top,min(pointer->m_point_a.y,pointer->m_point_b.y));
			rect.bottom = max(rect.bottom,max(pointer->m_point_a.y,pointer->m_point_b.y));
			rect.left 	 = min(rect.left,min(pointer->m_point_a.x,pointer->m_point_b.x));
			rect.right  = max(rect.right,max(pointer->m_point_a.x,pointer->m_point_b.x));

			++ it;
		}
	}
	else
	{
		rect = CDRect( 0,0, GetDetails().m_szPage.cx, GetDetails().m_szPage.cy );
	}

	rect.InflateRect( 0,0, 10,10 );


	// Transform the origin so the design lies at 0,0
	Transform newTransform;
	newTransform.SetOrigin( CDPoint( rect.left, rect.top ) );

	// Set the scaling
	newTransform.SetZoomFactor( static_cast<double>(scaling) / 100.0 );
	rect.right = (rect.right * scaling) / 100;
	rect.bottom = (rect.bottom * scaling) / 100;

	CImagePNG png;
	
	CBitmap *bitmap = png.CreateImageBitmap( static_cast<int>(rect.Width()), static_cast<int>(rect.Height()), ref_dc, 32 );


	CDC bitmap_dc;
	bitmap_dc.CreateCompatibleDC( &ref_dc );
	CBitmap *old_bitmap = bitmap_dc.SelectObject( bitmap );

	bitmap_dc.SelectStockObject( WHITE_BRUSH );
	bitmap_dc.SelectStockObject( WHITE_PEN );
	bitmap_dc.Rectangle( 0,0,static_cast<int>(rect.Width()), static_cast<int>(rect.Height()) );

	// Create the DC and render...
	{
		CContext dc(&bitmap_dc,newTransform);
		if (bw)
		{
			dc.SetBlack( TRUE );
		}

		if (IsSelected())
		{
			// Draw just the selected part
			CJunctionUtils j( this );			
			for( selectIterator i = GetSelectBegin(); i != GetSelectEnd(); i++ ) 
			{
				j.AddObjectToTodo( *i );
				(*i)->Paint(dc,draw_normal);
			}
			j.PaintJunctions(dc,draw_normal);
		}
		else
		{
			// Draw the whole design into the metafile
			drawingIterator it = GetDrawingBegin();
			while (it != GetDrawingEnd()) 
			{
				(*it)->Paint(dc,draw_normal);
				++ it;
			}

			// Show the design 
			Display( dc );
		}

	}

	bitmap_dc.SelectObject( old_bitmap );

	// Do we rotate?
	if (rotate)
	{
		png.Rotate( ref_dc );
	}

	// ... and save to a png
	png.Save( ref_dc, file_name );
}