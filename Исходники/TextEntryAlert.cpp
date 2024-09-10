void TextEntryAlertBackgroundView::Draw(BRect update_rect)
{
	if(update_rect.Intersects(m_entry_text_rect))
	{
		SetHighColor(m_dark_1_color);
		StrokeLine(BPoint(m_entry_text_rect.left,m_entry_text_rect.top),
			BPoint(m_entry_text_rect.right,m_entry_text_rect.top));
		StrokeLine(BPoint(m_entry_text_rect.left,m_entry_text_rect.top+1),
			BPoint(m_entry_text_rect.left,m_entry_text_rect.bottom));
		SetHighColor( ui_color(B_SHINE_COLOR));
		StrokeLine(BPoint(m_entry_text_rect.right,m_entry_text_rect.top+1),
			BPoint(m_entry_text_rect.right,m_entry_text_rect.bottom-1));
		StrokeLine(BPoint(m_entry_text_rect.left+1,m_entry_text_rect.bottom),
			BPoint(m_entry_text_rect.right,m_entry_text_rect.bottom));
		SetHighColor( BmWeakenColor(B_SHADOW_COLOR, BeShadowMod));
		StrokeLine(BPoint(m_entry_text_rect.left+1,m_entry_text_rect.top+1),
			BPoint(m_entry_text_rect.right-1,m_entry_text_rect.top+1));
		StrokeLine(BPoint(m_entry_text_rect.left+1,m_entry_text_rect.top+2),
			BPoint(m_entry_text_rect.left+1,m_entry_text_rect.bottom-1));
	}
}