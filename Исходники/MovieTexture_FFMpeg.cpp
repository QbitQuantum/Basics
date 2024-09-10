avcodec::offset_t URLRageFile_seek( avcodec::URLContext *h, avcodec::offset_t pos, int whence )
{
	RageFileBasic *f = (RageFileBasic *) h->priv_data;
	if( whence == AVSEEK_SIZE )
		return f->GetFileSize();

	if( whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END )
		return -1;

	return f->Seek( (int) pos, whence );
}