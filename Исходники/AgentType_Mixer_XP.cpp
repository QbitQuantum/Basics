//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//agenttype_mixer_notify
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void agenttype_mixer_notify_xp (agent *a, int notifytype, void *messagedata)
{
	
	//Get the agent details
	AgentType_Mixer_XP * details = static_cast<AgentType_Mixer_XP *>(a->agentdetails);

	//Variables
	double *value_double = NULL;
	bool *value_bool = NULL;
	MIXERCONTROLDETAILS_UNSIGNED    mixer_setcontrol_value_double;
	MIXERCONTROLDETAILS_BOOLEAN     mixer_setcontrol_value_bool;

	switch (notifytype)
	{
		case NOTIFY_CHANGE:
		{
			//Set up the values
			if (a->agenttypeptr->format & CONTROL_FORMAT_SCALE)
			{
				value_double = (double *) messagedata;
				details->m_mixer_controldetails.paDetails = &mixer_setcontrol_value_double;
			}
			else if (a->agenttypeptr->format & CONTROL_FORMAT_BOOL)
			{
				value_bool = (bool *) messagedata;
				details->m_mixer_controldetails.paDetails = &mixer_setcontrol_value_bool;
			}

			//Retrieve the details
			if (MMSYSERR_NOERROR != mixerGetControlDetails((HMIXEROBJ) details->m_mixer_handle, &details->m_mixer_controldetails, MIXER_GETCONTROLDETAILSF_VALUE)) return;

			//Set the value
			if (a->agenttypeptr->format & CONTROL_FORMAT_SCALE)
			{
				mixer_setcontrol_value_double.dwValue = (ULONG) (*value_double * 65535);
			}
			else if (a->agenttypeptr->format & CONTROL_FORMAT_BOOL)
			{
				mixer_setcontrol_value_bool.fValue = *value_bool;
			}

			//Reload the details
			MMRESULT const res = mixerSetControlDetails((HMIXEROBJ) details->m_mixer_handle, &details->m_mixer_controldetails, MIXER_SETCONTROLDETAILSF_VALUE);
			if (MMSYSERR_NOERROR != res) return;

			break;
		}
		case NOTIFY_SAVE_AGENT:
			//Write existance
			char temp[30];
			sprintf(temp, "%d %d %d", (int)details->m_device, (int)details->m_line, (int)details->m_control);
			config_write(config_get_control_setagent_c(a->controlptr, a->agentaction, a->agenttypeptr->agenttypename, temp));
			break;
	}
}