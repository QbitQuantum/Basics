/*
============
CDAudio_AccessVolume
  JDH: get/set CD volume
       (code adpated from cd_player.c in avp package at icculus.org)
============
*/
void CDAudio_AccessVolume (float *vol, CDDA_OP op)
{
	int					numDevs, i;
	HMIXEROBJ			hMixer;
	MIXERLINEA			line;
	MIXERLINECONTROLSA	lineControls;
	MIXERCONTROL		control;
	MIXERCONTROLDETAILS details;
	MIXERCONTROLDETAILS_UNSIGNED detailValue;
	DWORD				range;
	
	numDevs = mixerGetNumDevs ();
	for (i = 0; i < numDevs; i++)
	{
		if (mixerOpen ((HMIXER *)&hMixer, i, 0, 0, MIXER_OBJECTF_MIXER) != MMSYSERR_NOERROR)
			continue;

		line.cbStruct = sizeof(MIXERLINE);
		line.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC;

		if (mixerGetLineInfoA (hMixer, &line, MIXER_GETLINEINFOF_COMPONENTTYPE) == MMSYSERR_NOERROR)
		{
			control.cbStruct = sizeof(MIXERCONTROL);
			
			lineControls.cbStruct = sizeof(MIXERLINECONTROLS);
			lineControls.dwLineID = line.dwLineID;
			lineControls.pamxctrl = &control;
			lineControls.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
			lineControls.cControls = 1;
			lineControls.cbmxctrl = sizeof(MIXERCONTROL);
			
			if (mixerGetLineControlsA (hMixer, &lineControls, MIXER_GETLINECONTROLSF_ONEBYTYPE) == MMSYSERR_NOERROR)
			{
				details.cbStruct = sizeof(MIXERCONTROLDETAILS);
				details.dwControlID = control.dwControlID;
				details.cChannels = 1;
				details.cMultipleItems = 0;
				details.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
				details.paDetails = &detailValue;

				range = control.Bounds.dwMaximum - control.Bounds.dwMinimum;
				if (op == CDDA_SETVOL)
				{
					detailValue.dwValue = control.Bounds.dwMinimum + (*vol * range);
				
					mixerSetControlDetails (hMixer, &details, MIXER_SETCONTROLDETAILSF_VALUE);
				}
				else
				{
					mixerGetControlDetails (hMixer, &details, MIXER_GETCONTROLDETAILSF_VALUE);

					*vol = (float)(detailValue.dwValue - control.Bounds.dwMinimum) / range;
				}
				
				mixerClose ((HMIXER) hMixer);
				return;
			}
		}
		
		mixerClose ((HMIXER) hMixer);
	}
}