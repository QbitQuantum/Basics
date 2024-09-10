int CamuleGuiBase::InitGui(bool geometry_enabled, wxString &geom_string)
{
	// Standard size is 800x600 at position (0,0)
	int geometry_x = 0;
	int geometry_y = 0;
	unsigned int geometry_width = 800;
	unsigned int geometry_height = 600;

	if ( geometry_enabled ) {
		// I plan on moving this to a separate function, as it just clutters up OnInit()
		/*
		This implementation might work with mac, provided that the
		SetSize() function works as expected.
		*/

		// Remove possible prefix
		if ( geom_string.GetChar(0) == '=' ) {
			geom_string.Remove( 0, 1 );
		}

		// Stupid ToLong functions forces me to use longs =(
		long width = geometry_width;
		long height = geometry_height;

		// Get the avilable display area
		wxRect display = wxGetClientDisplayRect();

		// We want to place aMule inside the client area by default
		long x = display.x;
		long y = display.y;

		// Tokenize the string
		wxStringTokenizer tokens(geom_string, wxT("xX+-"));

		// First part: Program width
		if ( tokens.GetNextToken().ToLong( &width ) ) {
			wxString prefix = geom_string[ tokens.GetPosition() - 1 ];
			if ( prefix == wxT("x") || prefix == wxT("X") ) {
				// Second part: Program height
				if ( tokens.GetNextToken().ToLong( &height ) ) {
					prefix = geom_string[ tokens.GetPosition() - 1 ];
					if ( prefix == wxT("+") || prefix == wxT("-") ) {
						// Third part: X-Offset
						if ( tokens.GetNextToken().ToLong( &x ) ) {
							if ( prefix == wxT("-") )
								x = display.GetRight() - ( width + x );
							prefix = geom_string[ tokens.GetPosition() - 1 ];
							if ( prefix == wxT("+") || prefix == wxT("-") ) {
								// Fourth part: Y-Offset
								if ( tokens.GetNextToken().ToLong( &y ) ) {
									if ( prefix == wxT("-") )
										y = display.GetBottom() - ( height + y );
								}
							}
						}
					}
					// We need at least height and width to override default geometry
					geometry_enabled = true;
					geometry_x = x;
					geometry_y = y;
					geometry_width = width;
					geometry_height = height;
				}
			}
		}
	}

	ResetTitle();

	// Should default/last-used position be overridden?
	if ( geometry_enabled ) {
		amuledlg = new CamuleDlg(NULL, m_FrameTitle,
		                         wxPoint(geometry_x,geometry_y),
		                         wxSize( geometry_width, geometry_height - 58 ));
	} else {
		amuledlg = new CamuleDlg(NULL, m_FrameTitle);
	}

	return 0;
}