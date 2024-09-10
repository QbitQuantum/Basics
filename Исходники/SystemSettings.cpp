/**
 * Exec handler implementation.
 *
 * @param InWorld World context
 * @param Cmd	Command to parse
 * @param Ar	Output device to log to
 *
 * @return true if command was handled, false otherwise
 */
bool FSystemSettings::Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar )
{
	FSystemSettingsData OldSystemSettings = *this;

	// Keep track whether the command was handled or not.
	bool bHandledCommand = false;

	if( FParse::Command(&Cmd,TEXT("SCALE")) )
	{
		// Some of these settings are used in both threads so we need to stop the rendering thread before changing them.
		FlushRenderingCommands();

		if( FParse::Command(&Cmd,TEXT("LOWEND")) )
		{
			bHandledCommand	= HandleLowendCommand( Cmd, Ar );
		}
		else if( FParse::Command(&Cmd,TEXT("HIGHEND")) )
		{
			bHandledCommand	= HandleHighendCommand( Cmd, Ar );	
		}

		if (!bHandledCommand)
		{
			Ar.Logf(TEXT("Unrecognized system setting (note that console variables can be set much easier)"));
		}
		else
		{
			// Write the new settings to the INI.
			SaveToIni();
		}
	}

	return bHandledCommand;
}