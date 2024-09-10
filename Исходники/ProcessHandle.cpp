void InitVolumeName()
{
	DWORD disk = GetLogicalDrives();
	for (int i=0; i<26; i++)
	{
		if (disk&(1<<i))
		{
			char str[] = "A-:\\";
			str[0] += i;
			GetVolumeInformationA(str, NULL, 0, &Volumeserial[i], 0, 0, 0, 0);
		}
	}
}