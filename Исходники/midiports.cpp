std::vector<std::string> getInputPorts()
{
	std::vector< std:: string > res;
	
	MIDIINCAPS caps;
	
	int n_devices = midiInGetNumDevs();
	
	for(int i=0; i < n_devices; ++i)
	{
		midiInGetDevCaps(i, &caps, sizeof(MIDIINCAPS));
		WCHAR *wname = caps.szPname;
		
		char name[256];
		int j;
		for(j=0; j<255 && wname[j]!=0; ++j) {
			name[j] = (char)wname[j];
		}
		name[j] = 0;
		
		res.push_back(std::string(name));
	}
	
	return res;
}