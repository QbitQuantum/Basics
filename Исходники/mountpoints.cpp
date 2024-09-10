void CMountPoints::GetDriveVolumes()
{
	m_drive.SetSize(32);

	DWORD drives= GetLogicalDrives();
	int i;
	DWORD mask= 0x00000001;
	for (i=0; i < 32; i++, mask <<= 1)
	{
		CString volume;

		if ((drives & mask) != 0)
		{
			CString s;
			s.Format(_T("%c:\\"), i + _T('A'));

			BOOL b= m_va.GetVolumeNameForVolumeMountPoint(s, volume.GetBuffer(_MAX_PATH), _MAX_PATH);
			volume.ReleaseBuffer();

			if (!b)
			{
				TRACE(_T("GetVolumeNameForVolumeMountPoint(%s) failed.\n"), s);
				volume.Empty();
			}
		}

		m_drive[i]= volume;
	}
}