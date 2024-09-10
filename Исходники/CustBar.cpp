void CCustomToolBar::DeselectPalette(CDC& dc, CPalette*& pOldPalette, BOOL fForceBackground)
{
	// Helper method for deselecting the palette out of a DC.
   if (pOldPalette != NULL)
   {
      dc.SelectPalette(pOldPalette, fForceBackground);

		if (!fForceBackground)
		{
			dc.RealizePalette();
		}

      pOldPalette = NULL;
   }
}