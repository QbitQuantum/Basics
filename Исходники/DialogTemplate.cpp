void Dialog::TemplateMaker::Create (Dialog::Template & tmpl)
{
	tmpl.SetVersion (1); // Extended
	Dialog::Template::Serializer out = tmpl.GetSerializer ();
	// WORD dlgVer;
	out.PutWord (1);
	// WORD signature;
	out.PutWord (0xffff);
	// DWORD helpID;
	out.PutDWord (_helpId);
	// DWORD exStyle;
	out.PutDWord (_style.GetExStyleBits ());
	// DWORD style;
	out.PutDWord (_style.GetStyleBits ());
	// WORD cDlgItems;
	out.PutWord (static_cast<WORD>(_items.size ()));
	// short x, y, cx, cy;
	out.PutShort(static_cast<short>(_rect.Left()));
	out.PutShort(static_cast<short>(_rect.Top()));
	out.PutShort(static_cast<short>(_rect.Width()));
	out.PutShort(static_cast<short>(_rect.Height()));
	// sz_Or_Ord menu;
	out.PutWchar (0);
	// sz_Or_Ord windowClass;
	out.PutWchar (0);
	// WCHAR title[titleLen];
	out.PutString (_title);
	if (_style.TestStyleBits (Dialog::Style::SetFont))
	{
		// These members are only present if the style specified DS_SETFONT or DS_SHELLFONT
		// WORD pointsize;
		out.PutWord (_pointSize);
		// WORD weight;
		out.PutWord (_weight);
		// BYTE italic;
		out.PutByte (_italic ? 1 : 0);
		// BYTE charset;
		out.PutByte (_charSet);
		// WCHAR typeface[stringLen];
		out.PutString (_fontName);
	}
	for (ItemList::const_iterator it = _items.begin (); it != _items.end (); ++it)
		(*it)->Serialize (out);
}