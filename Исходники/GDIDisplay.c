static void SetPaletteColors(void)
{
    assert(This.m_PalEntries      != NULL);
    assert(This.m_AdjustedPalette != NULL);

    if (This.m_nDepth == 8)
    {
        assert(This.m_hPalette != NULL);
        SetPaletteEntries(This.m_hPalette, 0, This.m_nTotalColors, This.m_AdjustedPalette);
    }
    else
    if (This.m_bModifiablePalette == TRUE)
    {
        UINT i;

        for (i = 0; i < This.m_nTotalColors; i++)
        {
	        This.m_p16BitLookup[i] = MAKECOL(This.m_AdjustedPalette[i].peRed,
                                             This.m_AdjustedPalette[i].peGreen,
                                             This.m_AdjustedPalette[i].peBlue) * 0x10001;
        }
    }
}