static int Create(rawaudio* p)
{
	if (Scanf(String(p->Format.Format.Class,RAWAUDIO_FORMAT),T("acodec/0x%x"),&p->Type)!=1)
		return ERR_INVALID_PARAM;
	p->Format.Init = (fmtfunc)RawAudioInit;
	p->Format.Seek = (fmtseek)RawAudioSeek;
	p->Format.ReadPacket = (fmtreadpacket)ReadPacket;
	p->SeekTime = 1; // but don't want to return 0
	p->VBR = 1;
	return ERR_NONE;
}