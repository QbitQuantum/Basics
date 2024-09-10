wxString KeynameConverter::discardModifier( const wxString& keystring )
{
	wxString result;
	if ( keystring.EndsWith(wxT("+")) )	//handle stuff like numpad+ or ctrl++
	{
		wxString tmp = keystring;
		result = tmp.RemoveLast().AfterLast(wxT('+')) + wxT('+');
	}
	else if ( keystring.StartsWith(wxT("+")) )	//handle stuff like "+ (numpad)"
	{
		result = keystring;
	}
	else 
	{
		size_t lastAdd = keystring.find_last_of(wxT('+'));
		if ( ( lastAdd != keystring.npos ) && ( keystring.GetChar(lastAdd - 1) == wxT('+') ) )
		{
			assert( (lastAdd > 0) && "character '+' found in unexcepted location!" );
			result = keystring.substr( lastAdd );
		}
		else
		{
			result = keystring.AfterLast(wxT('+'));
		}
	}
	return result;
}