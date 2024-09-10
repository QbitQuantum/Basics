void PolyDrawArgs::SetStyle(const FRenderStyle &renderstyle, double alpha, uint32_t fillcolor, uint32_t translationID, FTexture *tex, bool fullbright)
{
	bool forcePal = (renderstyle == LegacyRenderStyles[STYLE_Shaded] || renderstyle == LegacyRenderStyles[STYLE_AddShaded]);
	SetTexture(tex, translationID, forcePal);

	if (renderstyle == LegacyRenderStyles[STYLE_Normal] || (r_drawfuzz == 0 && renderstyle == LegacyRenderStyles[STYLE_OptFuzzy]))
	{
		SetStyle(Translation() ? TriBlendMode::TranslatedAdd : TriBlendMode::TextureAdd, 1.0, 0.0);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_Add] && fullbright && alpha == 1.0 && !Translation())
	{
		SetStyle(TriBlendMode::TextureAddSrcColor, 1.0, 1.0);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_Add])
	{
		SetStyle(Translation() ? TriBlendMode::TranslatedAdd : TriBlendMode::TextureAdd, alpha, 1.0);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_Subtract])
	{
		SetStyle(Translation() ? TriBlendMode::TranslatedRevSub : TriBlendMode::TextureRevSub, alpha, 1.0);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_SoulTrans])
	{
		SetStyle(Translation() ? TriBlendMode::TranslatedAdd : TriBlendMode::TextureAdd, transsouls, 1.0 - transsouls);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_Fuzzy] || (r_drawfuzz == 1 && renderstyle == LegacyRenderStyles[STYLE_OptFuzzy]))
	{
		SetColor(0xff000000, 0);
		SetStyle(TriBlendMode::Fuzz);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_Shadow] || (r_drawfuzz == 2 && renderstyle == LegacyRenderStyles[STYLE_OptFuzzy]))
	{
		SetStyle(Translation() ? TriBlendMode::TranslatedAdd : TriBlendMode::TextureAdd, 0.0, 160 / 255.0);
	}
	else if (renderstyle == LegacyRenderStyles[STYLE_TranslucentStencil])
	{
		SetColor(0xff000000 | fillcolor, fillcolor >> 24);
		SetStyle(TriBlendMode::Stencil, alpha, 1.0 - alpha);
	}