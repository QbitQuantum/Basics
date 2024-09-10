void CFontDialog::GetCharFormat(CHARFORMAT& cf) const
{
	USES_CONVERSION;
	cf.dwEffects = 0;
	cf.dwMask = 0;
	if ((m_cf.Flags & CF_NOSTYLESEL) == 0)
	{
		cf.dwMask |= CFM_BOLD | CFM_ITALIC;
		cf.dwEffects |= (IsBold()) ? CFE_BOLD : 0;
		cf.dwEffects |= (IsItalic()) ? CFE_ITALIC : 0;
	}
	if ((m_cf.Flags & CF_NOSIZESEL) == 0)
	{
		cf.dwMask |= CFM_SIZE;
		//GetSize() returns in tenths of points so mulitply by 2 to get twips
		cf.yHeight = GetSize()*2;
	}

	if ((m_cf.Flags & CF_NOFACESEL) == 0)
	{
		cf.dwMask |= CFM_FACE;
		cf.bPitchAndFamily = m_cf.lpLogFont->lfPitchAndFamily;
		lstrcpyA(cf.szFaceName, T2A((LPTSTR)(LPCTSTR)GetFaceName()));
	}

	if (m_cf.Flags & CF_EFFECTS)
	{
		cf.dwMask |= CFM_UNDERLINE | CFM_STRIKEOUT | CFM_COLOR;
		cf.dwEffects |= (IsUnderline()) ? CFE_UNDERLINE : 0;
		cf.dwEffects |= (IsStrikeOut()) ? CFE_STRIKEOUT : 0;
		cf.crTextColor = GetColor();
	}
	if ((m_cf.Flags & CF_NOSCRIPTSEL) == 0)
	{
		cf.bCharSet = m_cf.lpLogFont->lfCharSet;
		cf.dwMask |= CFM_CHARSET;
	}
	cf.yOffset = 0;
}