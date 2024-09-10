// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CLTWnd::DrawToSurface
//
//	PURPOSE:	Does the dirty work for drawing a single window to a surface
//
// ----------------------------------------------------------------------- //
BOOL CLTWnd::DrawToSurface(HSURFACE hSurfDest)
{
	// We don't draw the main window (the only one without a parent)
	if (m_pParentWnd)
	{
		CRect	rcSurf;
		GetSurfaceRect(&rcSurf);

		CRect	rcClip;
		GetClipRect(&rcClip);

		CRect	rcSource;

		// check for intersection of the clip area and the surface
		if (rcSource.IntersectRect(rcSurf, rcClip))
		{
			// retain the absolute coordinates of the intersection relative to the main drawing window
			CPoint	ptIntersect = rcSource.TopLeft();

			// normalize coordinates relative to child surface
			rcSource -= rcSurf.TopLeft();

			// create a lithtech-compatible rect
            LTRect   drcSource;

			drcSource.left = rcSource.left;
			drcSource.top = rcSource.top;
			drcSource.right = rcSource.right;
			drcSource.bottom = rcSource.bottom;

			// draw the surface
			if (m_hSurf)
			{
				if (IsFlagSet(LTWF_TRANSPARENT))
				{
                    if(g_pLTClient->DrawSurfaceToSurfaceTransparent(hSurfDest,m_hSurf, &drcSource, ptIntersect.x, ptIntersect.y, m_hColorTransparent) != LT_OK)
						return FALSE;
				}
				else
				{
                    if(g_pLTClient->DrawSurfaceToSurface(hSurfDest, m_hSurf, &drcSource, ptIntersect.x, ptIntersect.y) != LT_OK)
						return FALSE;
				}
			}
		}
	}
	return TRUE;
}