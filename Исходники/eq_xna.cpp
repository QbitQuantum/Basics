	// Recommended frequencies are ...
	//
	//  lowfreq  = 880  Hz
	//  highfreq = 5000 Hz
	//
	// Set mixfreq to whatever rate your system is using (eg 48Khz)
	void init_3band_state(EQSTATE* es, int lowfreq, int highfreq, int mixfreq)
	{
	  // Clear state 

	  memset(es,0,sizeof(EQSTATE));

	  // Set Low/Mid/High gains to unity

	  es->lg = XMVectorReplicate(1.0f);
	  es->mg = XMVectorReplicate(1.0f);
	  es->hg = XMVectorReplicate(1.0f);

	  // Calculate filter cutoff frequencies
	  float	lf = 2 * sinf(cPi * ((float)lowfreq / (float)mixfreq)); 
	  float	hf = 2 * sinf(cPi * ((float)highfreq  / (float)mixfreq)); 

	  es->lf = XMVectorReplicate(lf);
	  es->hf = XMVectorReplicate(hf);
	}