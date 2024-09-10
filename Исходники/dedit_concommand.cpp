// Note : This can't use CEditRegion::RenameTexture because that initializes the texture space.  Which we don't want.
// (It also counts the number of instances, which doesn't give nearly as much information...)
static void dcon_ReplaceTextures(int argc, char *argv[])
{
	if (argc < 2)
	{
		// Display an error.  Must have 2 arguments
		AddDebugMessage("Not enough texture arguments specified.  Please use the form:");
		AddDebugMessage("  ReplaceTex CurrentTexture NewTexture");
		return;
	}

	// Get the current region
	CRegionDoc  *pDoc = GetActiveRegionDoc();
	if (!pDoc)
	{
		AddDebugMessage("No active document available.");
		return;
	}

	CEditRegion *pRegion = pDoc->GetRegion();
	if (!pRegion)
	{
		AddDebugMessage("No active region available.");
		return;
	}

	// Tell the user what we're doing..
	AddDebugMessage("Searching %d brushes for replacement...", pRegion->m_Brushes.GetSize());

	// Keep track of the replacement count
	uint32 nReplaceCount = 0;

	// Point into the brush list
	LPOS iPos = pRegion->m_Brushes.GetHeadPosition();

	// Replace textures on all brush matching argv[0] with argv[1]
	while (iPos)
	{
		// Get the brush
		CEditBrush *pBrush = pRegion->m_Brushes.GetNext(iPos);

		// Did we find a match on this brush?
		bool bFoundMatch = false;

		// For every polygon..
		for (uint32 nPolyLoop = 0; nPolyLoop < pBrush->m_Polies; ++nPolyLoop)
		{
			CEditPoly *pPoly = pBrush->m_Polies[nPolyLoop];

			for(uint32 nCurrTex = 0; nCurrTex < CEditPoly::NUM_TEXTURES; nCurrTex++)
			{
				// Is this your texture?
				if (stricmp(pPoly->GetTexture(nCurrTex).m_pTextureName, argv[0]) == 0)
				{
					// Replace it...
					pPoly->GetTexture(nCurrTex).m_pTextureName = pRegion->m_pStringHolder->AddString(argv[1]);
					pPoly->GetTexture(nCurrTex).UpdateTextureID();

					// Found a match..
					bFoundMatch = true;
				}
			}
		}

		if (bFoundMatch)
			++nReplaceCount;
	}

	// And the results were...?
	AddDebugMessage("Done.  Replaced texture on %d brushes", nReplaceCount);

	// Redraw the region & mark it as changed if necessary
	if (nReplaceCount)
	{
		pDoc->Modify();
		pDoc->RedrawAllViews();
	}
}