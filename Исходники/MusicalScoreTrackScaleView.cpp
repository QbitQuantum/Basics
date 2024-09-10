	forEachTrack (pMIDIData, pTempTrack) {
		if (pMusicalScoreFrame->IsTrackVisible (i)) {
			if (lVisibleTopTrack <= i && i <= lVisibleBottomTrack) { 
				long lColor = MIDITrack_GetForeColor (pTempTrack);
				pDC->SetTextColor (lColor);
				CPen theTrackPen;
				CBrush theTrackBrush;
				theTrackPen.CreatePen (PS_SOLID, 1, lColor);
				theTrackBrush.CreateSolidBrush (lColor);
				CPen* pOldPen = pDC->SelectObject (&theTrackPen);
				CBrush* pOldBrush = pDC->SelectObject (&theTrackBrush);
				DrawTimeAndKeySignature (pDC, i, lTime);
				pDC->SelectObject (pOldPen);
				pDC->SelectObject (pOldBrush);
				theTrackPen.DeleteObject ();
				theTrackBrush.DeleteObject ();
			}
		}
		i++;
	}