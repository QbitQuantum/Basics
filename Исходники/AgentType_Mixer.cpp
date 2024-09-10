//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//agenttype_mixer_destroy
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int agenttype_mixer_destroy(agent *a)
{
	if (a->agentdetails)
	{
		//Get the details
		agenttype_mixer_details *details = (agenttype_mixer_details *) a->agentdetails;

		//Close the window
		if (details->hwnd_reciever) window_helper_destroy(details->hwnd_reciever);
		details->hwnd_reciever = NULL;

		//Close the mixer
		mixerClose(details->mixer_handle);

		//Delete the details
		delete details;
		a->agentdetails = NULL;
	}

	//Destroy the window if necessary
	mixer_controlcount--;
	if (mixer_controlcount < 1 && mixer_recieverregistered)
	{
		window_helper_unregister(mixer_recieverclass);
		mixer_recieverregistered = false;
	}

	//No errors
	return 0;
}