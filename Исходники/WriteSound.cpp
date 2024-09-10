LRESULT WriteSound::OnCreateFile(WPARAM wParam, LPARAM lParam)
{
int cbsize;
MMRESULT mmret;
char *filename=(char*)lParam;
char str[200];
sprintf(str,"filename is %s ",filename);

log.WriteString(str);

log.WriteString("\n Creating new file ");


m_hwrite=::mmioOpen(filename,NULL,MMIO_CREATE |MMIO_WRITE | MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
	
	if(filename)
	delete filename;


	if(m_hwrite==NULL)
	{
	log.WriteString("Unable to create the specified file");
	return FALSE;
	}
	//AfxMessageBox("File created ");
	log.WriteString("\n File created successfully");

	ZeroMemory(&riffblock,sizeof(MMCKINFO));
	ZeroMemory(&fmtblock,sizeof(MMCKINFO));
	ZeroMemory(&datablock,sizeof(MMCKINFO));

	riffblock.fccType=mmioFOURCC('W','A','V','E');
	mmret=mmioCreateChunk(m_hwrite,&riffblock,MMIO_CREATERIFF);
	
	if(mmret!=MMSYSERR_NOERROR)
	{
	log.WriteString("\n Riff format writing error");
	return FALSE;
	}


	fmtblock.ckid=mmioFOURCC('f','m','t',' ');
	cbsize=sizeof(WAVEFORMATEX)-2;
	fmtblock.cksize=cbsize;
	mmret=mmioCreateChunk(m_hwrite,&fmtblock,0);
	
	if(mmret!=MMSYSERR_NOERROR)
	{
	log.WriteString("\n fmt format writing error");
	return FALSE;
	}
	
	::mmioWrite(m_hwrite,(const char*)&waveformat,cbsize);

	datablock.ckid=mmioFOURCC('d','a','t','a');
	mmret=mmioCreateChunk(m_hwrite,&datablock,0);
	
	if(mmret!=MMSYSERR_NOERROR)
	{
	log.WriteString("\n data format writing error");
	return FALSE;
	}

	log.WriteString("\n Format details written successfully");
return TRUE;
}