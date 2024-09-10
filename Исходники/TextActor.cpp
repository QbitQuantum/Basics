//--------------------------------------------------------------------------------
void TextActor::DrawLine( const std::wstring& text )
{
	// Check the length of the string, and use the line justification to advance 
	// the cursor an appropriate amount before actually drawing the line of text.

	float fWidth = m_pSpriteFont->GetStringWidth( text ) * m_fPhysicalScale;

	switch( m_LineJustification )
	{
	case LineJustification::LEFT:
		// No change needed - just draw the text from teh current cursor position
		break;
	case LineJustification::CENTER:
		// Advance cursor to the 'left' by half the string width
		AdvanceCursor( -fWidth * 0.5f );
		break;
	case LineJustification::RIGHT:
		// Advance the cursor by the full size of the string.
		AdvanceCursor( -fWidth );
	}


	for ( UINT i = 0; i < text.length(); i++ )
	{
		wchar_t character = text[i];

		if ( character == ' ' ) {
			
			// For a space, we simply move over one space's width for the next
			// character.
			Space();

		} else if ( character == '\n' ) {
			
			// Go back to the original location on xdir, and advance along ydir.
			NewLine();

		} else {
			
			// If this is an actual character, then draw it!
			DrawCharacter( character );

		}
	}

	//NewLine();
}