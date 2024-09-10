void vmsFDMCustomizations::EncryptFile(vmsMemFile &file)
{
	DWORD dwSize = file.get_FileBufferSize () - 4;

	
	
	DWORD dw = 8 - (dwSize % 8);
	if (dw != 8)
		file.WriteFile ("\0\0\0\0\0\0\0", dw);

	LPBYTE pb = file.get_FileBuffer () + 4;
	dwSize = file.get_FileBufferSize () - 4;
	
	LPBYTE pbRes = new BYTE [dwSize];
	m_des.Encrypt (pb, pbRes, dwSize);
	m_xor.Encrypt (pbRes, pbRes, dwSize);
	CopyMemory (pb, pbRes, dwSize);
	delete [] pbRes;
}