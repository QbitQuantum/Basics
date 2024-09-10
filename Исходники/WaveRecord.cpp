void CWaveRecord::GetProductNames(CStringArray& strArrProductNames)
{
	WAVEINCAPS caps;
	
	strArrProductNames.RemoveAll();
	for(int i = 0; i < waveInGetNumDevs(); i++)
	{
		waveInGetDevCaps(i, &caps, sizeof(WAVEINCAPS));
		strArrProductNames.Add(caps.szPname);
	}
}