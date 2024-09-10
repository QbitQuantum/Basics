int PlatChangeCDDAVolume(int volume)
{
    MMRESULT mmres;
	unsigned int newVolume;
	int i;
	int numDev = mixerGetNumDevs();

    /* check the cdDeviceId */
    if(cdDeviceID==NO_DEVICE) return SOUND_PLATFORMERROR;

	//go through the mixer devices searching for one that can deal with the cd volume
	for(i=0;i<numDev;i++)
	{
		HMIXER handle;
		if(mixerOpen(&handle,i,0,0,MIXER_OBJECTF_MIXER ) == MMSYSERR_NOERROR )
		{
			
			//try to get the compact disc mixer line
			MIXERLINE line;
			line.cbStruct=sizeof(MIXERLINE);
			line.dwComponentType=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC;

			if(mixerGetLineInfo(handle,&line,MIXER_GETLINEINFOF_COMPONENTTYPE) == MMSYSERR_NOERROR)
			{
				MIXERLINECONTROLS lineControls;
				MIXERCONTROL control;


				lineControls.cbStruct=sizeof(MIXERLINECONTROLS);
				lineControls.dwLineID=line.dwLineID;
				lineControls.pamxctrl=&control;
				lineControls.dwControlType=MIXERCONTROL_CONTROLTYPE_VOLUME ;
				lineControls.cControls=1;
				lineControls.cbmxctrl=sizeof(MIXERCONTROL);
				
				control.cbStruct=sizeof(MIXERCONTROL);


				//try to get the volume control
				if(mixerGetLineControls(handle,&lineControls,MIXER_GETLINECONTROLSF_ONEBYTYPE)==MMSYSERR_NOERROR)
				{

					MIXERCONTROLDETAILS details;
					MIXERCONTROLDETAILS_UNSIGNED detailValue;

					details.cbStruct=sizeof(MIXERCONTROLDETAILS);
					details.dwControlID=control.dwControlID;
					details.cChannels=1;
					details.cMultipleItems=0;
					details.cbDetails=sizeof(MIXERCONTROLDETAILS_UNSIGNED);
					details.paDetails=&detailValue;
										
					
					if(volume==CDDA_VOLUME_RESTOREPREGAMEVALUE)
					{
						//set the volume to what it was before the game started
						newVolume=PreGameCDVolume;
					}
					else
					{
						//scale the volume
						newVolume = control.Bounds.dwMinimum +  WideMulNarrowDiv(volume,
							(control.Bounds.dwMaximum-control.Bounds.dwMinimum), (CDDA_VOLUME_MAX-CDDA_VOLUME_MIN));

						if(newVolume<control.Bounds.dwMinimum) newVolume=control.Bounds.dwMinimum;
						if(newVolume>control.Bounds.dwMaximum) newVolume=control.Bounds.dwMaximum;
					}
					//fill in the volume in the control details structure
					detailValue.dwValue=newVolume;
	
	
					mmres = mixerSetControlDetails(handle,&details,MIXER_SETCONTROLDETAILSF_VALUE);
					mixerClose(handle);

					if(mmres==MMSYSERR_NOERROR) return 1;
					else return SOUND_PLATFORMERROR;	
					
				}
			}
			 
			
			mixerClose(handle);
		}

	}

	return SOUND_PLATFORMERROR;
}