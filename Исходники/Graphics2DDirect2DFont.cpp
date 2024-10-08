	// ------------------------------------------------------------------------------------------
	//! Creates a 2D font with specified parameters.
	//! @param gfxFontCreationInfo Pointer to the font creation information.
	GDAPI IGraphics2DDirect2DFont::IGraphics2DDirect2DFont(IGraphics2DFontCreationInfo const* const gfxFontCreationInfo)
		: IGraphics2DFont(gfxFontCreationInfo), D2DFontName(L"_font_"), D2DFontCollection(nullptr)
	{
		switch (gfxFontCreationInfo->FontLocation)
		{
		case IGRPAHICS2D_FONT_LOCATION_FILE: 
			{
#if GD_FALSE || 1
				BOOL   D2DFontIsSystem = FALSE;
				UINT32 D2DFontSystemIndex = UINT32_MAX;
				WCHAR  D2DFontFileName[_MAX_FNAME] = {};

				// First of all, we will try to load the font from the system collection..
				_wsplitpath_s(gfxFontCreationInfo->FontFilePath, nullptr, 0, nullptr, 0, D2DFontFileName, GD_ARRAY_LENGTH(D2DFontFileName), nullptr, 0);
				ThrowIfFailed(GD_IGRAPHICS2D_DIRECT2D->D2DDWFontCollectionDefault->FindFamilyName(D2DFontFileName, &D2DFontSystemIndex, &D2DFontIsSystem));
				if (D2DFontIsSystem != FALSE && D2DFontSystemIndex != UINT32_MAX)
				{
					// Font with this name was located inside system. There is no need to reload this font once more time. 
					// Theoretically, this font may differ from the system one.. but I don't give a shit.
					D2DFontCollection = GD_IGRAPHICS2D_DIRECT2D->D2DDWFontCollectionDefault;
					D2DFontName = D2DFontFileName;
					return;
				}
#endif	// if GD_FALSE

			//	GD_IGRAPHICS2D_DIRECT2D->D2DTextFactory->CreateCustomFontFileReference();
			} break;

			default: 
				GD_DEBUG_ASSERT_FALSE("Invalid font location.");
		}
	}