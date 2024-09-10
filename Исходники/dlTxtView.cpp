void CdlTxtView::OnSetSize(NMHDR* pNMHDR, LRESULT* pRes)
{
	
	CFont cfont;
	cfont.CreateFontW(-((CHARNMHDR*)pNMHDR)->cf.yHeight/20,                        // nHeight
					0,                         // nWidth
				  0,                         // nEscapement
				  0,                         // nOrientation
				  400,                 // nWeight
				  FALSE,                     // bItalic
				  FALSE,                     // bUnderline
				  0,                         // cStrikeOut
				  ANSI_CHARSET,              // nCharSet
				  OUT_DEFAULT_PRECIS,        // nOutPrecision
				  CLIP_DEFAULT_PRECIS,       // nClipPrecision
				  DEFAULT_QUALITY,           // nQuality
				  DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
				  _T("Arial"));
	GetRichEditCtrl().SetFont(&cfont);

	*pRes =1;
}