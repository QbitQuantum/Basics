/* MainApp::readConfigFile
 * Reads and parses the SLADE configuration file
 *******************************************************************/
void MainApp::readConfigFile()
{
	// Open SLADE.cfg
	Tokenizer tz;
	if (!tz.openFile(appPath("slade3.cfg", DIR_USER)))
		return;

	// Go through the file with the tokenizer
	string token = tz.getToken();
	while (token.Cmp(""))
	{
		// If we come across a 'cvars' token, read in the cvars section
		if (!token.Cmp("cvars"))
		{
			token = tz.getToken();	// Skip '{'

			// Keep reading name/value pairs until we hit the ending '}'
			string cvar_name = tz.getToken();
			while (cvar_name.Cmp("}"))
			{
				string cvar_val = tz.getToken();
				read_cvar(cvar_name, cvar_val);
				cvar_name = tz.getToken();
			}
		}

		// Read base resource archive paths
		if (!token.Cmp("base_resource_paths"))
		{
			// Skip {
			token = wxString::FromUTF8(UTF8(tz.getToken()));

			// Read paths until closing brace found
			token = tz.getToken();
			while (token.Cmp("}"))
			{
				theArchiveManager->addBaseResourcePath(token);
				token = wxString::FromUTF8(UTF8(tz.getToken()));
			}
		}

		// Read recent files list
		if (token == "recent_files")
		{
			// Skip {
			token = tz.getToken();

			// Read files until closing brace found
			token = wxString::FromUTF8(UTF8(tz.getToken()));
			while (token != "}")
			{
				theArchiveManager->addRecentFile(token);
				token = wxString::FromUTF8(UTF8(tz.getToken()));
			}
		}

		// Read keybinds
		if (token == "keys")
		{
			token = tz.getToken();	// Skip {
			KeyBind::readBinds(tz);
		}

		// Read nodebuilder paths
		if (token == "nodebuilder_paths")
		{
			token = tz.getToken();	// Skip {

			// Read paths until closing brace found
			token = tz.getToken();
			while (token != "}")
			{
				string path = tz.getToken();
				NodeBuilders::addBuilderPath(token, path);
				token = tz.getToken();
			}
		}

		// Read game exe paths
		if (token == "executable_paths")
		{
			token = tz.getToken();	// Skip {

			// Read paths until closing brace found
			token = tz.getToken();
			while (token != "}")
			{
				if (token.length())
				{
					string path = tz.getToken();
					Executables::setExePath(token, path);
				}
				token = tz.getToken();
			}
		}

		// Read window size/position info
		if (token == "window_info")
		{
			token = tz.getToken();	// Skip {
			Misc::readWindowInfo(&tz);
		}

		// Get next token
		token = tz.getToken();
	}
}