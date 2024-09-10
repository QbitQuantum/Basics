CUIStatic* CUIListBoxItem::AddField(LPCSTR txt, float len, LPCSTR key)
{
	fields.push_back		(xr_new<CUIStatic>());
	CUIStatic* st			= fields.back();
	AttachChild				(st);
	st->Init				(FieldsLength(),0, GetWidth(), len);
	st->SetFont				(GetFont());
	st->SetTextAlignment	(GetTextAlignment());
	st->SetVTextAlignment	(m_lines.GetVTextAlignment());
	st->SetTextColor		(GetTextColor());
	st->SetText				(txt);	
	st->SetWindowName		(key);

	return st;
}