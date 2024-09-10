//-----------------------------------------------------------------------------
// Purpose: Handle "cd" console command
//-----------------------------------------------------------------------------
void CCDAudio::CD_f ( void )
{
	char	*command;
	int		ret;
	int		n;

	if ( Cmd_Argc() < 2 )
		return;

	command = Cmd_Argv (1);

	if (stricmp(command, "on") == 0)
	{
		m_bEnabled = true;
		return;
	}

	if (stricmp(command, "off") == 0)
	{
		if (m_bIsPlaying)
			Stop();
		m_bEnabled = false;
		return;
	}

	if (stricmp(command, "reset") == 0)
	{
		m_bEnabled = true;
		if (m_bIsPlaying)
			Stop();
		for (n = 0; n < 100; n++)
			m_rgRemapCD[n] = n;
		GetAudioDiskInfo();
		return;
	}

	if (stricmp(command, "remap") == 0)
	{
		ret = Cmd_Argc() - 2;
		if ( ret > 0)
		{
			for (n = 1; n <= ret; n++)
			{
				m_rgRemapCD[n] = atoi(Cmd_Argv (n+1));
			}
		}
		return;
	}

	if (stricmp(command, "close") == 0)
	{
		CloseDoor();
		return;
	}

	if (!m_bIsValid)
	{
		GetAudioDiskInfo();
		if (!m_bIsValid)
		{
			return;
		}
	}

	if (stricmp(command, "play") == 0)
	{
		Play( atoi(Cmd_Argv (2)), false );
		return;
	}

	if (stricmp(command, "loop") == 0)
	{
		Play( atoi(Cmd_Argv (2)), true );
		return;
	}

	if (stricmp(command, "stop") == 0)
	{
		Stop();
		return;
	}

	if (stricmp(command, "pause") == 0)
	{
		Pause();
		return;
	}

	if (stricmp(command, "resume") == 0)
	{
		Resume();
		return;
	}

	if (stricmp(command, "eject") == 0)
	{
		if (m_bIsPlaying)
			Stop();
		Eject();
		m_bIsValid = false;
		return;
	}

	if (stricmp(command, "info") == 0)
	{
		Msg("%u tracks\n", m_nMaxTrack);
		if ( m_bIsPlaying )
		{
			Msg("Currently %s track %u\n", m_bIsLooping ? "looping" : "playing", m_nPlayTrack);
		}
		else if ( m_bWasPlaying )
		{
			Msg("Paused %s track %u\n", m_bIsLooping ? "looping" : "playing", m_nPlayTrack);
		}
		Msg("Volume is %f\n", m_flVolume);
		return;
	}
}