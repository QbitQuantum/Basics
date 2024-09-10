bool SndfileDecoder::Open(FileSpecifier& File)
{
	if (sndfile)
	{
		sf_close(sndfile);
		sndfile = 0;
	}

	sfinfo.format = 0;
	sndfile = sf_open(File.GetPath(), SFM_READ, &sfinfo);

	return sndfile;
}