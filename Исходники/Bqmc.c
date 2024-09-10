int hang (int howlonghang)
{
	int lol;
	int templocaltime;
	#ifndef LINUX
		templocaltime = _time32(NULL);
	#endif
	#ifdef LINUX
		templocaltime = time(&temploctim);
	#endif
	lol = templocaltime + howlonghang;
	for(;;)
	{
		#ifndef LINUX
			templocaltime = _time32(NULL);
		#endif
		#ifdef LINUX
			templocaltime = time(&temploctim);
		#endif
		if(lol == templocaltime)
			break;
	}
	return 0;
};