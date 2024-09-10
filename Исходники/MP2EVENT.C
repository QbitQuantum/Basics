int checkhang()
{
	long ptr[4];
	
	first_init=0;
	
	buffptr(ptr);

#ifdef DEBUG	
	fprintf(stderr,"first_buf=%lx ptr[0]=%lx\n",first_buf,ptr[0]);
#endif

	if(ptr[0]-first_buf < 512)
	{
#ifdef DEBUG
		fprintf(stderr,"init failed, trying again!\n");
		fprintf(stderr,"first_buf=%lx ptr[0]=%lx\n",first_buf,ptr[0]);
#endif
		Fseek(o_filepos,fd,0);
		filepos = o_filepos;
		init_replay();
		return 1;
	}
	return 0;
}