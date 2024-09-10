void RichLabel::CreateLabel( const Gwen::UnicodeString & text, const DividedText & txt, int & x, int & y, int & lineheight, bool NoSplit )
{
	//
	// Use default font or is one set?
	//
	Gwen::Font* pFont = GetSkin()->GetDefaultFont();

	if ( txt.font ) { pFont = txt.font; }

	//
	// This string is too long for us, split it up.
	//
	Gwen::Point p = GetSkin()->GetRender()->MeasureText( pFont, text );

	if ( lineheight == -1 )
	{
		lineheight = p.y;
	}

	if ( !NoSplit )
	{
		if ( x + p.x > Width() )
		{
			return SplitLabel( text, pFont, txt, x, y, lineheight );
		}
	}

	//
	// Wrap
	//
	if ( x + p.x >= Width() )
	{
		CreateNewline( x, y, lineheight );
	}

	Gwen::Controls::Label*	pLabel = new Gwen::Controls::Label( this );
	pLabel->SetText( x == 0 ? Gwen::Utility::Strings::TrimLeft<Gwen::UnicodeString> ( text, U" " ) : text );
	pLabel->SetTextColor( txt.color );
	pLabel->SetFont( pFont );
	pLabel->SizeToContents();
	pLabel->SetPos( x, y );
	//lineheight = (lineheight + pLabel->Height()) / 2;
	x += pLabel->Width();

	if ( x >= Width() )
	{
		CreateNewline( x, y, lineheight );
	}
}