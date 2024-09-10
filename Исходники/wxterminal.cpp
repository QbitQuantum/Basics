bool wxTerminal::CheckForCD( const wxString &command, wxString &path )
{
	if ( command.IsEmpty() )               return false; // Returning true tells caller there's nothing else to do
	if ( command.Left(2) != wxT("cd") )    return false; // Not a cd attempt so return false so that RunCommand takes over
	if ( wxIsalpha( command.GetChar(2) ) ) return false; // This must be a real command beginning with cd???

	if ( command == wxT("cd.") || command == wxT("cd .") )  {
		path = wxGetCwd();
		return true;
	}

	if ( command == wxT("cd") || command == wxT("cd~") || command == wxT("cd ~") ) {
		path = wxGetHomeDir();
		return true;

	} else if ( command.Find(wxT("&&")) != wxNOT_FOUND ) {
		// a complex command: cd <somewhere> && ...
		return false;

	} else {
		// Otherwise it should be a real dir. Remove the initial cd, plus any white-space
		path = command.Mid( 2 );
		path << wxFileName::GetPathSeparator();
		path.Trim(false);
		wxFileName fn(path);
		fn.MakeAbsolute(m_workingDir);
		fn.Normalize();
		if( fn.DirExists() ) {
			path = fn.GetFullPath();
			return true;
		}
		return false;
	}
}