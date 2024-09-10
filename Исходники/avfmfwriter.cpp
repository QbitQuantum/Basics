int AVFmfWriter::Close()
{
	//seek to location in file where nframes is stored and replace
	fseek (fp, 20, SEEK_SET );	
	_fwrite_nolock(&nframes, sizeof(unsigned __int64), 1, fp);

	fclose(fp);
	fclose(flog);
	fclose(ftraj);

	fp = NULL;
	flog = NULL;
	ftraj = NULL;

	return 1;
}